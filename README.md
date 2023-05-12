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

- W/S or ARROW UP/DOWN: Move

- A/D or ARROW LEFT/RIGHT: Rotate

## Configuration

#### Map extension
Maps have to be of the **.cub** extension!

#### Map configuration
The following identifiers can be adjusted:
- North texture: "NO *path_to_texture*"
- South texture: "SO *path_to_texture*"
- West texture: "WE *path_to_texture*"
- East texture: "EA *path_to_texture*"
- Floor color: "F *colorcode in RGB*"
- Ceiling color: "C *colorcode in RGB*"

Information can be in any order with newlines in between. The map ***has*** to be the last element in the map file.

#### Maps

Maps can consist of spaces (**NOT tabs or other whitespaces**) and a few possible characters:
- `0`: Floor
- `1`: Walls
- `NSEW`: player starting position (letter indicates starting orientation)

A map is considered to be valid if it respects:
- Floors have to be surrounded by walls
- Maps can only have a single starting position
