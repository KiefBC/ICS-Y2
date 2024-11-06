import socket
import struct

HOST = "localhost"
PORT = 12345


def send_short_and_receive_total(number):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        sock.connect((HOST, PORT))

        # Send the number as an unsigned short (2 bytes)
        sock.sendall(struct.pack("!H", number))

        # Receive the total as an unsigned long long (8 bytes)
        data = sock.recv(8)
        if len(data) == 8:
            total = struct.unpack("!Q", data)[0]
            print(f"Sent {number}, received running total: {total}")
        else:
            print("Invalid response from server")


# Example usage
send_short_and_receive_total(10)
send_short_and_receive_total(20)
