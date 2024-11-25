#!/usr/bin/env bash
# Exit on error
set -o errexit

# Function to print messages to the Render log
log() {
    echo "-----> $1"
}

log "Starting build process..."

# Install Python dependencies
log "Upgrading pip and installing pipenv..."
pip install --upgrade pip
pip install pipenv

log "Installing project dependencies with pipenv..."
pipenv install --deploy --ignore-pipfile

# Install Node.js dependencies for Tailwind CSS
log "Installing Node.js dependencies for Tailwind CSS..."
cd bs_theme/static_src
npm install
cd -

# Build Tailwind CSS
log "Building Tailwind CSS..."
pipenv run python manage.py tailwind build

# Collect static files
log "Collecting static files..."
pipenv run python manage.py collectstatic --no-input

# Apply database migrations
log "Applying database migrations..."
pipenv run python manage.py migrate

log "Build process completed successfully."
