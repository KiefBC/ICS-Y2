#!/usr/bin/python3

import socket
import struct
import threading

# Port and address for the server
HOST = ""  # Listen on all interfaces
PORT = 12345

# Shared running total
running_total = 0
total_lock = threading.Lock()


def handle_client(conn):
    global running_total
    try:
        # Read 2 bytes from the client (unsigned short)
        data = conn.recv(2)
        if len(data) != 2:
            print("Invalid data received. Expected 2 bytes.")
            return

        # Unpack the data as an unsigned short (H format code)
        received_number = struct.unpack("!H", data)[
            0
        ]  # ! for network byte order (big-endian)

        # Update the running total with thread safety
        with total_lock:
            running_total += received_number
            current_total = running_total

        # Send the updated total as an unsigned long long (Q format code)
        conn.sendall(struct.pack("!Q", current_total))  # ! for network byte order
        print(f"Received {received_number}, running total is {current_total}")

    except Exception as e:
        print(f"Error handling client: {e}")
    finally:
        conn.close()  # Close the connection with the client


def main():
    # Set up the server socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((HOST, PORT))
        server_socket.listen()
        print(f"Server listening on port {PORT}...")

        # Accept clients in a loop
        while True:
            conn, addr = server_socket.accept()
            print(f"Connected by {addr}")
            # Handle each client in a new thread
            client_thread = threading.Thread(target=handle_client, args=(conn,))
            client_thread.start()


if __name__ == "__main__":
    main()
