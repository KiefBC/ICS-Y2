import asyncio

HOST = "localhost"  # Replace with your server's host
PORT = 12345  # Replace with your server's port
LOW = 0  # Replace with your starting low boundary
HIGH = 100  # Replace with your starting high boundary


async def guess_number():
    try:
        reader, writer = await asyncio.open_connection(HOST, PORT)
    except Exception as e:
        print(f"Could not connect to server: {e}")
        return

    low = LOW
    high = HIGH

    try:
        while low <= high:
            mid = (low + high) // 2
            guess_str = str(mid) + "\n"

            try:
                # Send guess
                writer.write(guess_str.encode("utf-8"))
                await writer.drain()

                # Receive response
                response = await reader.readline()
                if not response:
                    # No response, server closed the connection unexpectedly
                    print("Server closed connection unexpectedly.")
                    break

                decoded = response.decode("utf-8").strip()
                print(f"Sent: {mid}, Received: '{decoded}'")

                if decoded == "Too High":
                    high = mid - 1
                elif decoded == "Too Low":
                    low = mid + 1
                elif decoded == "Correct":
                    print("Guessed correctly! Closing connection.")
                    break
                else:
                    print(f"Unexpected response from server: {decoded}")
                    break
            except Exception as e:
                print(f"An error occurred during communication: {e}")
                break
    except Exception as e:
        print(f"An error occurred during communication: {e}")
    finally:
        # Clean up resources
        writer.close()
        await writer.wait_closed()


async def main():
    try:
        server = await asyncio.start_server(guess_number, HOST, PORT)
        print(f"Server started on {HOST}:{PORT}")
        async with server:
            await server.serve_forever()
    except Exception as e:
        print(f"An error occurred: {e}")
        return


if __name__ == "__main__":
    asyncio.run(main())
