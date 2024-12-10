import asyncio
import random

HOST = ""
PORT = 12345
SERVER = (HOST, PORT)
SERVER_RUNNING = True
SECRET_NUMBER = random.randint(1, 100)

client_list = []
curr_conn = 0


async def get_guess(reader, writer, local_id):
    writer.write(f"[Client {local_id}]: Guess a number between 1 and 100: ".encode())
    await writer.drain()
    return await reader.readline()


async def handle_connections(reader, writer):
    global curr_conn
    local_id = curr_conn
    curr_conn += 1

    try:
        writer.write("Welcome to the Number Guessing Game!\n".encode())
        await writer.drain()
    except Exception:
        client_list.remove((reader, writer))
        return

    await handle_client(reader, writer, local_id)


async def handle_client(reader, writer, local_id):
    global curr_conn
    try:
        while SERVER_RUNNING:
            user_guess = await get_guess(reader, writer, local_id)
            if not user_guess:
                client_list.remove((reader, writer))
                curr_conn -= 1
                break
            try:
                user_guess = int(user_guess.decode().strip())
            except ValueError:
                writer.write("Invalid input. Please enter a number.\n".encode())
                await writer.drain()
                continue
            print(f"[Client {local_id}] Guess Received: {user_guess}")
            if user_guess == SECRET_NUMBER:
                writer.write("Congratulations! You guessed the number!\n".encode())
                await writer.drain()
                break
            elif user_guess < SECRET_NUMBER:
                writer.write("Too low! Try again!\n".encode())
                await writer.drain()
            else:
                writer.write("Too high! Try again!\n".encode())
                await writer.drain()

    except Exception:
        if (reader, writer) in client_list:
            client_list.remove((reader, writer))
    finally:
        writer.close()
        curr_conn -= 1
        await writer.wait_closed()


async def main():
    def shutdown_handler():
        global SERVER_RUNNING
        print("\nShutting down server...")
        SERVER_RUNNING = False
        for reader, writer in client_list:
            writer.close()
        client_list.clear()

    try:
        server = await asyncio.start_server(
            handle_connections, host=HOST, port=PORT, reuse_address=True
        )
        print(f"Server running on {HOST}:{PORT}")

        async with server:
            await server.serve_forever()
    except KeyboardInterrupt:
        shutdown_handler()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nServer shutdown...")
