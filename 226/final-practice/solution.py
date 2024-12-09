#!/usr/bin/python3.11
from random import randint
from socket import socket, AF_INET, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR
from threading import Semaphore, Thread
HOST = ''
NUM_CLIENTS = 1
PORT = 12345
MIN = 1
MAX = 100
r = randint(MIN, MAX)
print(r)
lock = Semaphore()
winner = 0
def get_line(current_socket: socket) -> bytes:
buffer = b''
while True:
data = current_socket.recv(1)
if data == b'' or data == b'\n':
return buffer
buffer += data # can overflow
def contact_player(client: socket, player_id: int) -> None:
global lock, r, winner
with client:
client.sendall(f'Hello Player {player_id}\n'.encode())
while True:
try:
number = int(get_line(client))
found = False
found_first = False
with lock:
if number == r:
found = True
if winner == 0:
found_first = True
winner = player_id
# Sending takes Fme, so it's done outside the lock porFon
if found_first:
client.sendall(b'You won!\n')
elif found:
client.sendall(b'You got it!\n')
else:
client.sendall(b'No\n')
except ValueError:
conFnue
with socket(AF_INET, SOCK_STREAM) as sock:
sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
sock.bind((HOST, PORT))
sock.listen(NUM_CLIENTS)
num_players = 1
while True:
sc, _ = sock.accept()
Thread(target=contact_player, args=(sc, num_players,)).start()
num_players += 1
