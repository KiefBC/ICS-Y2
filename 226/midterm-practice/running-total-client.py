#!/usr/bin/python3

from socket import AF_INET, SOCK_STREAM, socket
from struct import pack, unpack
from sys import argv

PORT = 12345
HOST = ""  # Connect to localhost


def main():
    if len(argv) != 2:
        print(f"Usage: {argv[0]} <number of runs>")
        print("Example: python running-total-client.py 5")
        exit(1)

    try:
        runs = int(argv[1])
        if runs < 1:
            raise ValueError
    except ValueError:
        print("The number of runs must be a positive integer")
        exit(1)

    # Create a socket
    with socket(AF_INET, SOCK_STREAM) as sock:
        # Connect to the server
        sock.connect((HOST, PORT))
        print(f"Connected to the server at {HOST}:{PORT}\n")

        # Send the number of runs to the server
        data = pack("!H", runs)
        sock.sendall(data)
        print(f"Sent the number of runs: {runs}")

        # Receive the total number of runs from the server
        response = b""
        while len(response) < 2:
            chunk = sock.recv(2 - len(response))
            if not chunk:
                break
            response += chunk

        if len(response) == 2:
            # Unpack the total number of runs
            total_runs = unpack("!H", response)[0]
            print(f"Total runs: {total_runs}")


if __name__ == "__main__":
    main()
