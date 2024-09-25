import random


class Board:
    """
    Class representing a game board.
    """
    def __init__(self, board_size, num_treasures):
        """
        Initialize the board with given size and number of treasure types.

        :param board_size: Size of the board (NxN).
        :param num_treasures: Number of different types of treasures.
        """
        # Validate that board_size and num_treasure_types are integers greater than 0
        if not isinstance(board_size, int) or not isinstance(num_treasures, int):
            raise ValueError("board_size and num_treasure_types must be integers.")
        if board_size <= 0 or num_treasures <= 0:
            raise ValueError("board_size and num_treasure_types must be greater than 0.")

        max_treasures = num_treasures * (num_treasures + 1) // 2
        if max_treasures > board_size * board_size:
            raise ValueError("Too many treasures to fit on the board.")

        self.board_size = board_size
        self.num_treasure_types = num_treasures
        self.grid = [["0"] * board_size for _ in range(board_size)]

        for treasure_type in range(1, num_treasures + 1):
            treasures_per_type = treasure_type

            # Decide randomly whether to place treasures horizontally or vertically
            placement_direction = random.choice(['horizontal', 'vertical'])

            # If the treasure is placed at (0, 0), the next one will be at (0, 1) or (1, 0)
            placement_step = random.choice([1, -1])

            # Place the treasure randomly
            current_row = random.randint(0, board_size - 1) # -1 because randint is inclusive
            current_col = random.randint(0, board_size - 1)
            self.grid[current_row][current_col] = str(treasure_type)

            for _ in range(treasures_per_type - 1):
                if placement_direction == 'horizontal':
                    current_col = (current_col + placement_step) % board_size
                else:
                    current_row = (current_row + placement_step) % board_size
                self.grid[current_row][current_col] = str(treasure_type)

    def pick(self, target_row, target_col):
        """
        Allows the player to pick a cell on the board.
        :param target_row:
        :param target_col:
        :return:
        """

        # Validate that target_row and target_col are integers
        if not (0 <= target_row < self.board_size) or not (0 <= target_col < self.board_size):
            raise ValueError("Row and column must be within the board.")
        cell_value = self.grid[target_row][target_col]
        self.grid[target_row][target_col] = "✓"
        return int(cell_value) if cell_value != "?" else None

    def __str__(self):
        """
        String representation of the board.
        :return:
        """
        top_numbers = "    " + " ".join(f"{i}" for i in range(self.board_size))
        border = "   " + "=" * (self.board_size * 2 + 1)
        board_rows = []
        for index, row in enumerate(self.grid):
            row_str = f"{index} | " + " ".join(row) + " |"
            board_rows.append(row_str)

        board_str = "\n".join(board_rows)
        return f"{top_numbers}\n{border}\n{board_str}\n{border}\n"

