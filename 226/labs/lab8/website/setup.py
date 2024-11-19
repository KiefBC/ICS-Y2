import os
import subprocess
import sys
from pathlib import Path

def run_command(command, cwd=None):
    try:
        subprocess.run(command, shell=True, check=True, cwd=cwd)
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {command}")
        print(e)
        sys.exit(1)

def main():
    # Get the absolute path to the project root
    project_root = Path(__file__).parent

    # Install requirements
    print("\nInstalling project requirements...")
    print("=================================\n")
    run_command("pipenv install")
    run_command(f"pipenv run pip install -r {project_root}/battleship/requirements.txt")
    print("=================================\n")

    # Django migrations
    print("\nRunning Django migrations...")
    print("=================================\n")
    run_command("pipenv run python manage.py makemigrations", cwd=project_root)
    run_command("pipenv run python manage.py migrate", cwd=project_root)
    print("=================================\n")

    # Install npm dependencies
    print("\nInstalling npm dependencies...")
    print("=================================\n")
    theme_dir = project_root / "bs_theme" / "static_src"
    run_command("npm install", cwd=theme_dir)
    print("=================================\n")

    # Build Tailwind
    print("\nBuilding Tailwind CSS...")
    print("=================================\n")
    run_command("pipenv run python manage.py tailwind build", cwd=project_root)
    print("=================================\n")

    # Start the server
    print("\nStarting Django server...")
    print("=================================\n")
    run_command("pipenv run python manage.py runserver", cwd=project_root)
    print("=================================\n")

if __name__ == "__main__":
    print("\nSetting up the project...")
    print("=================================\n")
    print("So far so good!\n")
    main() 
