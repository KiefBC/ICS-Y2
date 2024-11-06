#!/usr/bin/python3

from sys import argv
from threading import Thread
from time import sleep


def main():
    if len(argv) != 2:
        print("Usage: python3 threading.py <number>")
        return

    number = int(argv[1])

    for i in range(number):
        Thread(target=print_number, args=(i,)).start()


def print_number(number):
    """
    Print the number every 2 seconds
    The number is acting as a thread identifier
    Each thread will print its own number
    The numbers will not always be in order
    """
    while True:
        print(number)
        sleep(2)


if __name__ == "__main__":
    main()
