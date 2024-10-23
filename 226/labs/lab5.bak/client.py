import socket
import struct


def recv_exact(sock, num_bytes):
    """Receive exactly num_bytes bytes from the socket."""
    data = b''
    while len(data) < num_bytes:
        packet = sock.recv(num_bytes - len(data))
        if not packet:
            return None  # Connection closed
        data += packet
    return data


def send_player_name(sock, player_name):
    """Send the player's name length (packed) followed by the player name."""
    # First send the length of the player's name as an unsigned short (2 bytes)
    name_length_data = struct.pack('!H', len(player_name))
    sock.sendall(name_length_data)

    # Then send the player name itself
    sock.sendall(player_name.encode('utf-8'))


def main():
    server_address = ('localhost', 12345)

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(server_address)

            # Receive the length of the player name
            name_length_data = recv_exact(sock, 2)
            if not name_length_data:
                print("Failed to receive player name length.")
                return
            name_length = struct.unpack('!H', name_length_data)[0]

            # Receive the player name
            player_name_data = recv_exact(sock, name_length)
            if not player_name_data:
                print("Failed to receive player name.")
                return
            player_name = player_name_data.decode('utf-8')
            print(f"Your player name is: {player_name}")

            while True:
                try:
                    # Prompt for row and column
                    row = int(input("Enter the row: "))
                    col = int(input("Enter the column: "))

                    # Pack and send row and column
                    move_data = struct.pack('!HH', row, col)
                    sock.sendall(move_data)

                    # Receive the response from the server
                    response = recv_exact(sock, 2)
                    if not response:
                        print("Server closed connection.")
                        break

                    # Unpack and process the response (whatever the server sends)
                    result = struct.unpack('!HH', response)
                    print(f"Response: {result}")

                except (ValueError, struct.error) as e:
                    print(f"Error: {e}")

    except ConnectionError as e:
        print(f"Connection error: {e}")


if __name__ == "__main__":
    main()
