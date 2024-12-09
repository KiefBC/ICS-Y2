from random import randint
from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Lock, Thread

HOST = ""
PORT = 12345
SECRET_NUM = randint(1, 100)
MAX_GUESSES = 5
SERVER = (HOST, PORT)
SERVER_RUNNING = True
LOCK = Lock()
WINNER = False
FOUND_FIRST = False


def print_welcome():
    print("Welcome to the Numbr Guessing GAME!")
    print("I'm thinking of a number between 1 and 100.")
    print("Try to guess it in as few attempts as possible.")
    print("You have", MAX_GUESSES, "attempts.")
    print("=============================================")


def handle_client(client, client_id):
    global SERVER_RUNNING, WINNER, FOUND_FIRST
    guess_count = 0
    try:
        while SERVER_RUNNING and guess_count < MAX_GUESSES:
            # Send the client a prompt to enter a guess
            client.send(b"\nEnter your guess: ")
            guess = client.recv(1024).decode("utf-8").strip()
            if not guess:  # If the client sends an empty string,
                client.send(b"Please enter a number.\n")
                continue
            if not guess.isdigit():  # If the client sends a non-numeric string
                client.send(b"Please enter a valid number.\n")
                continue

            # Convert the guess to an integer
            guess = int(guess)
            guess_count += 1
            print(f"Client {client_id} guessed: ", guess)

            # Use the LOCK to synchronize access to the shared variables
            with LOCK:
                if guess_count == MAX_GUESSES and not WINNER:
                    client.send(b"Sorry, you are out of guesses.\n")
                    break

                if guess == SECRET_NUM:
                    WINNER = True
                    if not FOUND_FIRST:
                        client.send(b"Congratulations! You guessed the number!\n")
                        FOUND_FIRST = True
                else:
                    if guess < SECRET_NUM:
                        client.send(b"Try a higher number.\n")
                    else:
                        client.send(b"Try a lower number.\n")

    except Exception:
        print(f"Cient {client_id} has disconnected.")
    finally:  # If the client disconnects, close the connection
        print(f"Closing connection for client {client_id}.")
        client.close()


def main():
    global SECRET_NUM, SERVER_RUNNING
    client_id = 1
    print_welcome()
    print("The secret number is:", SECRET_NUM)
    try:
        with socket(AF_INET, SOCK_STREAM) as server_socket:
            # Allow Reuse of the Address to avoid "Address already in use"
            server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
            # Bind the server socket to the address and port
            server_socket.bind(SERVER)
            # Listen for incoming connections
            server_socket.listen()  # Add a number to limit connections
            print("Server is listening on port: ", PORT)

            while SERVER_RUNNING:
                client, address = server_socket.accept()

                print("Connection from: ", address)

                client.send(
                    f"You are Connected as Client {client_id}\n".encode("utf-8")
                )
                client.send(b"Welcome to the Number Guessing Game!\n")
                client.send(b"Can you guess the secret number?\n")

                # Create a new thread to handle the client
                client_thread = Thread(target=handle_client, args=(client, client_id))
                client_thread.start()
                client_id += 1
    except KeyboardInterrupt:
        print("\nServer is shutting down...")
        SERVER_RUNNING = False
    except Exception as e:
        print("An error occurred: ", e)


if __name__ == "__main__":
    main()
