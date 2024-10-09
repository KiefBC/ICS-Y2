import pytest
from Board import Board
from Player import Player

def test_player():
    """
    Test the Player class
    """
    player = Player("Test_Player")

    assert player.name == "Test_Player"
    assert player.score == 0

    player.add_score(10)
    assert player.get_score() == 10

    player.add_score(5)
    assert player.get_score() == 15

def test_board():
    """
    Test the Board class
    """
    print("Testing Board")
    with pytest.raises(ValueError, match='Too many treasures to fit on the board.'):
        board = Board(1, 5)

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
    Test the Board class with invalid treasure types
    """
    with pytest.raises(ValueError, match="board_size and num_treasure_types must be integers."):
        Board("large", 2)
    with pytest.raises(ValueError, match="board_size and num_treasure_types must be integers."):
        Board(5, "many")

def test_empty_space():
    """
    Test the Board class with empty space
    """
    board = Board(5, 2)
    value = board.pick(0, 0)
    assert value is None
    assert board.grid[0][0] == "✗"

def test_gameplay_loop():
    """
    Test the Board class with a full game loop
    """
    board = Board(5, 2)
    player = Player("Test_Player")

    for row in range(5):
        for col in range(5):
            value = board.pick(row, col)
            if value:
                player.add_score(value)

    assert player.get_score() > 0