import socket
from threading import Thread

# Server configuration
HOST = "127.0.0.1"  # Localhost
PORT = 12345  # Port number to listen on


# Step 1: Define a function to handle each client connection
def handle_client(client_socket, client_address):
    print(f"New connection from {client_address}")
    try:
        while True:
            # Receive data from the client
            data = client_socket.recv(1024)
            if not data:
                break  # Exit if no data is received (client has closed the connection)

            print(f"Received from {client_address}: {data.decode()}")

            # Echo the data back to the client
            client_socket.sendall(data)

    finally:
        # Close the client connection
        client_socket.close()
        print(f"Connection to {client_address} closed")


# Step 2: Create the main server socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()  # Allows multiple connections in the queue
print(f"Server is listening on {HOST}:{PORT}...")

try:
    while True:
        # Step 3: Accept new client connections
        client_socket, client_address = server_socket.accept()

        # Step 4: Create a new thread for each client connection
        # Pass the client socket and address to the handler function
        client_thread = Thread(
            target=handle_client, args=(client_socket, client_address)
        )
        client_thread.start()  # Start the thread

finally:
    # Step 5: Close the server socket (only runs if the server is stopped)
    server_socket.close()
    print("Server shut down")
