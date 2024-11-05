#!/usr/bin/python3

from socket import AF_INET, SOCK_STREAM, socket
from sys import argv

PORT = 65432
HOST = ""  # localhost


def main():
    if len(argv) != 2:
        print(f"{argv[0]} - Where is your message?")
        exit(1)

    with socket(AF_INET, SOCK_STREAM) as sock:
        sock.connect((HOST, PORT))
        print(f"Connected to {HOST}:{PORT}")
        print(
            f"Client: {sock.getsockname()}"
        )  # getsockname() returns the socket's own address

        data = argv[1].encode("utf-8")
        print(f"Sending data: '{argv[1]}' to {HOST}:{PORT}")

        sock.sendall(data)

        reply = sock.recv(1024)
        print(f"Reply from server: {reply.decode()}")


if __name__ == "__main__":
    main()
