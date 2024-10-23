class Player:
    def __init__(self, name):
        """
        Initialize a new player with a given name and a starting score of 0.

        :param name: The name of the player.
        """
        self.name = name
        self.score = 0

    def add_score(self, score):
        """
        Add a score to the player's current score.

        :param score: The score to add to the player's total.
        """
        self.score += score

    def get_score(self):
        """
        Get the player's current score.

        :return: The current score of the player.
        """
        return self.score

    def __str__(self):
        """
        Return a string representation of the player.

        :return: A string showing the player's name and score.
        """
        return f"Player: {self.name}, Score: {self.score}"
