#!/usr/bin/env bash
python -m pip install --upgrade pip
pip install pipenv
pipenv install --deploy --system
python website/manage.py collectstatic --no-input
python website/manage.py migrate