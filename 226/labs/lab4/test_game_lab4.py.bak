import pytest
from Board import Board
from Player import Player


def test_player():
    """
    Test the Player class with valid player names and score updates
    """
    player = Player("Test_Player")

    pytest.assume(player.name == "Test_Player",
                  f"Expected player name 'Test_Player', got {player.name}")
    pytest.assume(player.score == 0,
                  f"Expected initial score 0, got {player.score}")

    player.add_score(10)
    pytest.assume(player.get_score() == 10,
                  f"Expected score 10 after adding, got {player.get_score()}")

    player.add_score(5)
    pytest.assume(player.get_score() == 15,
                  f"Expected score 15 after adding 5, got {player.get_score()}")


def test_board():
    """
    Test the Board class with valid board sizes and treasure types
    """
    with pytest.raises(ValueError, match='Too many treasures to fit on the board.'):
        Board(1, 5)

    with pytest.raises(ValueError, match='board_size and num_treasure_types must be integers.'):
        Board("small", 5)

    board = Board(5, 2)
    pytest.assume(board.board_size == 5)

    for row in range(5):
        for col in range(5):
            value = board.pick(row, col)

            if value:
                pytest.assume(value in range(
                    1, 3), f"Expected treasure in range 1-2, got {value} at ({row}, {col})")
            else:
                pytest.assume(board.grid[row][col] == "✗",
                              f"Expected '✗', got {board.grid[row][col]} at ({row}, {col})")


def test_board_size():
    """
    Test the Board class with invalid board sizes
    """
    with pytest.raises(ValueError, match="board_size and num_treasure_types must be greater than 0."):
        Board(0, 2)
    with pytest.raises(ValueError, match="board_size and num_treasure_types must be greater than 0."):
        Board(-5, 2)


def test_treasure_count():
    """
    Test the Board class with too many treasures
    """
    with pytest.raises(ValueError, match="Too many treasures to fit on the board."):
        Board(2, 10)


def test_treasure_board_types():
    """
    Test the Board class with invalid treasure types and board sizes
    """
    with pytest.raises(ValueError, match="board_size and num_treasure_types must be integers."):
        Board("large", 2)
    with pytest.raises(ValueError, match="board_size and num_treasure_types must be integers."):
        Board(5, "many")


def test_empty_space():
    """
    Test the Board class with an empty space pick
    """
    board = Board(5, 1)

    empty_pos = None
    for row in range(board.board_size):
        for col in range(board.board_size):
            if board.grid[row][col] == "-":
                empty_pos = (row, col)
                break
        if empty_pos:
            break

    pytest.assume(empty_pos is not None, "No empty space found on the board.")

    if empty_pos:
        row, col = empty_pos
        value = board.pick(row, col)

        pytest.assume(
            value is None, f"Expected None, got {value} at position ({row}, {col})")
        pytest.assume(board.grid[row][col] == "✗",
                      f"Expected '✗', got {board.grid[row][col]} at position ({row}, {col})")


def test_invalid_pick():
    """
    Test that an invalid pick raises an IndexError
    """
    board = Board(5, 2)

    with pytest.raises(IndexError, match="Row or column out of bounds"):
        board.pick(5, 5)

    with pytest.raises(IndexError, match="Row or column out of bounds"):
        board.pick(-1, 0)

    with pytest.raises(IndexError, match="Row or column out of bounds"):
        board.pick(0, 5)


def test_player_str():
    """
    Test the string representation of the Player class
    """
    player = Player("Test_Player")
    player_str = str(player)

    pytest.assume("Test_Player" in player_str,
                  f"Expected 'Test_Player' in string, got {player_str}")
    pytest.assume("Score: 0" in player_str,
                  f"Expected 'Score: 0' in string, got {player_str}")


def test_board_initialization():
    """
    Test that the Board is initialized with the correct size and treasure placement
    """
    board = Board(5, 2)
    pytest.assume(board.board_size == 5,
                  f"Expected board size 5, got {board.board_size}")
    pytest.assume(len(board.grid) == 5,
                  f"Expected grid length 5, got {len(board.grid)}")
    for row in board.grid:
        pytest.assume(len(row) == 5, f"Expected row length 5, got {len(row)}")


def test_repeated_picks():
    """
    Test picking the same spot multiple times
    """
    board = Board(5, 2)
    value = board.pick(0, 0)

    if value is None:
        pytest.assume(board.grid[0][0] == "✗",
                      f"Expected '✗' at (0,0), got {board.grid[0][0]}")
    else:
        pytest.assume(board.grid[0][0] == "✓",
                      f"Expected '✓' at (0,0), got {board.grid[0][0]}")

    second_value = board.pick(0, 0)
    pytest.assume(second_value is None,
                  f"Expected None for repeated pick at (0,0), got {second_value}")
    pytest.assume(board.grid[0][0] in ["✗", "✓"],
                  f"Unexpected value at (0,0): {board.grid[0][0]}")
