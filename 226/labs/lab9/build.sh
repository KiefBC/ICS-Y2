#!/usr/bin/env bash

# Install dependencies
python -m pip install --upgrade pip
pip install pipenv
pipenv install --system --deploy

# Install Django and other requirements
cd website/battleship
pip install -r requirements.txt
cd ../..

# Run Django commands
cd website
python manage.py collectstatic --no-input
python manage.py migrate