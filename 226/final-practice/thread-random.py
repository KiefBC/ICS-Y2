import sys
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


def print_welcome():
    print("Welcome to the Numbr Guessing GAME!")
    print("I'm thinking of a number between 1 and 100.")
    print("Try to guess it in as few attempts as possible.")
    print("You have", MAX_GUESSES, "attempts.")
    print("=============================================")


def handle_client(client):
    global SERVER_RUNNING
    try:
        while SERVER_RUNNING:
            client.send(b"Enter your guess: ")
            guess = client.recv(1024).decode("utf-8").strip()
            if not guess:
                break
            if not guess.isdigit():
                client.send(b"Please enter a valid number.")
                continue

            # Convert the guess to an integer
            guess = int(guess)
            print("Client guessed: ", guess)

            # Lock the shared resource
            with LOCK:
                if guess < SECRET_NUM:
                    client.send(b"Try a higher number.\n")
                elif guess > SECRET_NUM:
                    client.send(b"Try a lower number.\n")
                else:
                    client.send(b"Congratulations! You guessed the number.\n")
                    break
    except KeyboardInterrupt:
        print("Server is shutting down...")
        SERVER_RUNNING = False
        sys.exit(0)


def main():
    print_welcome()
    print("The secret number is:", SECRET_NUM)

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

            with LOCK:
                print("Connection from: ", address)
                client.send(b"Welcome to the Number Guessing Game!")
                client.send(b"Can you guess the secret number?")

            # Create a new thread to handle the client
            client_thread = Thread(target=handle_client, args=(client,))
            client_thread.start()


if __name__ == "__main__":
    main()
