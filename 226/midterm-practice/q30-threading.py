import time
from socket import AF_INET, SO_REUSEADDR, SOCK_STREAM, SOL_SOCKET, socket
from threading import Lock, Thread

"""
Write a multithreaded server that monitors sensors. Specifically, using a b'?', the
server prompts the first sensor client whether or not an alert condition is present.
The 1-byte reply is sent to the server. If an alert is present (b'!'), the alert counter is
incremented and the counter value is printed on the server. The server, using a b'?',
then prompts the second sensor client whether or not an alert condition is present.
The reply is sent to the server. If an alert is present (b'!'), the alert counter is
incremented and a message is printed on the server. This repeats indefinitely. Your
answer must be multithreaded, using one thread per client.
"""

# Server configuration
HOST = ""  # Bind to all available network interfaces
PORT = 12345  # Port to listen on
NUM_CLIENTS = 2  # Number of sensor clients expected

# Shared alert counter and lock for synchronization
alert_counter = 0
counter_lock = Lock()  # Lock to ensure thread-safe updates to alert_counter


# Function to handle each sensor client
def handle_sensor(sensor_socket: socket, sensor_id: int) -> None:
    global alert_counter  # Access the global alert counter

    try:
        with sensor_socket:
            while True:
                # Send the prompt to the sensor
                sensor_socket.sendall(b"?")

                # Receive 1 byte from the sensor
                response = sensor_socket.recv(1)
                if not response:
                    print(f"Sensor {sensor_id} disconnected.")
                    break  # Exit if the sensor disconnects

                # Check if the response is an alert (b'!')
                if response == b"!":
                    # Update the alert counter in a thread-safe manner
                    with counter_lock:
                        alert_counter += 1
                        print(
                            f"Alert received from Sensor {sensor_id}! Total alerts: {alert_counter}"
                        )
                else:
                    print(f"Sensor {sensor_id} reported no alert.")

                # Small delay for simulation purposes (can be adjusted as needed)
                time.sleep(1)

    except Exception as e:
        print(f"An error occurred with Sensor {sensor_id}: {e}")


# Main server setup
with socket(AF_INET, SOCK_STREAM) as server_socket:
    # Configure the socket for address reuse and bind to the host and port
    server_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    server_socket.bind((HOST, PORT))
    server_socket.listen(NUM_CLIENTS)
    print(
        f"Server listening on port {PORT}, waiting for {NUM_CLIENTS} sensor clients..."
    )

    # Accept connections for each expected sensor client
    sensor_threads = []
    for sensor_id in range(1, NUM_CLIENTS + 1):
        sensor_socket, sensor_address = server_socket.accept()
        print(f"Sensor {sensor_id} connected from {sensor_address}")

        # Start a new thread for each sensor
        thread = Thread(target=handle_sensor, args=(sensor_socket, sensor_id))
        thread.start()
        sensor_threads.append(thread)

    # Wait for all threads to complete (if they are to run indefinitely, this will not reach)
    for thread in sensor_threads:
        thread.join()
