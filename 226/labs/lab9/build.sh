#!/usr/bin/env bash
pipenv run pipenv install
pipenv run python website/manage.py collectstatic --no-input
pipenv run python website/manage.py migrate