import pytest
from Board import Board
from Player import Player

def test_player():
    print("Testing Player")
    player = Player("Test_Player")

    assert player.name == "Test_Player"
    print("Player name test passed")

    assert player.score == 0
    print("Initial score test passed")

    player.add_score(10)
    assert player.get_score() == 10
    print("Score after adding 10 test passed")

    player.add_score(5)
    assert player.get_score() == 15
    print("Score after adding 5 test passed")

def test_board():
    print("Testing Board")
    with pytest.raises(ValueError, match='Too many treasures to fit on the board.'):
        board = Board(1, 5)
