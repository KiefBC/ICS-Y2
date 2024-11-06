from random import randint
from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Semaphore, Thread

"""
Write a multithreaded Python server that guesses a random number between 1 and
100 (you can use random.randint(1, 100) from the random library); listens on port
12345; accepts an arbitrary number of clients; let's them know their ID; repeatedly
reads in the guesses from the clients, who send the number as a newline-
terminated string; lets the clients know whether or not they correctly guessed the
number, and if so, if they were the first. The server should not crash. You can use
nc localhost 12345 to mimic a client connecting to a server on local port 12345.
"""

# Server configuration
HOST = ""  # Bind to all available network interfaces
PORT = 12345  # Port number to listen on
MIN = 1  # Minimum number in the guessing range
MAX = 100  # Maximum number in the guessing range
NUM_CLIENTS = 1  # Number of clients expected

# Generate a random target number for clients to guess
r = randint(MIN, MAX)
print(f"Target number (for debugging): {r}")

# Shared variables for managing guesses
lock = Semaphore()  # Semaphore for synchronized access to the winner variable
winner = 0  # Tracks the ID of the first player who guessed correctly


# Function to read a newline-terminated line from the client
def get_line(current_socket: socket) -> bytes:
    buffer = b""  # Initialize buffer to accumulate bytes received from the client
    while True:
        data = current_socket.recv(1)  # Read 1 byte at a time from the client
        if data == b"" or data == b"\n":  # End of message or client disconnected
            return buffer
        buffer += data  # Append each byte to the buffer


# Function to handle communication with a single client
def contact_player(client: socket, player_id: int) -> None:
    global lock, r, winner

    # Ensure socket is closed after interaction
    with client:
        # Send a welcome message with the player ID
        client.sendall(f"Hello Player {player_id}\n".encode())

        while True:
            try:
                # Read the guess from the client
                number = int(get_line(client))
                found = False  # Flag to track if the guess was correct
                found_first = False  # Flag to check if this client guessed first

                # Lock to ensure thread-safe access to the winner variable
                with lock:
                    if number == r:
                        found = True
                        # Check if this is the first correct guess
                        if winner == 0:
                            found_first = True
                            winner = player_id  # Record the ID of the first player to guess correctly

                # Sending responses outside the lock to avoid delays in critical section
                if found_first:
                    client.sendall(b"You won!\n")  # Inform the first correct guesser
                elif found:
                    client.sendall(
                        b"You got it!\n"
                    )  # Inform correct guessers after the first
                    client.sendall(
                        f"Player {winner} was the first to guess correctly.\n".encode()
                    )
                else:
                    client.sendall(b"No\n")  # Inform incorrect guessers

            except ValueError:
                # Handle non-integer inputs by ignoring them and prompting for another guess
                continue


# Main server setup
with socket(AF_INET, SOCK_STREAM) as sock:
    # Configure socket to allow address reuse for quicker restarts
    sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    # Bind the socket to the specified host and port
    sock.bind((HOST, PORT))
    # Start listening for incoming connections
    sock.listen(NUM_CLIENTS)

    num_players = 1  # Counter for connected players

    while True:
        # Accept a new player connection
        sc, _ = sock.accept()

        # Start a new thread to handle the player
        Thread(
            target=contact_player,
            args=(
                sc,
                num_players,
            ),
        ).start()

        # Increment the player counter for unique player IDs
        num_players += 1
