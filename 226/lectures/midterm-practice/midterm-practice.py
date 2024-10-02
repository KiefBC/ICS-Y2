# Slide 20 Programs

# MIN_SPEED = 0
# MAX_SPEED = 50
#
# while True:
#     try:
#         user_speed = int(input("Enter your speed: "))
#
#         if user_speed < MIN_SPEED:
#             print("Too slow\n")
#         elif user_speed > MAX_SPEED:
#             print("Where you going?\n")
#         else:
#             print(f"Your speed {user_speed} is valid.\n")
#             break
#     except ValueError:
#         print("Needs to be an integer. Please try again.\n")
#
# FREEZING_POINT = 0
#
# while True:
#     try:
#         user_temp = int(input("Enter the temperature: "))
#
#         if user_temp < FREEZING_POINT:
#             print("Below Freezing\n")
#             break
#         elif user_temp > FREEZING_POINT:
#             print("Above Freezing\n")
#             break
#         else:
#             print("Freezing Point\n")
#             break
#     except ValueError:
#         print("Only Ints allowed\n")

# Slide 23

# while True:
#     user_input = input("Enter a new password: ")
#     match user_input:
#         case '1234' | 'password':
#             print("Too common\n")
#         case length if len(user_input) < 8:
#             print("Too short\n")
#         case all_numbers if user_input.isnumeric():
#             print("No all number passwords\n")
#         case _:
#             print("Password Ok\n")
#             break

# Slide 27

# counter = 0
# MAGIC = 3
#
# while True:
#     user_input = input("Enter Quit (Or don't): ")
#     if user_input.lower() == "quit":
#         counter += 1
#         print(counter)
#     if counter == MAGIC:
#         break

# import random as r
#
# MAX_RANGE = 10
# MIN_RANGE = 0
# while True:
#     try:
#         userNum = int(input("Enter a number: "))
#
#         if MIN_RANGE < userNum <= MAX_RANGE:
#             print("Valid Number\n")
#             break
#         else:
#             print(f"Enter a number between {MIN_RANGE} and {MAX_RANGE}\n")
#             continue
#     except ValueError:
#         print("Numbers only!\n")
#
# randomNum = r.randrange(userNum)
# print(f"Random Number is: {randomNum}")

# Slice 32

# SQUARE = 2
# input = int(input("Enter a number: "))
#
# for num in range(input):
#     print(f"Square of {num} is {num ** SQUARE}")

# import random as r
#
# MAX = 100
# total = 0
#
# for _ in range(MAX):
#     total += r.randint(0, MAX)
#
# print(f"The Average of {MAX} items is: {total / MAX}")

# Slide 40

# user_input = input("Enter String: ")
#
# for char in user_input:
#     if char.isnumeric():
#         if int(char) % 5 == 0:
#             print(f"{char} is divisible by 5.")
#     if ord(char) % 5 == 0:
#         print(f"{char} is divisible by 5.")
#
# counter = 0
# for x in user_input:
#     counter += 1
#     if counter % 3 == 0:
#         print(f"Third Value: {x}")

# Slide 43

# TODO: Finish
num = int(input('Enter a number: '))  # Assume int > 1
i = 2
while i * i <= num:
    if num % i == 0:
        print(str(num) + ' is not a prime')
        break
    i = i + 1
else:
    print(str(num) + ' is a prime')
