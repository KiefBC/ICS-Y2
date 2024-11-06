#!/usr/bin/python3

from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket

PORT = 65432
HOST = ""  # localhost


def main():
    print("Starting server....")

    with socket(AF_INET, SOCK_STREAM) as sock:
        sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        sock.bind((HOST, PORT))
        sock.listen(1)
        print(f"Server is listening on port {PORT}")
        print(f"Server is running on {HOST}\n")

        # Repeatedly accept connections
        while True:
            conn, addr = sock.accept()
            with conn:
                print(f"Connected by {addr}")
                data = conn.recv(1)
                print(f"Received {data} from client\n")

                if data:
                    # Get the byte data
                    byte_value = data[0]  # [0] is the first byte
                    if byte_value & 0xF0 == 0xF0:
                        print("Notification:: The first 4 bits are all 1's")

                        # Notify client
                        reply = "The first 4 bits are all 1's".encode("utf-8")
                        conn.sendall(reply)
                    else:
                        print("Notification:: The first 4 bits are not all 1's")

                        # Notify client
                        reply = "The first 4 bits are not all 1's".encode("utf-8")
                        conn.sendall(reply)
                else:
                    print("No data received from client")
                    reply = "No data received".encode("utf-8")
                    conn.sendall(reply)


if __name__ == "__main__":
    main()
