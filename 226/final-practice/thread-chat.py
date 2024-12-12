from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Lock, Thread

MAX_CONNECTIONS = 2  # Maximum number of clients allowed
HOST = ""  # Empty string means server will listen on all available interfaces
PORT = 12345  # Port number for the server (must be > 1024 unless root)
SERVER = (HOST, PORT)
SERVER_RUNNING = True  # Global flag to control server shutdown

# Shared resources
clients = []  # List to store all connected client sockets
clients_lock = Lock()  # Mutex lock for safely modifying the shared clients list
client_id = 0  # Counter for assigning unique IDs to clients


def handle_client(client_socket, user_id):
    """
    This function handles individual client connections. Each client runs in its own thread.
    Receives messages from the client and broadcasts them to all other connected clients.

    Args:
        client_socket: Socket object for this client's connection
        user_id: Unique identifier for this client
    """
    global SERVER_RUNNING, clients
    try:
        while SERVER_RUNNING:
            # Receive and decode message from client
            message = client_socket.recv(1024).decode("utf-8").strip()
            if not message:  # Client disconnected if empty message
                break
            print(f"Client {user_id} sent: {message}")

            # Broadcast message to all other clients
            with clients_lock:  # Safely access shared clients list
                for client in clients:
                    if client is not client_socket:  # Don't send back to sender
                        client.send(f"Client {user_id}: {message}\n".encode("utf-8"))
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        # Clean up: remove client from list and close socket
        with clients_lock:
            clients.remove(client_socket)
        print(f"Client {user_id} disconnected.")
        client_socket.close()


def main():
    """
    Main server function that sets up the socket and accepts client connections.
    Creates a new thread for each connected client.
    """
    global SERVER_RUNNING, clients, client_id
    try:
        # Create and configure the server socket
        with socket(AF_INET, SOCK_STREAM) as server_socket:
            server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
            server_socket.bind(SERVER)
            server_socket.listen(MAX_CONNECTIONS)
            print("Server is listening for incoming connections...")

            while SERVER_RUNNING:
                try:
                    # Accept new client connection
                    client_socket, client_address = (
                        server_socket.accept()
                    )  # This line is blocking until a client connects
                    print(
                        f"Client {client_address} connected. This is Client {client_id}"
                    )

                    with clients_lock:
                        user_id = client_id
                        client_id += 1

                    # Check if server is full before accepting client
                    with clients_lock:
                        if len(clients) < MAX_CONNECTIONS:
                            print("Connection accepted.")
                        else:
                            print(
                                "Connection refused. Server is full. Look at this idiot trying to MITM us."
                            )
                            client_socket.send(
                                b"Server is full. Try again later you squid born fuck.\n"
                            )
                            client_socket.close()
                            continue
                        clients.append(client_socket)

                    # Send welcome message to new client
                    client_socket.send(f"Welcome, Client {user_id}!\n".encode("utf-8"))

                    # Create new thread to handle this client
                    Thread(
                        target=handle_client,
                        args=(client_socket, user_id),
                        daemon=True,
                    ).start()
                except Exception as e:
                    print("An error occurred: ", e)
    except KeyboardInterrupt:
        print("\nServer is shutting down...")
        SERVER_RUNNING = False
    except Exception as e:
        print("An error occurred: ", e)
    finally:
        with clients_lock:
            for client in clients:
                client.close()


# Standard Python idiom to ensure main() only runs if this file is run directly
if __name__ == "__main__":
    main()
