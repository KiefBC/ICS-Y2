import socket

# Server configuration
HOST = (
    "127.0.0.1"  # Localhost (change to '0.0.0.0' to listen on all network interfaces)
)
PORT = 12345  # Port number to listen on

# Step 1: Create a TCP socket
# AF_INET is for IPv4, SOCK_STREAM indicates TCP
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Step 2: Bind the socket to the address and port
server_socket.bind((HOST, PORT))

# Step 3: Start listening for incoming connections
server_socket.listen(1)  # Allows one connection in the queue (can increase if needed)
print(f"Server is listening on {HOST}:{PORT}...")

# Step 4: Accept a single client connection
client_socket, client_address = server_socket.accept()
print(f"Connected to client at {client_address}")

# Step 5: Receive and send data (simple echo server)
try:
    while True:
        # Receive data from the client
        data = client_socket.recv(1024)  # Receives up to 1024 bytes
        if not data:
            break  # Exit if no data is received (client has closed the connection)

        print(f"Received data: {data.decode()}")

        # Send the same data back to the client (echo)
        client_socket.sendall(data)

finally:
    # Step 6: Close the client and server sockets
    client_socket.close()
    server_socket.close()
    print("Connection closed")
