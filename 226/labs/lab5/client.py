import socket
import struct

import Board


def send_player_name(sock, player_name):
    """Send the player's name length (packed) followed by the player name."""
    # First send the length of the player's name as an unsigned short (2 bytes)
    name_length = struct.pack('!H', len(player_name))
    sock.sendall(name_length)
    sock.sendall(player_name.encode('utf-8'))

def main():
    server_address = ('localhost', 12345)

    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect(server_address)

            # Receive the length of the player name
            name_length_data = sock.recv(2)
            if len(name_length_data) < 2:
                print("Failed to receive player name length.")
                return
            name_length = struct.unpack('!H', name_length_data)[0]

            # Receive the player name
            player_name_data = sock.recv(name_length)
            if len(player_name_data) < name_length:
                print("Failed to receive player name.")
                return
            player_name = player_name_data.decode('utf-8')
            print(f"Your player name is: {player_name}")

            while True:
                try:
                    row = int(input("Enter the row: "))
                    col = int(input("Enter the column: "))
                    segment = (row << 4) | col
                    move_data = struct.pack('!B', segment)
                    sock.sendall(move_data)

                    # row = int(input("Enter the row: "))
                    # col = int(input("Enter the column: "))
                    #
                    # # Pack and send row and column
                    # move_data = struct.pack('!H', row, col)
                    # sock.sendall(move_data)

                    response = sock.recv(4)
                    if len(response) < 4:
                        print("Server closed the connection.")
                        break

                    # Unpack the server's response
                    player_score, opponent_score = struct.unpack('!HH', response)
                    print(f"Player Score: {player_score}, Opponent Score: {opponent_score}")

                except Exception as e:
                    print(f"Error: {e}")
                    break

    except ConnectionError as e:
        print(f"Connection failed: {e}")

if __name__ == "__main__":
    main()
