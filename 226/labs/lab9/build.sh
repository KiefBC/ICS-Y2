#!/usr/bin/env bash
# Exit on error
set -o errexit

# Function to print messages to the Render log
log() {
    echo "-----> $1"
}

print_cwd() {
    cwd=$(pwd)
    CWD_UPPER=${cwd^^}
    echo -e "\nCurrent Working Directory: $CWD_UPPER\n"
}

log "Starting build process..."

# Install Python dependencies
log "Upgrading pip and installing pipenv..."
print_cwd
pip install --upgrade pip
pip install pipenv

log "Installing project dependencies with pipenv..."
print_cwd
pipenv install --deploy --ignore-pipfile

# Install Node.js dependencies for Tailwind CSS
log "Installing Node.js dependencies for Tailwind CSS..."
print_cwd
cd bs_theme/static_src
npm install
cd -

# Build Tailwind CSS
log "Building Tailwind CSS..."
print_cwd
pipenv run python manage.py tailwind build

# Collect static files
log "Collecting static files..."
print_cwd
pipenv run python manage.py collectstatic --no-input

# Apply database migrations
log "Applying database migrations..."
print_cwd
pipenv run python manage.py migrate

log "Build process completed successfully."
