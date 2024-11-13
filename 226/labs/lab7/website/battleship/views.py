from django.shortcuts import render, redirect
from django.http import HttpResponse, HttpResponseBadRequest
from django.db import transaction
from .models import Tile, Player
import random
import time

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
    
    return redirect('display_game')

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
            return render(request, 'battleship/pick_result.html', {
                'message': "Out of Boundary",
                'players': Player.objects.all()
            })
            
        # Get player with lock
        try:
            player = Player.objects.select_for_update().get(name=player_name)
        except Player.DoesNotExist:
            return render(request, 'battleship/pick_result.html', {
                'message': f"Player {player_name} not found",
                'players': Player.objects.all()
            })
            
        # Get tile with lock
        try:
            tile = Tile.objects.select_for_update().get(row=row, column=col)
        except Tile.DoesNotExist:
            return render(request, 'battleship/pick_result.html', {
                'message': f"Tile at position ({row}, {col}) not found",
                'players': Player.objects.all()
            })
            
        # Check if tile was already picked
        if tile.value in ["picked", "revealed_treasure"]:
            return render(request, 'battleship/pick_result.html', {
                'message': "This tile has already been picked",
                'players': Player.objects.all()
            })
            
        # Update tile and score
        if tile.value == "treasure":
            player.score += 1
            player.save()
            tile.value = "revealed_treasure"
            message = "Treasure found!"
        else:
            tile.value = "picked"
            message = "No treasure here"
        tile.save()
        
        return render(request, 'battleship/pick_result.html', {
            'message': message,
            'players': Player.objects.all()
        })
        
    except Exception as e:
        return render(request, 'battleship/pick_result.html', {
            'message': f"An error occurred: {str(e)}",
            'players': Player.objects.all()
        })
