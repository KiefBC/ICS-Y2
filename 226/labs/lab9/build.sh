#!/usr/bin/env bash
pipenv run 
pipenv install
pipenv run pip install -r website/battleship/requirements.txt
pipenv run python website/manage.py collectstatic --no-input
pipenv run python website/manage.py makemigrations
pipenv run python website/manage.py migrate
npm install website/bs_theme/static_src
pipenv run python website/manage.py tailwind build
