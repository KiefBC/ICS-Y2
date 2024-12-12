import asyncio

# from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
# from threading import Lock, Thread

HOST = ""  # Empty string means server will listen on all available interfaces
PORT = 12345  # Port number for the server (must be > 1024 unless root)
SERVER = (HOST, PORT)
SERVER_RUNNING = True  # Global flag to control server shutdown

# # Shared Resources - Not needed in async version
# message_lock = Lock()
# client_lock = Lock()
client_id = 0
client_list = []  # Will store (reader, writer) pairs instead of raw sockets


async def get_message(
    reader: asyncio.StreamReader, writer: asyncio.StreamWriter
) -> bytes:
    """Async version of message retrieval"""
    writer.write(b"Message: ")
    await writer.drain()
    return await reader.readline()


# Old threaded version
# def get_message(local_socket: socket) -> bytes:
#     local_socket.send(b"Message: ")
#     buffer = b''
#     while True:
#         received_data = local_socket.recv(1)
#         if received_data in [b'', b'\n']:
#             return buffer
#         buffer += received_data


async def handle_client(
    reader: asyncio.StreamReader, writer: asyncio.StreamWriter, local_id: int
):
    """Async version of client handler"""
    global client_id
    try:
        while SERVER_RUNNING:
            message = await get_message(reader, writer)
            if not message:
                client_list.remove((reader, writer))
                client_id -= 1
                break
            print(f"[Client {local_id}] Message Received: {message.decode()}")
    except Exception:
        if (reader, writer) in client_list:
            client_list.remove((reader, writer))
    finally:
        writer.close()
        await writer.wait_closed()


# Old threaded version
# def handle_client(local_socket: socket, local_id: int):
#     global client_id
#     try:
#         with local_socket:
#             while SERVER_RUNNING:
#                 message = get_message(local_socket)
#                 if not message:
#                     with client_lock:
#                         client_id -= 1
#                         client_list.remove(local_socket)
#                     break
#                 with message_lock:
#                     print(f"[Client {local_id}] Message Received: {message.decode()}")
#     except Exception as e:
#         with client_lock:
#             if local_socket in client_list:
#                 client_list.remove(local_socket)
#     finally:
#         local_socket.close()


async def handle_new_connection(
    reader: asyncio.StreamReader, writer: asyncio.StreamWriter
):
    """Handler for new client connections"""
    global client_id
    local_id = client_id
    client_id += 1
    client_list.append((reader, writer))

    try:
        writer.write(
            f"Welcome to the Server Chat, Client {local_id}\n\n".encode("utf-8")
        )
        await writer.drain()
    except Exception:
        client_list.remove((reader, writer))
        return

    await handle_client(reader, writer, local_id)


async def main():
    """Async main server function"""

    def shutdown_handler():
        """Handle graceful shutdown"""
        global SERVER_RUNNING
        SERVER_RUNNING = False
        for reader, writer in client_list:
            writer.close()
        client_list.clear()

    try:
        server = await asyncio.start_server(
            handle_new_connection, host=HOST, port=PORT, reuse_address=True
        )

        print("Server listening...\n")

        async with server:
            await server.serve_forever()
    except KeyboardInterrupt:
        print("\nServer Shutdown...")
        shutdown_handler()


# Old threaded version
# def main():
#     global client_id, client_list
#     try:
#         with socket(AF_INET, SOCK_STREAM) as sc:
#             sc.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
#             sc.bind(SERVER)
#             sc.listen(1)
#             print("Server listening...\n")
#
#             while SERVER_RUNNING:
#                 cs, addr = sc.accept()
#                 with client_lock:
#                     local_id = client_id
#                     client_id += 1
#                     client_list.append(cs)
#                     try:
#                         cs.send(f"Welcome to the Server Chat, Client {local_id}\n\n".encode("utf-8"))
#                     except Exception:
#                         client_list.remove(cs)
#                         continue
#
#                 Thread(target=handle_client, args=(cs, local_id), daemon=True).start()
#     except KeyboardInterrupt:
#         print("\nServer Shutdown...")
#         with client_lock:
#             for client in client_list[:]:
#                 try:
#                     client.close()
#                 except Exception:
#                     pass
#             client_list.clear()

if __name__ == "__main__":
    asyncio.run(main())  # Use asyncio.run() instead of direct main() call

