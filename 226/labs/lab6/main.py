import asyncio
import struct
import traceback

from Board import Board
from Player import Player

# Constants
BUF_SIZE = 2
HOST = "0.0.0.0"
PORT = 12345
BOARD_SIZE = 10
TREASURE_AMT = 5
MAX_CONNECTIONS = 2

active_connections = 0
players = {}


async def handle_client(reader, writer, board, player_id):
    global active_connections
    try:
        # Send player name to client
        player_name = f"{'One' if active_connections == 1 else 'Two'}"
        name_length = struct.pack("!H", len(player_name))
        writer.write(name_length)
        writer.write(player_name.encode("utf-8"))
        writer.drain()
        print(f"Sent player name '{player_name}'")

        while True:
            # Receive row and column as packed unsigned shorts
            move_data = await reader.readexactly(1)
            segment = struct.unpack("B", move_data)[0]
            row = segment >> 4
            col = segment & 0xF

            print(f"Received move - Row: {row}, Col: {col}")

            # Handle game logic
            treasure_value = board.pick(row, col)
            current_score = players[player_id].get_score()
            new_score = current_score + (
                treasure_value if treasure_value is not None else 0
            )
            # players[player_id].add_score(new_score)
            players[player_id].add_score(
                treasure_value if treasure_value is not None else 0
            )

            # Get opponent's score
            opponent_id = 1 if player_id == 2 else 2
            opponent_score = (
                players[opponent_id].get_score() if opponent_id in players else 0
            )
            print(board)

            # Send back the player's score and opponent's score
            reply = struct.pack("!HH", new_score, opponent_score)
            writer.write(reply)
            await writer.drain()
    except asyncio.IncompleteReadError:
        print(f"Client {player_id} disconnected unexpectedly.")
    except Exception as e:
        print(f"Error handling client: {e}")
        print(traceback.format_exc())
    finally:
        await writer.drain()
        writer.close()
        await writer.wait_closed()
        active_connections -= 1
        print(f"Connection closed. Active connections: {active_connections}")


async def main():
    global active_connections

    board = Board(BOARD_SIZE, TREASURE_AMT)
    print(board)

    async def accept_client(reader, writer):
        global active_connections
        if active_connections >= MAX_CONNECTIONS:
            writer.close()
            await writer.wait_closed()
            return

        active_connections += 1
        player_id = active_connections
        players[player_id] = Player(f"Player {player_id}")
        print(
            f"Accepted connection. Assigned as Player {player_id}. Active connections: {active_connections}"
        )
        await handle_client(reader, writer, board, player_id)

    server = await asyncio.start_server(accept_client, HOST, PORT)
    print(f"Server listening on port {PORT}")

    async with server:
        await server.serve_forever()


if __name__ == "__main__":
    asyncio.run(main())
