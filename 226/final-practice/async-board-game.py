import asyncio
import random

HOST = ""
PORT = 12345
SERVER_RUNNING = True

# Game state
BOARD_SIZE = 4
board = [[0 for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)]
target_row = random.randint(0, BOARD_SIZE - 1)
target_col = random.randint(0, BOARD_SIZE - 1)

def print_board():
    """Print the current state of the board"""
    for row in board:
        print(" ".join(str(cell) for cell in row))
    print()

# Set the target position
board[target_row][target_col] = 1

async def validate_guess(guess: str) -> tuple[bool, int, int]:
    """Validate the guess format and values"""
    try:
        if len(guess.strip()) != 3:  # Format should be "r c\n"
            return False, -1, -1
            
        row, col = map(int, guess.strip().split())
        
        if not (0 <= row < BOARD_SIZE and 0 <= col < BOARD_SIZE):
            return False, -1, -1
            
        return True, row, col
    except ValueError:
        return False, -1, -1

async def handle_client(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    """Handle a single client connection"""
    try:
        while SERVER_RUNNING:
            # Prompt client for guess
            writer.write("GO\n".encode())
            await writer.drain()
            
            # Get guess from client
            data = await reader.readline()
            if not data:
                break
                
            # Validate guess
            valid, row, col = await validate_guess(data.decode())
            
            if not valid:
                writer.write("NO\n".encode())
                await writer.drain()
                continue
                
            # Check if guess is correct
            if row == target_row and col == target_col:
                writer.write("OK\n".encode())
                await writer.drain()
                break
            else:
                writer.write("NO\n".encode())
                await writer.drain()
                
    except Exception as e:
        print(f"Client error: {e}")
    finally:
        writer.close()
        await writer.wait_closed()

async def main():
    try:
        # Print initial board state
        print("Game Board:")
        print_board()
        print(f"Target position: ({target_row}, {target_col})")
        
        server = await asyncio.start_server(
            handle_client,
            host=HOST,
            port=PORT,
            reuse_address=True
        )
        
        print(f"Server running on {HOST}:{PORT}")
        
        async with server:
            await server.serve_forever()
            
    except KeyboardInterrupt:
        print("\nServer shutting down...")
    except Exception as e:
        print(f"Server error: {e}")

if __name__ == "__main__":
    asyncio.run(main()) 