import asyncio

HOST = ""  # Empty string means listen on all available interfaces
PORT = 33333
PUNCTUATION = set('.,:;?')  # Set of punctuation marks to count

async def count_punctuation(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    try:
        # Read the input line
        data = await reader.readline()
        if not data:
            return
            
        # Count punctuation marks in the received text
        text = data.decode('utf-8')
        count = sum(1 for char in text if char in PUNCTUATION)
        
        # Send the count back to client
        writer.write(f"{count}\n".encode('utf-8'))
        await writer.drain()
        
    except Exception as e:
        print(f"Error processing client request: {e}")
    finally:
        writer.close()
        await writer.wait_closed()

async def main():
    try:
        server = await asyncio.start_server(
            count_punctuation,
            host=HOST,
            port=PORT,
            reuse_address=True
        )
        
        print(f"Server running on {HOST}:{PORT}")
        
        async with server:
            await server.serve_forever()
            
    except KeyboardInterrupt:
        print("\nServer shutting down...")
    except Exception as e:
        print(f"Server error: {e}")

if __name__ == "__main__":
    asyncio.run(main()) 