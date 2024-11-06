from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Semaphore, Thread

"""
Write a multithreaded messaging server that accepts 2 connections. The first client
to connect to the server is prompted for a message. The server then sends that
message to the second client. The second client is then prompted for a message,
which is sent back to the server, which in turn sends that message to the first client.
This repeats ad infinitum. Your answer must be multithreaded, using one thread per
client. The server should not crash.
"""

# Server configuration
HOST = ""  # Bind to all available network interfaces
PORT = 12345  # Port number to listen on
NUM_CLIENTS = 2  # Number of clients expected

# Array of semaphores for synchronizing message flow between clients
locks = [Semaphore(), Semaphore()]
locks[
    -1
].acquire()  # Lock the second client initially to ensure the first client starts

# Initial message to prompt the first client
msg = b"Please begin\n"


# Function to read a newline-terminated line from the client
def get_line(current_socket: socket) -> bytes:
    buffer = b""  # Initialize buffer to accumulate bytes received from client
    while True:
        data = current_socket.recv(1)  # Read 1 byte at a time from client
        if data == b"" or data == b"\n":  # End of message or client disconnected
            return buffer
        buffer = (
            buffer + data
        )  # Accumulate bytes in the buffer (can overflow if input is too long)


# Function to handle communication with a single client
def contact_client(client: socket, client_id: int) -> None:
    global locks, msg
    # Accept connection from the client
    sc, _ = client.accept()

    # Ensure socket is closed after interaction
    with sc:
        while True:
            # Wait for this client's turn to send a message (using semaphore)
            locks[client_id].acquire()

            # Send the current message to the client
            # If in the first iteration, the message is the initial prompt
            sc.sendall(msg)

            # Wait for a response from the client
            msg = (
                get_line(sc) + b"\n"
            )  # Get the line from client and append newline for the next client

            # Release the lock for the next client to send their message
            locks[(client_id + 1) % NUM_CLIENTS].release()


# Main server setup
with socket(AF_INET, SOCK_STREAM) as sock:
    # Configure socket to allow address reuse
    sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    # Bind the socket to the specified host and port
    sock.bind((HOST, PORT))
    # Start listening for incoming connections
    sock.listen(NUM_CLIENTS)

    # Counter for connected clients
    num_clients = 0

    # Accept connections until we have the required number of clients
    while num_clients != NUM_CLIENTS:
        # Start a new thread for each client, passing the server socket and client index
        Thread(target=contact_client, args=(sock, num_clients)).start()
        num_clients = num_clients + 1
