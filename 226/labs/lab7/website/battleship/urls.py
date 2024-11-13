from django.urls import path
from . import views

urlpatterns = [
    path('game/create/', views.create_game, name='create_game'),
    path('game/', views.display_game, name='display_game'),
    path('game/pick/<str:player_name>/<int:row>/<int:col>/', views.pick_tile, name='pick_tile'),
] 