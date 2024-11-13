from django.shortcuts import render, redirect
from django.http import HttpResponse, HttpResponseBadRequest
from django.db import transaction
from .models import Tile, Player
import random

def create_game(request):
    # Clear existing game data
    Tile.objects.all().delete()
    Player.objects.all().delete()
    
    # Create players
    Player.objects.create(name="One", score=0)
    Player.objects.create(name="Two", score=0)
    
    # Create empty board
    for row in range(10):
        for col in range(10):
            Tile.objects.create(row=row, column=col, value="empty")
    
    # Place 4 treasures randomly
    all_tiles = list(Tile.objects.all())
    treasure_tiles = random.sample(all_tiles, 4)
    
    for tile in treasure_tiles:
        tile.value = "treasure"
        tile.save()
    
    return HttpResponse("Game created successfully!")

def display_game(request):
    # Get all tiles ordered by row and column
    tiles = Tile.objects.all().order_by('row', 'column')
    players = Player.objects.all().order_by('name')
    
    # Create a 2D list for the board
    board = []
    current_row = []
    current_row_number = 0
    
    for tile in tiles:
        if tile.row > current_row_number:
            board.append(current_row)
            current_row = []
            current_row_number = tile.row
        current_row.append(tile)
    board.append(current_row)
    
    return render(request, 'battleship/game.html', {
        'board': board,
        'players': players,
    })

@transaction.atomic
def pick_tile(request, player_name, row, col):
    try:
        # Input validation
        if not (0 <= row <= 9 and 0 <= col <= 9):
            return HttpResponseBadRequest("Invalid row or column. Must be between 0 and 9.")
            
        # Get player with lock
        try:
            player = Player.objects.select_for_update().get(name=player_name)
        except Player.DoesNotExist:
            return HttpResponseBadRequest(f"Player {player_name} not found.")
            
        # Get tile with lock
        try:
            tile = Tile.objects.select_for_update().get(row=row, column=col)
        except Tile.DoesNotExist:
            return HttpResponseBadRequest(f"Tile at position ({row}, {col}) not found.")
            
        # Check if tile was already picked
        if tile.value == "picked":
            return HttpResponseBadRequest("This tile has already been picked.")
            
        # Update tile and score
        if tile.value == "treasure":
            player.score += 1
            player.save()
            
        tile.value = "picked"
        tile.save()
        
        # Get all players for score display
        players = Player.objects.all()
        scores = ", ".join([f"{p.name}: {p.score}" for p in players])
        
        return HttpResponse(f"Pick processed. Current scores: {scores}")
        
    except Exception as e:
        return HttpResponseBadRequest(f"An error occurred: {str(e)}")
