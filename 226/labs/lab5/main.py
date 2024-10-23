import socket
import struct
import threading
from Board import Board
from Player import Player

# Constants
BUF_SIZE = 2
HOST = ''
PORT = 12345
BOARD_SIZE = 10
TREASURE_AMT = 5
MAX_CONNECTIONS = 2

# Shared variables
active_connections = 0
lock = threading.Lock()
players = {}  # To keep track of player scores

def handle_client(client_socket, client_address, board, player_id):
    global active_connections
    try:
        # Send player name to client
        with lock:
            player_name = f"Player {player_id}"
            name_length = struct.pack('!H', len(player_name))
            client_socket.sendall(name_length)
            client_socket.sendall(player_name.encode('utf-8'))
            print(f"Sent player name '{player_name}' to {client_address}")

        while True:
            # Receive row and column as packed unsigned shorts
            move_data = client_socket.recv(4)
            if len(move_data) < 4:
                print(f"Client {client_address} disconnected.")
                break
            row, col = struct.unpack('!HH', move_data)
            print(f"Received move from {client_address} - Row: {row}, Col: {col}")

            # Update the board and player's score
            with lock:
                # Update score logic as per your game rules
                current_score = players[player_id].get_score()
                new_score = current_score + 1  # Example increment
                players[player_id].set_score(new_score)

                # Get opponent's score
                opponent_id = 1 if player_id == 2 else 2
                opponent_score = players[opponent_id].get_score() if opponent_id in players else 0

            # Send back the player's score and opponent's score
            reply = struct.pack('!HH', new_score, opponent_score)
            client_socket.sendall(reply)

    except Exception as e:
        print(f"Error handling client {client_address}: {e}")
    finally:
        client_socket.close()
        with lock:
            active_connections -= 1
            print(f"Connection with {client_address} closed. Active connections: {active_connections}")

def main():
    global active_connections

    # Initialize game board
    board = Board(BOARD_SIZE, TREASURE_AMT)

    print("Creating game Board...")
    print(board)

    # Set up the server socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind((HOST, PORT))
        server_socket.listen(MAX_CONNECTIONS)
        print(f'Server listening on port {PORT}')

        while True:
            print('Waiting for a connection...\n')
            client_socket, client_address = server_socket.accept()

            # Enforce connection limit with a lock
            with lock:
                if active_connections >= MAX_CONNECTIONS:
                    print(f"Rejecting connection from {client_address}. Max connections reached.")
                    client_socket.close()
                    continue

                active_connections += 1
                player_id = active_connections
                players[player_id] = Player(f"Player {player_id}")
                print(f"Accepted connection from {client_address}. Assigned as Player {player_id}. Active connections: {active_connections}")

            # Create a new thread for each client
            client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address, board, player_id))
            client_thread.start()

if __name__ == "__main__":
    main()
