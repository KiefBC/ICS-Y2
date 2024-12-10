# Python Network Programming Guide: Threading and Async

## Introduction
This guide covers the fundamentals of network programming in Python, exploring both threaded and asynchronous implementations. We'll examine different server types, their implementations, and the process of converting between threading and async approaches.

## Core Concepts

### Server Configuration
#### Threaded Approach
In threaded servers, we typically start with socket configuration:
```python
from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket

HOST = ""  # Empty string for all available interfaces
PORT = 12345
SERVER = (HOST, PORT)

# Basic socket setup
server_socket = socket(AF_INET, SOCK_STREAM)
server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
server_socket.bind(SERVER)
server_socket.listen(num_connections)
```

#### Async Approach
Async servers use asyncio's high-level API:
```python
import asyncio

async def main():
    server = await asyncio.start_server(
        handle_client,
        host="",
        port=12345,
        reuse_address=True
    )
```

### Connection Handling

#### Threaded Model
Threaded servers handle connections by creating a new thread for each client:
```python
def main():
    while SERVER_RUNNING:
        client_socket, address = server_socket.accept()
        Thread(target=handle_client, args=(client_socket,), daemon=True).start()
```

#### Async Model
Async servers handle connections through coroutines:
```python
async def handle_new_connection(reader: asyncio.StreamReader, 
                              writer: asyncio.StreamWriter):
    try:
        await handle_client(reader, writer)
    finally:
        writer.close()
        await writer.wait_closed()
```

### Message Processing

#### Threaded Implementation
```python
def get_message(socket):
    socket.send(b"Message: ")
    buffer = b''
    while True:
        data = socket.recv(1)
        if data in [b'', b'\n']:
            return buffer
        buffer += data
```

#### Async Implementation
```python
async def get_message(reader, writer):
    writer.write(b"Message: ")
    await writer.drain()
    return await reader.readline()
```

## Server Types and Their Implementations

### Basic Chat Server
A chat server allows multiple clients to connect and exchange messages.

#### Key Features:
- Message broadcasting
- Client management
- Connection handling

```python
# Threaded version
def handle_client(client_socket, user_id):
    try:
        while SERVER_RUNNING:
            message = client_socket.recv(1024).decode("utf-8")
            if not message:
                break
            broadcast_message(f"Client {user_id}: {message}")
    finally:
        client_socket.close()

# Async version
async def handle_client(reader, writer):
    try:
        while True:
            data = await reader.read(1024)
            if not data:
                break
            message = data.decode()
            await broadcast_message(message)
    finally:
        writer.close()
        await writer.wait_closed()
```

### Alert System Server
An alert system server coordinates messages between clients and tracks specific events.

#### Key Features:
- Alert counting
- Client coordination
- Synchronized shutdown

```python
# Threaded version with semaphores
client_lock = [Semaphore(0) for _ in range(NUM_CLIENTS)]

def handle_client(socket, client_id):
    while SERVER_RUNNING:
        client_lock[client_id].acquire()
        if alert_received():
            increment_alert_count()
        client_lock[(client_id + 1) % NUM_CLIENTS].release()

# Async version with events
async def handle_client(reader, writer, client_id):
    while SERVER_RUNNING:
        await client_events[client_id].wait()
        if await check_alert():
            await increment_alert_count()
        client_events[(client_id + 1) % NUM_CLIENTS].set()
```

### Game Server
A game server managing state and client interactions.

#### Key Features:
- State management
- Turn coordination
- Winner detection

```python
# Threaded version
def handle_client(client_socket, client_id):
    while not WINNER and guesses < MAX_GUESSES:
        with LOCK:
            guess = int(client_socket.recv(1024).decode())
            if guess == SECRET_NUMBER:
                WINNER = True

# Async version
async def handle_client(reader, writer):
    while not game_state.winner and game_state.guesses < MAX_GUESSES:
        guess = int(await reader.readline())
        async with game_state.lock:
            if guess == game_state.secret_number:
                game_state.winner = True
```

## Converting Threading to Async

### Step 1: Library Changes
Replace threading imports with asyncio:
```python
# From
from threading import Thread, Lock
# To
import asyncio
```

### Step 2: Function Conversion
Convert regular functions to coroutines:
```python
# From
def handle_client(socket):
    data = socket.recv(1024)
    
# To
async def handle_client(reader, writer):
    data = await reader.read(1024)
```

### Step 3: Resource Management
Replace locks with asyncio primitives:
```python
# From
lock = Lock()
with lock:
    # critical section

# To
lock = asyncio.Lock()
async with lock:
    # critical section
```

### Step 4: Socket Operations
Replace socket operations with asyncio streams:
```python
# From
socket.send(data)
socket.recv(1024)

# To
writer.write(data)
await writer.drain()
await reader.read(1024)
```

## Best Practices

### Threading Best Practices
1. Always use proper lock management for shared resources
2. Implement proper exception handling
3. Use daemon threads for automatic cleanup
4. Implement graceful shutdown procedures
5. Use context managers for resource cleanup

### Async Best Practices
1. Always await coroutines
2. Use asyncio.gather for concurrent operations
3. Implement proper exception handling
4. Use async context managers
5. Remember to drain writers
6. Always close writers and wait for closure

## Common Patterns

### Broadcasting Messages
```python
# Threaded
def broadcast(message, sender=None):
    with clients_lock:
        for client in clients:
            if client != sender:
                client.send(message)

# Async
async def broadcast(message, sender=None):
    tasks = []
    for client in clients:
        if client != sender:
            tasks.append(client.write(message))
    await asyncio.gather(*tasks)
```

### Resource Cleanup
```python
# Threaded
def cleanup():
    with client_lock:
        for client in clients[:]:
            client.close()
        clients.clear()

# Async
async def cleanup():
    for client in clients[:]:
        client.close()
        await client.wait_closed()
    clients.clear()
```

## Performance Considerations

### Threading
- Better for CPU-bound tasks
- One thread per client can be resource-intensive
- Requires careful lock management
- Better for smaller numbers of concurrent connections

### Async
- Better for I/O-bound tasks
- More efficient resource usage
- No need for explicit lock management
- Better for large numbers of concurrent connections
- Lower memory overhead

## Debugging Tips

### Threading Issues
1. Race conditions
2. Deadlocks
3. Resource leaks
4. Thread safety

### Async Issues
1. Forgotten awaits
2. Coroutine never scheduled
3. Event loop blocking
4. Resource cleanup