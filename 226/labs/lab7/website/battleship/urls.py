from django.shortcuts import redirect
from django.urls import path

from . import views


def redirect_to_game():
    return redirect("display_game")


urlpatterns = [
    path("", redirect_to_game, name="root"),
    path("game/create/", views.create_game, name="create_game"),
    path("game/", views.display_game, name="display_game"),
    path(
        "game/pick/<str:player_name>/<str:row>/<str:col>/",
        views.pick_tile,
        name="pick_tile",
    ),
]

