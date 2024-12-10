from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Lock, Thread

HOST = ""  # Empty string means server will listen on all available interfaces
PORT = 12345  # Port number for the server (must be > 1024 unless root)
SERVER = (HOST, PORT)
SERVER_RUNNING = True  # Global flag to control server shutdown

# Shared Resources
message_lock = Lock()
client_lock = Lock()
client_id = 0
client_list = []

def get_message(local_socket: socket) -> bytes:
    local_socket.send(b"Message: ")
    buffer = b''
    while True:
        received_data = local_socket.recv(1)
        if received_data in [b'', b'\n']:
            return buffer
        buffer += received_data

def handle_client(local_socket: socket, local_id: int):
    global client_id
    try:
        with local_socket:
            while SERVER_RUNNING:
                message = get_message(local_socket)
                if not message:
                    with client_lock:
                        client_id -= 1
                        client_list.remove(local_socket)  # Remove client safely
                    break
                with message_lock:
                    print(f"[Client {local_id}] Message Received: {message.decode()}")
    except Exception as e:
        with client_lock:
            if local_socket in client_list:
                client_list.remove(local_socket)
    finally:
        local_socket.close()

def main():
    global client_id, client_list
    try:
        with socket(AF_INET, SOCK_STREAM) as sc:
            sc.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
            sc.bind(SERVER)
            sc.listen(1)
            print("Server listening...\n")

            while SERVER_RUNNING:
                cs, addr = sc.accept()
                with client_lock:
                    local_id = client_id
                    client_id += 1
                    client_list.append(cs)
                    try:
                        cs.send(f"Welcome to the Server Chat, Client {local_id}\n\n".encode("utf-8"))
                    except Exception:
                        client_list.remove(cs)
                        continue

                Thread(target=handle_client, args=(cs, local_id), daemon=True).start()
    except KeyboardInterrupt:
        print("\nServer Shutdown...")
        with client_lock:
            for client in client_list[:]:  # Create a copy of the list to iterate
                try:
                    client.close()
                except Exception:
                    pass
            client_list.clear()
    finally:
        print("All Connectioned Closed.")

if __name__ == "__main__":
    main()