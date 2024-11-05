#!/usr/bin/python3

import struct
from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket

PORT = 12345
HOST = ""  # Listen on all interfaces


def main():
    total_runs = 0  # Total number of runs

    # Create a socket
    with socket(AF_INET, SOCK_STREAM) as sock:
        # Set the SO_REUSEADDR option to allow the server to bind to a previously used address
        sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

        # Bind the socket to the address and port
        sock.bind((HOST, PORT))

        # Listen for incoming connections
        sock.listen(1)

        while True:
            # Accept a connection and get the client socket
            conn, addr = sock.accept()

            with conn:
                print(f"Connected by {addr}\n")

                # Read the number of runs from the client
                data = b""
                while len(data) < 2:
                    chunk = conn.recv(2 - len(data))
                    if not chunk:
                        break
                    data += chunk

                if len(data) == 2:
                    # Unpack the number of runs
                    runs = struct.unpack("!H", data)[0]
                    print(f"Number of runs: {runs}")

                    # Increment the total number of runs
                    total_runs += runs
                    print(f"Total runs: {total_runs}\n")

                    # Send the total number of runs back to the client
                    response = struct.pack("!H", total_runs)
                    conn.sendall(response)


if __name__ == "__main__":
    main()
