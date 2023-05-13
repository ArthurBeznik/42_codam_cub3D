
# cub3D - My first RayCaster with miniLibX

This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.

## Collaborator

**[@Zangetsu89](https://github.com/Zangetsu89)**

## Usage

### Installation
```bash
git clone git@github.com:ArthurBeznik/42_codam_cub3D.git
```
#### Install MLX42 Submodule
Since we are using MLX42 as a submodule, you will have to run the following commands:
```bash
cd libs/MLX42
git submodule init
git submodule update
```
You should now have the MLX42 lib installed, you can now go back to the main folder, or run:
```bash
cd ../..
```
### Create the binary
```bash
make
```

### Run the binary
```bash
./cub3D <path/to/map/file>
```
By default, a few maps can be found in the `scenes/` folder.

## Controls

- `W/S` or `ARROW UP/DOWN`: Move
- `A/D` or `ARROW LEFT/RIGHT`: Rotate

## Configuration

#### Scene file extension
Scene files have to be of the **.cub** extension.

#### Map rules
The map must be composed of only 6 possible characters: 
- `0`: an empty space
- `1`: a wall
- `N`, `S`, `E` or `W`: the player’s start position and spawning orientation
The map **must** be closed/surrounded by walls.

This is a simple valid map:
```bash
111111
100101
101001
1100N1
111111
```

#### Scene file configuration
- Except for the map content, each type of element can be separated by one or more empty line(s).
- Except for the map content which always has to be the last, each type of element can be set in any order in the file.
- Except for the map, each type of information from an element can be separated by one or more space(s).
- Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as:
    - North texture: `NO ./path_to_texture`
    - South texture: `SO ./path_to_texture`
    - West texture: `WE ./path_to_texture`
    - East texture: `EA ./path_to_texture`
    - Floor color: `F 255,0,0` (R,G,B colors in range [0,255])
    - Ceiling color: `C 0,0,255` (R,G,B colors in range [0,255])
