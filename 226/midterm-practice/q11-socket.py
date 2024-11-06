from socket import AF_INET, SOCK_STREAM, socket

BUF_SIZE = 1024
PORT = 24680
HOST = ""


def main():
    # Create a socket
    server = socket(family=AF_INET, type=SOCK_STREAM)
    # Bind the socket to the address and port
    server.bind((HOST, PORT))
    # Listen for incoming connections
    server.listen(1)
    print("Server is listening on port", PORT)

    while True:
        sock, addr = server.accept()  # Accept a connection
        with sock:
            data_from_client = sock.recv(BUF_SIZE)
            if not data_from_client:
                break

            total = 0

            try:
                for num in data_from_client.decode().split():
                    total += int(num)

                # reply = str(total).encode("utf-8")
                # sock.sendall(reply)

                second_reply = read_line(sock, total)
                sock.sendall(second_reply)
            except ValueError:
                sock.sendall(b"Invalid input\n")


def read_line(current_socket: socket) -> bytes:
    line = b""
    while True:
        char = current_socket.recv(1)
        if char == b"\n":
            break
        line += char
    return line


if __name__ == "__main__":
    main()
