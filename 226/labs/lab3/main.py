from Board import Board
from Player import Player


def get_input(prompt, min_val=None, max_val=None):
    """
    Prompt the user for an integer within an optional range.
    """
    while True:
        user_input = input(prompt)
        try:
            user_input = int(user_input)
            if (min_val is not None and user_input < min_val) or (max_val is not None and user_input > max_val):
                range_msg = f" between {min_val} and {max_val}" if min_val is not None and max_val is not None else ""
                print(f"Please enter a valid integer{range_msg}.")
                continue
            return user_input
        except ValueError:
            print("Please enter a valid integer.")



def main():
    """
    Main function of the script.
    """
    size = get_input("Enter the size of the board (1 to 10): ", 1, 10)
    pieces = get_input("Enter the number of treasure types: ", 1)

    try:
        board = Board(size, pieces)
    except ValueError as e:
        print(f"Error initializing board: {e}")
        return

    player = Player("One")

    while True:
        print("\nCurrent Board:")
        print(board)
        print(player)

        row = get_input(f"Enter a row (0 to {size - 1}): ", 0, size - 1)
        col = get_input(f"Enter a column (0 to {size - 1}): ", 0, size - 1)

        try:
            value = board.pick(row, col)
            if value:
                print(f"Found treasure of value {value}!")
                player.add_score(value)
            else:
                print("No treasure at this location.")

            # Check if all treasures have been found
            if not any(cell.isdigit() for row in board.grid for cell in row if cell != "-"):
                print("\nAll treasures have been found!")
                print(player)
                break
        except ValueError as e:
            print(f"Error: {e}")
            print("Please enter valid integer values within the board range.")
        except Exception as e:
            print(f"Unexpected error: {e}")
            break

if __name__ == "__main__":
    main()
