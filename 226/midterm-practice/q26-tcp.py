from math import ceil, floor, log2
from socket import AF_INET, SOCK_STREAM, socket
from struct import pack
from sys import argv

"""
Write a Python program that:
(1) Expects a single positive integer passed as a command line argument. If no
argument, more than 1 argument, or a non-positive-integer argument is passed, the
program must print out an error message and terminate. The program must not
crash. For example, entering: ./client.py Hello results in the error message: ./
client.py <positive integer>
(2) The program must only take a command line argument. Do not use the input()
function. Do not read from file.
(3) Other than an error message (if applicable), the program must not print anything
to screen.
the number received in step 1. For example, 255 can be represented in 1 byte
(binary 11111111), but 256 requires 2 bytes (binary 00000001 00000000). To get the
number of bytes required to represent the number in variable num, you can use the
formula: math.ceil(math.floor(math.log2(num) + 1) / 8). You must import math for
this to work.
(5) The smallest supported number is 1, the largest supported number is 2 ** 64 - 1.
(6) The program then transmits the number received in step 1 to the server, prefaced
by the number of required bytes. So for example, when transmitting 255, the client
actually transmits: 1 255. In binary, this is 00000001 11111111. When transmitting
256, the client actually transmits: 2 256. In binary this is 00000010 00000001
00000000.
"""

# Server configuration
HOST = "127.0.0.1"  # Server IP address
PORT = 12345  # Server port

# Step 1: Command-line argument validation
if len(argv) != 2:
    print(argv[0] + " <positive integer>")
    exit()

try:
    # Try to convert the argument to an integer
    num = int(argv[1])
except ValueError:
    print(argv[0] + " <positive integer>")
    exit()

# Ensure the integer is positive and within the supported range
if num <= 0:
    print(argv[0] + " <positive integer>")
    exit()
if num > 2**64 - 1:
    print("Number too big")
    exit()

# Step 4: Determine the minimum number of bytes required to represent `num`
with socket(AF_INET, SOCK_STREAM) as sock:
    sock.connect((HOST, PORT))

    # Calculate the minimum bytes required to represent the integer
    numBytes = ceil(floor(log2(num) + 1) / 8)

    # Determine the appropriate format for struct packing
    flag = "!"
    if numBytes == 1:
        flag += "B"  # Unsigned char for 1 byte
        numBytes = 1
    elif numBytes <= 2:
        flag += "H"  # Unsigned short for 2 bytes
        numBytes = 2
    elif numBytes <= 4:
        flag += "I"  # Unsigned int for 4 bytes
        numBytes = 4
    elif numBytes <= 8:
        flag += "Q"  # Unsigned long long for up to 8 bytes
        numBytes = 8

    # Step 6: Send the number of bytes and the integer to the server
    # Send the byte count as a signed char (1 byte) with format `!b`
    sock.sendall(pack("!b", numBytes))
    # Send the actual number in the specified format (e.g., 'B', 'H', 'I', 'Q')
    sock.sendall(pack(flag, num))
