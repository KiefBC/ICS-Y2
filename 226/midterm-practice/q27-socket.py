import socket
from struct import pack, unpack

"""
Write a TCP server listening on port 12345 that expects an unsigned byte x,
followed by a 1-byte operator '+' or '*', followed by another packed byte y. The
server must then compute x + y (if the operator was a +) or x * y (if the operator was
a y) and return the result as an unsigned short, followed by a newline. For example,
sending 1+2 returns 3 and sending 3*4 returns 12. You can use the following to test
your program:

echo '012b02' | xxd -r -p | nc 127.0.0.1 12345 | xxd -p
This sends over byte 01, the + character (represented by ASCII 2b), and byte 02.
The result should be 00030a (0a here is the newline)
echo '032a04' | xxd -r -p | nc 127.0.0.1 12345 | xxd -p
This sends over byte 03, the * character (represented by ASCII 2a), and byte 04.
The result should be 000c0a (the c is hexadecimal for 12, and the 0a is the newline)
echo 'ff2aff' | xxd -r -p | nc 127.0.0.1 12345 | xxd -p
This computes 255*255 and should result in fe010a (which is hexadecimal for
65025)
"""

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
