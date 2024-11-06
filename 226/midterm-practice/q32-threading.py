from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Semaphore, Thread

"""
Write a Python server that creates a new thread for every client that connects. Each
thread waits for a newline-terminated string from its client. It then converts the
string to an integer (or 0, if that is not possible), and adds it to a global sum. It then
returns the latest global sum to the client. Be sure to use locks so that a race
condition is avoided. Numbers of more than 4 digits are ignored.

For a simple test, echo "123" | nc 127.0.0.1 12345 returns 123 and then echo
"877" | nc 127.0.0.1 12345 returns 1000 and then echo "1 error" | nc 127.0.0.1
12345 returns nothing. Sending echo "12345678" | nc 127.0.0.1 12345 also returns
nothing, but then sending echo "111" | nc 127.0.0.1 12345 returns 1111
"""

# Constants for server configuration
HOST = ""  # Bind to all available network interfaces
NUM_CLIENTS = 1  # Max number of queued connections
PORT = 12345  # Port number to listen on
MAX_DIGITS = 4  # Maximum allowed digits in the input number

# Semaphore lock for synchronizing access to the global sum variable
lock = Semaphore()
ol = 0  # Global sum variable, updated by each client interaction


# Function to read a newline-terminated string from a client socket
def get_line(current_socket: socket) -> bytes:
    current_size = 0  # Track size of the data read
    buffer = b""  # Initialize buffer to store received bytes

    # Read bytes until we hit the max number of digits or encounter a newline
    while current_size < MAX_DIGITS:
        data = current_socket.recv(1)  # Receive one byte from the client
        if data == b"" or data == b"\n":  # If empty or newline, return buffer
            return buffer
        buffer = buffer + data  # Append received byte to buffer
        current_size = current_size + len(data)  # Update the total size read

    # If we reach here, the number was too big (more than MAX_DIGITS).
    # Raise an error to indicate the input is invalid.
    raise ValueError("newline not found")


# Function to handle communication with a single client
def contact_client(client_socket: socket) -> None:
    global ol  # Allow function to modify the global sum variable

    try:
        # Ensure the client socket is closed after interaction
        with client_socket:
            # Read the input message (up to MAX_DIGITS or until newline)
            # Look to the get_line function for more details
            local_msg = get_line(client_socket)
            if local_msg == b"":  # If input is empty, return without action
                return

            # Convert the input message to an integer
            print(f"Received: {local_msg}")
            val = int(local_msg)

            # Use lock to safely update the global sum
            # We do this 2 steps to avoid holding the lock for too long
            with lock:
                new_val = ol + val  # Calculate the new sum
                ol = new_val  # Update the global sum variable

            # Send the updated global sum back to the client
            client_socket.sendall(
                str(new_val).encode("utf-8")
                + b"\n"  # Encode sum as bytes and add newline
            )  # Send outside the lock to avoid blocking other threads
    except Exception as details:
        print(details)  # Print any exception that occurs for debugging


# Main server setup
with socket(AF_INET, SOCK_STREAM) as sock:
    # Configure socket to allow address reuse for quicker restarts
    sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    # Bind the socket to the specified host and port
    sock.bind((HOST, PORT))
    # Begin listening for incoming connections
    sock.listen(NUM_CLIENTS)

    # Main loop to accept and handle incoming connections
    while True:
        sc, _ = sock.accept()  # Accept a new client connection
        # Start a new thread to handle each client connection
        Thread(target=contact_client, args=(sc,)).start()
