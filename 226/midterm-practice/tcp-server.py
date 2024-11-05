#!/usr/bin/python3

from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket

BUF_SIZE = 1024
PORT = 12345
HOST = ""  # localhost, 0.0.0.0 or "" are all the same


def main():
    with socket(AF_INET, SOCK_STREAM) as sock:  # TCP Socket
        # Allow the socket to be reused
        sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)  # 1 is True
        sock.bind((HOST, PORT))  # Bind the socket to the address and port
        sock.listen(
            1
        )  # Listen for incoming connections. 1 is the maximum number of queued connections
        print(f"Listening on {HOST}:{PORT}")
        print("Server: ", sock.getsockname())

        while True:
            conn, _ = sock.accept()  # Accept the connection
            with conn:
                print(f"Connected by {conn.getpeername()}")
                # recvfrom is not used because TCP is connection-oriented
                data = conn.recv(BUF_SIZE)  # Receive data from the socket
                print(f"Received data: {data.decode()} from {conn.getpeername()}")
                reply = "This is the server. I got your message.".encode("utf-8")
                conn.sendall(reply)  # Send the data back to the client


if __name__ == "__main__":
    main()
