#!/usr/bin/python3

from sys import argv
from threading import Lock, Thread

# This is used to lock the variable number
# so that only one thread can access it at a time
# We can also use Semaphore() which is a more advanced version of Lock() and can be used to lock multiple threads
# Exampple of Semaphore: lock = Semaphore(2) # This will allow 2 threads to access the variable at a time
lock = Lock()


def main():
    if len(argv) != 2:
        print(f"Usage: {argv[0]} <number>")
        exit(1)

    global number
    number = int(argv[1])
    threads = []

    for _ in range(number):
        threads.append(Thread(target=called_thread))
        threads[-1].start()  # We do [-1] to get the last element of the list

    # Wait for all threads to finish
    for thread in threads:
        thread.join()

    print(f"Final number: {number}")


def called_thread():
    global number
    for _ in range(1000000):
        with (
            lock
        ):  # Lock the variable number so that only one thread can access it at a time
            number += 1


if __name__ == "__main__":
    main()
