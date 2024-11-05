from socket import AF_INET, SOCK_DGRAM, socket

BUF_SIZE = 1024
PORT = 12345
HOST = "127.0.0.1"


def main():
    while True:
        with socket(AF_INET, SOCK_DGRAM) as sock:  # UDP socket
            sock.bind((HOST, PORT))  # Bind the socket to the address and port
            print(f"Listening on {HOST}:{PORT}\n")

            # Receive data from the socket
            # addr can also be written as: (ip, port)
            data, addr = sock.recvfrom(BUF_SIZE)
            print(f"Received data: {data.decode()} from {addr}")

            # Decode the data and print it
            text = data.decode("utf-8")
            # We did this above with the addr variable
            source_ip, source_port = addr
            print(f"Source IP: {source_ip}\nSource Port: {source_port}\nData: {text}\n")


if __name__ == "__main__":
    main()
