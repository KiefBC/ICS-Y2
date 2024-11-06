from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Lock, Thread

"""
Write a Python server that creates a new thread for every client that connects. Each
thread waits for a newline-terminated message from its client, then prints the
message to the server screen, then waits for the next message from its client. Be
sure to use locks so that a print command is not interrupted by another thread's
print command. The server must not crash.
"""

# Constants for server configuration
HOST = ""  # Bind to all available network interfaces
PORT = 12345  # Port number to listen on
NUM_CLIENTS = 5  # Maximum number of queued connections

# Lock for synchronizing print statements
print_lock = Lock()


# Function to handle communication with a single client
def handle_client(client_socket: socket) -> None:
    try:
        # Ensure the client socket is closed after interaction
        with client_socket:
            while True:
                # Read data from the client until a newline character is encountered
                message = b""
                while not message.endswith(b"\n"):
                    data = client_socket.recv(1)  # Receive one byte at a time
                    if not data:
                        return  # If no data, client has disconnected
                    message += data  # Append received byte to the message buffer

                # Safely print the received message using a lock
                with print_lock:
                    print("Received message:", message.decode("utf-8").strip())

                # Continue waiting for the next message from the same client
    except Exception as e:
        # Handle any unexpected exceptions without crashing
        print("An error occurred:", e)


# Main server setup
with socket(AF_INET, SOCK_STREAM) as server_socket:
    # Configure socket to allow address reuse for quicker restarts
    server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    # Bind the socket to the specified host and port
    server_socket.bind((HOST, PORT))
    # Begin listening for incoming connections
    server_socket.listen(NUM_CLIENTS)
    print(f"Server listening on port {PORT}")

    # Main loop to accept and handle incoming connections
    while True:
        # Accept a new client connection
        client_socket, client_address = server_socket.accept()
        print(f"Connection established with {client_address}")

        # Start a new thread to handle each client connection
        Thread(target=handle_client, args=(client_socket,)).start()
