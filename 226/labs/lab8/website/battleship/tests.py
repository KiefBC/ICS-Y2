from django.test import TestCase, Client
from django.urls import reverse
from .models import Player, Tile

class BattleshipGameTests(TestCase):
    def setUp(self):
        # Create a new game before each test
        self.client = Client()
        self.client.get(reverse('create_game'))

    def test_game_initialization(self):
        """Test that the game is properly initialized with players and tiles"""
        # Test player creation
        players = Player.objects.all()
        self.assertEqual(players.count(), 2)
        
        player_one = Player.objects.get(name="One")
        player_two = Player.objects.get(name="Two")
        
        # Test player initial states
        self.assertEqual(player_one.score, 0)
        self.assertTrue(player_one.is_turn)
        self.assertEqual(player_two.score, 0)
        self.assertFalse(player_two.is_turn)

        # Test board creation
        tiles = Tile.objects.all()
        self.assertEqual(tiles.count(), 100)  # 10x10 board

        # Test treasure placement
        treasure_tiles = Tile.objects.filter(value="treasure")
        self.assertEqual(treasure_tiles.count(), 4)

    def test_pick_tile_treasure(self):
        """Test picking a tile with treasure"""
        # Find a treasure tile
        treasure_tile = Tile.objects.filter(value="treasure").first()
        
        # Make the pick
        response = self.client.get(
            reverse('pick_tile', 
                   kwargs={'player_name': 'One',
                          'row': treasure_tile.row,
                          'col': treasure_tile.column})
        )
        
        # Check response
        self.assertEqual(response.status_code, 200)
        
        # Verify score update
        player_one = Player.objects.get(name="One")
        self.assertEqual(player_one.score, 1)
        
        # Verify tile state change
        updated_tile = Tile.objects.get(id=treasure_tile.id)
        self.assertEqual(updated_tile.value, "revealed_treasure")
        
        # Verify turn switched
        self.assertFalse(player_one.is_turn)
        player_two = Player.objects.get(name="Two")
        self.assertTrue(player_two.is_turn)

    def test_pick_tile_empty(self):
        """Test picking an empty tile"""
        # Find an empty tile
        empty_tile = Tile.objects.filter(value="empty").first()
        
        # Make the pick
        response = self.client.get(
            reverse('pick_tile', 
                   kwargs={'player_name': 'One',
                          'row': empty_tile.row,
                          'col': empty_tile.column})
        )
        
        # Check response
        self.assertEqual(response.status_code, 200)
        
        # Verify score didn't change
        player_one = Player.objects.get(name="One")
        self.assertEqual(player_one.score, 0)
        
        # Verify tile state change
        updated_tile = Tile.objects.get(id=empty_tile.id)
        self.assertEqual(updated_tile.value, "picked")

    def test_pick_tile_invalid_turn(self):
        """Test picking a tile when it's not the player's turn"""
        # Try to pick as Player Two when it's Player One's turn
        response = self.client.get(
            reverse('pick_tile', 
                   kwargs={'player_name': 'Two',
                          'row': 0,
                          'col': 0})
        )
        
        # Check response
        self.assertEqual(response.status_code, 200)
        self.assertContains(response, "It's not Two's turn!", html=True)

    def test_pick_tile_out_of_bounds(self):
        """Test picking a tile outside the board boundaries"""
        response = self.client.get(
            reverse('pick_tile', 
                   kwargs={'player_name': 'One',
                          'row': 10,
                          'col': 0})
        )
        
        # Check response
        self.assertEqual(response.status_code, 200)
        self.assertContains(response, "Out of Boundary")

    def test_pick_same_tile_twice(self):
        """Test picking the same tile twice"""
        # Pick a tile
        tile = Tile.objects.filter(value="empty").first()
        self.client.get(
            reverse('pick_tile', 
                   kwargs={'player_name': 'One',
                          'row': tile.row,
                          'col': tile.column})
        )
        
        # Try to pick the same tile as Player Two
        response = self.client.get(
            reverse('pick_tile', 
                   kwargs={'player_name': 'Two',
                          'row': tile.row,
                          'col': tile.column})
        )
        
        # Check response
        self.assertEqual(response.status_code, 200)
        self.assertContains(response, "This tile has already been picked")
