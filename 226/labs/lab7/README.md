# THE HARD WAY!

- Clone the Repo
- You may need to `dos2unix` files if they carry over Windows encoding.
- run `pipenv shell` and let it finish, it may seem like its hanging, but it is not - you will do this for every Terminal you open
- `cd` into `website/`
- run `./manage.py makemigrations`
- run `./manage.py migrate`
- `cd` into `website/battleship` and run `pipenv install -r requirements.txt`
- `cd` into `website/bs_theme/static_src` and run `npm install`
- `cd` into `website/`
- run `pipenv run python manage.py tailwind start` in the same directory in a different terminal - this will allow you to modify the tailwind classes if you want, otherwise type this command in the same directory to build the tailwind and not have to enter it via `pipenv run python manage.py tailwind build`
- run `pipenv run python manage.py runserver` in the same directory in a different terminal

## BUT WAIT! RUDY! WHAT IF YOU DON'T WANT TO DO ALL THIS?

I made an easy mode for you. All you need to do is run one command and it will handle the rest for you. DJANGO POWER!

1. `cd` into the root `website/`
2. `pipenv run python setup.py`

There you go. Nice, huh?