from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from struct import unpack

"""
Write a Python function called sum_bytes(socket). socket is a socket connection,
which may or may not be valid. Using socket, the function must first receive an
unsigned byte (call it n), followed by an unsigned 4-byte number (call it
payload_size), followed by the number of bytes indicated in payload_size (call it
payload). The function must then add up every nth byte in the payload and return
the result to the calling function. For all errors, False is returned. For example [1][2]
[65 66] returns 131 because 65 + 66 = 131; similarly, [2][20][65 66 ... 84] returns 740
because 65 + 67 + 69 + ... + 83 = 740. However, [80][20][65 66 ... 84][1] returns
False because 80 is larger than the number of bytes in the payload. Here are some
tests you can run from the command line to see if your server works:
echo -n '01000000024142' | xxd -r -p | nc -N 127.0.0.1 12345
Input: 1 2 65 66
Output: 131
echo -n '02000000144142434445464748494A4B4C4D4E4F5051525354' | xxd -r
-p | nc -N 127.0.0.1 12345
Input: 2 20 65 66 ... 84
Output: 740
echo -n '50000000144142434445464748494A4B4C4D4E4F5051525354' | xxd -r
-p | nc -N 127.0.0.1 12345
Input: 80 20 65 66 ... 84
Output: False
echo -n '01000000FF4142434445464748494A4B4C4D4E4F5051525354' | xxd -r
-p | nc -N 127.0.0.1 12345
Input: 1 255 65 66 ... 84
Output: False
"""


# Helper function to receive a specific number of bytes from the socket
def get_buf(current_socket: socket, expected_size: int) -> bytes:
    """
    Reads a specified number of bytes from the socket.

    :param current_socket: The socket from which to read.
    :param expected_size: The number of bytes to read from the socket.
    :return: The bytes read, or an empty byte string if the connection is closed.
    """
    current_size = 0
    buffer = b""  # Initialize an empty buffer to store received bytes
    while current_size < expected_size:
        # Calculate the number of bytes to request in each iteration
        requested_size = min(expected_size - current_size, BUF_SIZE)
        data = current_socket.recv(requested_size)  # Receive data from the socket

        # If no data is received, the connection may be closed
        if data == b"":
            break

        # Append received data to the buffer and update the current size
        buffer += data
        current_size += len(data)

    return buffer


# Main function to sum specific bytes in the payload received from the socket
def sum_bytes(s: socket) -> bool | int:
    """
    Receives data from a socket and sums every nth byte in a payload.

    The function expects the following structure in the socket stream:
    - An unsigned byte (offset `n`)
    - An unsigned 4-byte integer (payload size)
    - `payload_size` number of bytes (the payload itself)

    :param s: The socket from which to read data.
    :return: The sum of every nth byte in the payload or False if an error occurs.
    """
    try:
        # Step 1: Read the offset (n) from the socket
        offset = unpack("!B", get_buf(s, 1))[0]  # '!B' denotes an unsigned byte
        # Step 2: Read the payload size (4 bytes) from the socket
        payload_size = unpack("!I", get_buf(s, 4))[
            0
        ]  # '!I' denotes an unsigned 4-byte integer

        # Validate the offset
        # The offset must be positive and cannot exceed the payload size
        if offset == 0 or offset > payload_size:
            return False

        # Step 3: Read the payload based on the payload_size
        payload = get_buf(s, payload_size)

        # Check if the entire payload was received
        if payload_size != len(payload):
            return False

        # Step 4: Sum every nth byte in the payload, based on the offset
        val = 0  # Initialize sum accumulator
        for i in range(0, payload_size, offset):
            val += payload[i]  # Add the byte at each nth position to the sum

        return val  # Return the total sum of the selected bytes
    except Exception as details:
        # Print exception details for debugging if an error occurs
        print(details)
        return False  # Return False if any error occurs during processing


# Server setup to accept incoming connections and test `sum_bytes`
HOST = "127.0.0.1"
PORT = 12345
NUM_CONNECTIONS = 1  # Maximum number of queued connections
BUF_SIZE = 1024  # Buffer size for reading data from the socket

# Set up the server to listen for incoming connections
with socket(AF_INET, SOCK_STREAM) as sock:
    # Configure the socket to allow immediate reuse of the address and port
    sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    sock.bind((HOST, PORT))  # Bind the socket to the specified address and port
    sock.listen(NUM_CONNECTIONS)  # Start listening for incoming connections
    print(f"Server listening on {HOST}:{PORT}...")

    while True:
        # Accept a new client connection
        sc, _ = sock.accept()
        with sc:
            # Call `sum_bytes` function on the client connection and print the result
            print(sum_bytes(sc))
