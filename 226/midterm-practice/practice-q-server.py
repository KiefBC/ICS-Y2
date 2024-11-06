from socket import AF_INET, SOCK_STREAM, socket
from struct import pack, unpack
from sys import argv
from threading import Lock, Thread

HOST = ""
PORT = 12345

running_total = 0
total_lock = Lock()


def main():
    """
    This will be our main server file
    """
    # Step 1: Create a socket object
    with socket(AF_INET, SOCK_STREAM) as server:
        # Step 2: Bind the socket to the address and port
        server.bind((HOST, PORT))
        # Step 3: Listen for an incoming connection
        server.listen()
        print(f"Server listening on port {PORT}...\n")
        # Step 4: Accept the connection
        while True:
            conn, addr = server.accept()
            print(f"Connected by: {addr}\n")
            # Step 5: Handle each client in a new Thread
            client_thread = Thread(target=handle_client, args=(conn,))
            client_thread.start()


def handle_client(conn):
    # Step 1: Import global variables
    global running_total

    # Define the allowed bytes for filtering
    allowed_bytes = b"0123456789"
    try:
        # Step 2: Read 1 byte at a time from the client
        data = conn.recv(2)

        # Step 3: Check if the data is not empty
        if len(data) != 2:
            print("Invalid data received. Expected 1 byte.")
            return

        # Step 4: Unpack the data as an unsigned short (H format code)
        received_number = unpack("!H", data)[0]

        # Step 5: Update the running total with thread safety
        with total_lock:
            running_total += received_number
            current_total = running_total

        # Step 6: Read until newline and filter out unwanted characters
        filtered_data = read_until_newline(conn, allowed_bytes)

        # Step 7: Send the updated total and the filtered data back to the client
        # We send the b"\n" to indicate the end of the message
        print(f"Received {received_number}, running total is {current_total}\n")
        conn.sendall(pack("!Q", current_total) + filtered_data + b"\n")
    except Exception as e:
        print(f"Error handling client: {e}")
    finally:
        conn.close()


def read_until_newline(conn, allowed_bytes):
    """
    Read data from the connection until a newline character is received
    """
    result = b""
    while True:
        # Read 1 byte from the connection at a time
        data = conn.recv(1)

        # Stop reading if a newline character is received
        if data == b"\n":
            break

        # Add the data to the result if it is in the allowed bytes
        if data in allowed_bytes:
            result += data

    return result


if __name__ == "__main__":
    main()
