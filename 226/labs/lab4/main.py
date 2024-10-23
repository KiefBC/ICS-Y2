from Board import Board
from Player import Player
from socket import socket, AF_INET, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR
from sys import argv
import struct

# dos2unix /home/kiefer/school/ICS-Y2/226/labs/lab3/226_lab3/bin/pytest
# dos2unix 226_lab3/bin/activate
# dos2unix /home/kiefer/school/ICS-Y2/226/labs/lab3/226_lab3/bin/pip
# dos2unix /home/kiefer/school/ICS-Y2/226/labs/lab3/226_lab3/bin/python3
# pytest-assume

def get_input(prompt, min_val=None, max_val=None):
    """
    Prompt the user for an integer within an optional range.
    """
    while True:
        user_input = input(prompt)
        try:
            user_input = int(user_input)
            if (min_val is not None and user_input < min_val) or (max_val is not None and user_input > max_val):
                range_msg = f" between {min_val} and {max_val}" if min_val is not None and max_val is not None else ""
                print(f"Please enter a valid integer{range_msg}.")
                continue
            return user_input
        except ValueError:
            print("Please enter a valid integer.")


def main():
    """
    Main function of the script.
    """

    BUF_SIZE = 1
    HOST = '127.0.0.1'
    PORT = 12345
    BOARD_SIZE = 10
    TREASURE_AMT = 5

    board = Board(BOARD_SIZE, TREASURE_AMT)
    player = Player("Player 1")

    print("Creating game Board...")
    print(f"Player: {player.name}\n")
    print(board)

    with socket(AF_INET, SOCK_STREAM) as sock:
        sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        sock.bind((HOST, PORT))
        sock.listen(1)
        print(f'Server Port: {PORT}')

        while True:
            print('Waiting on Server Connection...\n')
            client_socket, client_address = sock.accept()
            with client_socket:
                # print('Client: ', client_socket.getpeername())
                print(f'Client Connected: {client_address}')

                data = client_socket.recv(BUF_SIZE)
                if not data:
                    print('Eh, chico, there was no dayta brother')
                    continue

                # print(f'The Data: {data}')

                segment = struct.unpack('B', data)[0]
                # print(f'The Segment: {segment}')

                row = (segment >> 4) & 0xF
                column = segment & 0xF
                print(f'Row: {row}, Column: {column}')

                # print(f'{client_address[0]} {data.hex()} {row} {column}')

                if row >= BOARD_SIZE or column >= BOARD_SIZE:
                    print(f'Row or Column are out of Range: {row}, {column}!')
                    client_socket.close()
                    continue

                try:
                    user_value = board.pick(row, column)
                    if user_value:
                        print(
                            f'Found Treasure of Value: {user_value} at Row: {row} and Column: {column}\n')
                        player.add_score(user_value)
                    else:
                        print(
                            f'No treasure found at Row: {row} and Column: {column}')

                    # The Tests won't run with my win condition
                    # if not any(cell.isdigit() for row in board.grid for cell in row if cell != "-"):
                        # print("All Treasures have been found!")
                        # print(player)
                        # break
                except Exception as e:
                    print(f'Error: {e}')
                    client_socket.close()
                    continue

                print(board)

                reply = struct.pack('!HH', player.get_score(), 0)
                client_socket.sendall(reply)

                print(
                    f'Sent response to: {client_address[0]}.\nPlayer Score: {player.get_score()}\n')
                client_socket.close()


if __name__ == "__main__":
    main()
