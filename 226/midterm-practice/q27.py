import socket
from struct import pack, unpack

HOST = "0.0.0.0"  # Listen on all network interfaces
PORT = 12345  # Port number to listen on
NUM_CONNECTIONS = 5  # Number of connections to queue

# Create a TCP/IP socket
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
    # Set socket options to allow address reuse
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    # Bind the socket to the address and port
    sock.bind((HOST, PORT))
    # Listen for incoming connections
    sock.listen(NUM_CONNECTIONS)
    while True:
        # Wait for a connection
        sc, _ = sock.accept()
        with sc:
            # Receive 1 byte for x
            xr = sc.recv(1)
            if not xr:
                continue
            # Receive 1 byte for the operator
            opr = sc.recv(1)
            if not opr:
                continue
            # Receive 1 byte for y
            yr = sc.recv(1)
            if not yr:
                continue
            # Unpack x as an unsigned byte
            (x,) = unpack("!B", xr)
            # Decode the operator from bytes to string
            op = opr.decode()
            # Unpack y as an unsigned byte
            (y,) = unpack("!B", yr)
            print(x, op, y)  # Print the received values for debugging
            if op == "+":
                # Compute x + y and send as unsigned short
                sc.sendall(pack("!H", x + y))
            elif op == "*":
                # Compute x * y and send as unsigned short
                sc.sendall(pack("!H", x * y))
            else:
                # Handle invalid operator
                sc.sendall(b"Invalid operator\n")
                continue
            # Send a newline character to signify end of response
            sc.sendall(b"\n")
