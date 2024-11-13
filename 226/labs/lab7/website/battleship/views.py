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
    redirect_script = "<script>setTimeout(function(){ window.location.href = '/game/'; }, 2000);</script>"
    
    try:
        # Input validation
        if not (0 <= row <= 9 and 0 <= col <= 9):
            return HttpResponse("Out of Boundary. Redirecting..." + redirect_script)
            
        # Get player with lock
        try:
            player = Player.objects.select_for_update().get(name=player_name)
        except Player.DoesNotExist:
            return HttpResponse(f"Player {player_name} not found. Redirecting..." + redirect_script)
            
        # Get tile with lock
        try:
            tile = Tile.objects.select_for_update().get(row=row, column=col)
        except Tile.DoesNotExist:
            return HttpResponse(f"Tile at position ({row}, {col}) not found. Redirecting..." + redirect_script)
            
        # Check if tile was already picked
        if tile.value in ["picked", "revealed_treasure"]:
            return HttpResponse("This tile has already been picked. Redirecting..." + redirect_script)
            
        # Update tile and score
        if tile.value == "treasure":
            player.score += 1
            player.save()
            tile.value = "revealed_treasure"
        else:
            tile.value = "picked"
        tile.save()
        
        # Get all players for score display
        players = Player.objects.all()
        scores = ", ".join([f"{p.name}: {p.score}" for p in players])
        
        return HttpResponse(f"Pick processed. Current scores: {scores}" + redirect_script)
        
    except Exception as e:
        return HttpResponse(f"An error occurred: {str(e)}. Redirecting..." + redirect_script)
