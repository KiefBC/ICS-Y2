#!/usr/bin/env bash

# Install Python dependencies
pip install --upgrade pip
pip install pipenv
pipenv install --deploy --ignore-pipfile

# Install Node.js dependencies for Tailwind CSS
cd bs_theme/static_src
npm install
cd -

# Build Tailwind CSS
pipenv run python manage.py tailwind build

# Collect static files
pipenv run python manage.py collectstatic --no-input

# Apply database migrations
pipenv run python manage.py migrate