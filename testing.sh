#!/bin/bash

EXE="cub3D"

# Colors
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
NC='\033[0m' # No Color

# Wait for user key press
#	-n 1 option reads only one character, 
#	-s option suppresses printing the typed character to the screen, 
#	-r option disables backslash escape interpretation, and 
#	-p option prompts the user with the given message before waiting for input.
function wait_key {
	read -n 1 -s -r -p "Press any key to continue..."
}

# Check the exit code
function check_exit {
	if [ $EXIT_CODE -eq 0 ]; then
		echo -e "${GREEN}cub3D exited successfully.${NC}\n"
	else
		echo -e "${RED}cub3D exited with code $EXIT_CODE.${NC}\n"
	fi
}

# Check if the cub3D executable exists
if [ ! -f $EXE ]; then
  echo -e "${RED}Error${NC}: $EXE executable not found.\n"
  exit 1
fi

# Iterate over all files in the scenes directory
# Execute cub3D with current scene file
for file in ./scenes/*; do
	echo -e "\n${BLUE}Running cub3D with $file${NC}\n"
	./cub3D "$file"
	EXIT_CODE=$?
	check_exit
	wait_key
done

