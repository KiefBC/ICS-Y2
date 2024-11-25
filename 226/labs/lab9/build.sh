#!/usr/bin/env bash

echo -e "\nStarting build process...\n"

# Install Python dependencies
echo -e "\nInstalling Python dependencies...\n"
python -m pip install --upgrade pip
pip install pipenv
pipenv install --system --deploy

# Install Node.js and build Tailwind
echo -e "\nInstalling Node.js dependencies and building Tailwind...\n"
cd website/bs_theme/static_src
npm install
npm run build
cd ../../..

# Run Django commands
echo -e "\nRunning Django commands...\n"
cd website
python manage.py collectstatic --no-input
python manage.py migrate
cd ..

echo -e "\nBuild process complete!\n"