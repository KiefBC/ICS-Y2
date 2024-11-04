#!/usr/bin/python3

from socket import AF_INET, SOCK_STREAM, socket
from sys import argv

BUF_SIZE = 1024
HOST = "127.0.0.1"
PORT = 12345


def main():
    if len(argv) != 2:
        print(f"{argv[0]} Message?")
        exit(1)

    with socket(AF_INET, SOCK_STREAM) as sock:  # TCP socket
        sock.connect((HOST, PORT))  # Connect to the server
        print(f"Connected to {HOST}:{PORT}")
        print(f"Client: {sock.getsockname()}")

        data = argv[1].encode("utf-8")
        sock.sendall(data)  # Send the message to the server
        print(f"Sent data: {argv[1]} to {HOST}:{PORT}")

        reply = sock.recv(BUF_SIZE)  # Receive data from the server
        print(f"Reply: {reply}")


if __name__ == "__main__":
    main()
