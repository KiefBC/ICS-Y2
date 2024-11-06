#!/usr/bin/python3

from sys import argv


def main():
    if len(argv) != 2:
        print("No argument passed.")
        num = int(input("Enter a number: "))
        print(f"Number chosen: {num}")
    else:
        print("Argument passed.")
        num = int(argv[1])
        print(f"Number chosen: {num}")

    result = count_bits(num)
    print(f"Number of bits set: {result}")


def count_bits(num):
    count = 0

    # Continue until num is 0
    while num:
        # Check if the last bit is 1 or 0
        # If 1, increment count, Shift the number to the right by 1
        # If 0, Shift the number to the right by 1
        if num & 1:
            count += 1

        # Shift the number to the right by 1
        num >>= 1

    return count


if __name__ == "__main__":
    main()
