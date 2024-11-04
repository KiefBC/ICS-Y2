#!/usr/bin/env python3

from socket import AF_INET, SOCK_DGRAM, socket
from sys import argv

BUF_SIZE = 1024
HOST = "127.0.0.1"
PORT = 12345


def main():
    if len(argv) != 2:
        print(f"{argv[0]} Message?")
        exit(1)

    with socket(AF_INET, SOCK_DGRAM) as sock:
        # This sends the message to the server
        sock.sendto(argv[1].encode(), (HOST, PORT))
        print(f"sent data: {argv[1]} to {HOST}:{PORT}")
        print(f"sent data: {argv[0]} to {HOST}:{PORT}")


if __name__ == "__main__":
    main()
