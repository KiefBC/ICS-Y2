from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Lock, Thread, Semaphore
import sys
import time

HOST = ""  # Empty string means server will listen on all available interfaces
PORT = 12345  # Port number for the server (must be > 1024 unless root)
SERVER = (HOST, PORT)
SERVER_RUNNING = True  # Global flag to control server shutdown
ALERT = b"!"  # Alert message that clients can send
NUM_CLIENTS = 3  # Number of clients that need to connect

# Counter for tracking total alerts received
alert_count = 0

# Create a list of semaphores for coordinating turns between clients
# Initialize with 0 means all semaphores start in a locked state
client_lock = [Semaphore(0) for _ in range(NUM_CLIENTS)]

# List to keep track of all connected client sockets
client_sockets = []
socket_lock = Lock()  # Mutex lock for safely modifying the shared client_sockets list

def handle_client(client_socket: socket, client_id: int):
    """
    Handle individual client connections. Each client runs in its own thread.
    Args:
        client_socket: The server socket used to accept the connection
        client_id: Unique identifier for this client (0 to NUM_CLIENTS-1)
    """
    global alert_count, client_lock, SERVER_RUNNING, client_sockets
    try:
        # Accept incoming connection
        used_socket, client_address = client_socket.accept()
        
        # Safely add this client to our list of connected clients
        with socket_lock:
            client_sockets.append(used_socket)
            print(f"Client {client_id} connected from {client_address}")

        with used_socket:
            print(f"Thread for client {client_id} unlocked.")
            
            while SERVER_RUNNING:
                # Wait for our turn using the semaphore token system
                client_lock[client_id].acquire()
                
                # Check if server is still running after waiting
                if not SERVER_RUNNING:
                    break
                
                # Prompt client for input
                used_socket.send(b"\nEnter: ? or ! to alert the next client: ")
                client_response = used_socket.recv(1)
                
                # Handle alert message from client
                if client_response == ALERT:
                    alert_count += 1
                    print(f"Alert received from client: {client_id}")
                    print(f"Alert count increased to: {alert_count}")

                    # If we've received 3 alerts, initiate shutdown
                    if alert_count == 3:
                        print("Alert count reached 3. Server shutting down....")
                        SERVER_RUNNING = False
                        
                        # Notify all clients about the shutdown
                        with socket_lock:
                            for sock in client_sockets:
                                try:
                                    # Send multiple messages to ensure delivery
                                    sock.send(b"\nALERT COUNT REACHED 3\n")
                                    sock.send(b"Server is shutting down...\n")
                                    sock.send(b"Goodbye!\n")
                                except Exception as e:
                                    print(f"Error sending shutdown message: {e}")
                        
                        # Release all semaphores so clients aren't stuck waiting
                        for lock in client_lock:
                            try:
                                lock.release()
                            except ValueError:  # Ignore if already released
                                pass
                                
                        break
                        
                # Pass the token to the next client if server is still running
                if SERVER_RUNNING:
                    # Use modulo to wrap around to client 0 after last client
                    client_lock[(client_id + 1) % NUM_CLIENTS].release()
                
    except Exception as e:
        print(f"Error handling client {client_id}: {e}")
    finally:
        # Clean up: remove socket from list and close it
        with socket_lock:
            if used_socket in client_sockets:
                client_sockets.remove(used_socket)
        used_socket.close()

def main():
    """
    Main server function that sets up the socket and creates client threads
    """
    global SERVER_RUNNING
    try:
        # Create and configure the server socket
        with socket(AF_INET, SOCK_STREAM) as server_socket:
            server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
            server_socket.bind(SERVER)
            server_socket.listen(NUM_CLIENTS)
            print("Server is running and listening for connections...")

            # Create threads for each client we expect
            num_connected = 0
            while num_connected != NUM_CLIENTS:
                print("Creating thread for client: ", num_connected)
                Thread(target=handle_client, 
                      args=(server_socket, num_connected), 
                      daemon=True).start()
                num_connected += 1

            print("Server setup complete. Awaiting client connections...")

            # Release the first client's lock to start the token passing
            client_lock[0].release()

            # Keep main thread alive until SERVER_RUNNING becomes False
            while SERVER_RUNNING:
                pass

    except KeyboardInterrupt:
        print("\nServer Shutting Down.....")
        SERVER_RUNNING = False
        # Release all semaphores to allow clients to exit cleanly
        for lock in client_lock:
            try:
                lock.release()
            except:
                pass
        sys.exit(0)

if __name__ == "__main__":
    main()
