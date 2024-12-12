import asyncio
import random

HOST = ""
PORT = 12345
SERVER_RUNNING = True

# Game state
SECRET_NUMBER = random.randint(0, 9)
client_list = []  # List of (reader, writer) pairs
current_turn = 0
turn_lock = asyncio.Lock()  # For managing turns


async def handle_client(
    reader: asyncio.StreamReader, writer: asyncio.StreamWriter, client_id: int
):
    global current_turn, SERVER_RUNNING

    try:
        while SERVER_RUNNING:
            # Wait for this client's turn
            async with turn_lock:
                if current_turn != client_id:
                    continue

                # Signal client it's their turn
                writer.write("GO!\n".encode())
                await writer.drain()

                # Get guess from client
                data = await reader.readline()
                if not data:
                    break

                try:
                    guess = int(data.decode().strip())

                    if guess == SECRET_NUMBER:
                        # Winner
                        writer.write("WIN\n".encode())
                        await writer.drain()

                        # Notify other clients of loss
                        for r, w in client_list:
                            if w != writer:
                                w.write("NO.\n".encode())
                                await w.drain()

                        # Game over - close all connections
                        SERVER_RUNNING = False
                        break

                except ValueError:
                    # Invalid input - move to next client
                    pass

                # Move to next client's turn
                current_turn = (current_turn + 1) % len(client_list)

    except Exception as e:
        print(f"Client {client_id} error: {e}")
    finally:
        if (reader, writer) in client_list:
            client_list.remove((reader, writer))
        writer.close()
        await writer.wait_closed()


async def handle_new_connection(
    reader: asyncio.StreamReader, writer: asyncio.StreamWriter
):
    client_id = len(client_list)
    client_list.append((reader, writer))

    await handle_client(reader, writer, client_id)


async def main():
    global SERVER_RUNNING
    try:
        server = await asyncio.start_server(
            handle_new_connection, host=HOST, port=PORT, reuse_address=True
        )

        print(f"Server running on {HOST}:{PORT}")
        print(f"Secret number is: {SECRET_NUMBER}")

        async with server:
            await server.serve_forever()

    except KeyboardInterrupt:
        print("\nServer shutting down...")
        SERVER_RUNNING = False

        # Close all client connections
        for reader, writer in client_list:
            writer.close()
        client_list.clear()
    except Exception as e:
        print(f"Server error: {e}")


if __name__ == "__main__":
    asyncio.run(main())
