# miniRT
* 42tokyo's raycasting project

### set up
* using docker (not sure about norminette)
* `docker compose run minirt` then `make` if necessary to create executable `./miniRT`
* provides maps by arg like `./miniRT ./maps/xyz.rt`

### Ubuntu
* you have to `make` in docker to make `./miniRT` then use it in local environment.

### Mac
* you need `XQuartz` installed (`brew install --casks XQuartz`)
* enable by checking `settings/security/allow connections from network clients`
* start the program and open XQuartz's terminal with `application/terminal` and key in `xhost + 127.0.0.1`
(many thanks to this [repo](https://github.com/jo-tan/42_cub3D))

