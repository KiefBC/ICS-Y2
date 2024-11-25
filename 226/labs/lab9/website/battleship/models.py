from django.db import models


class Tile(models.Model):
    row = models.IntegerField()
    column = models.IntegerField()
    value = models.CharField(max_length=100)

    def __str__(self):
        return f"{self.row} - {self.column} - {self.value}"


class Player(models.Model):
    name = models.CharField(max_length=100)
    score = models.IntegerField()
    is_turn = models.BooleanField(default=False)

    def __str__(self):
        return f"{self.name} - {self.score}"
