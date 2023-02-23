
// #include <stdio.h>
// #include <stdlib.h>

// #include <stdbool.h>

// #define ROWS 10
// #define COLS 10

// // Define the map
// char map[ROWS][COLS] = {
//     {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
//     {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
//     {'#', '.', '#', '#', '.', '#', '#', '#', '.', '#'},
//     {'#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
//     {'#', '.', '#', '.', '#', '.', '.', '#', '.', '#'},
//     {'#', '.', '#', '.', '#', '.', '.', '#', '.', '#'},
//     {'#', '.', '#', '.', '#', '.', '.', '#', '.', '#'},
//     {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
//     {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
//     {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
// };

// bool isTest(int row, int col)
// {
// 	if (map[row][col] == '#' || row < 0 || row >= ROWS || col < 0 || col >= COLS) {
//         return true;
//     }
//     map[row][col] = 'x';
// 	return (false);
// }

// // Function to check if a map is enclosed
// bool isEnclosed(int row, int col) {
//     // If the current position is a wall or is out of bounds, it is enclosed
//     if (map[row][col] == '#' || row < 0 || row >= ROWS || col < 0 || col >= COLS) {
//         return true;
//     }

//     // Mark the current position as visited
//     map[row][col] = 'x';

//     // Recursively check if the surrounding positions are enclosed
//     bool top = isTest(row - 1, col);
//     bool bottom = isTest(row + 1, col);
//     bool left = isTest(row, col - 1);
//     bool right = isTest(row, col + 1);

//     // If any of the surrounding positions are not enclosed, the current position is not enclosed
//     if (!top || !bottom || !left || !right) {
//         return false;
//     }

//     // If all surrounding positions are enclosed, the current position is enclosed
//     return true;
// }

// int main() {
//     // Starting position
//     int startRow = 0;
//     int startCol = 0;

//     // Check if the map is enclosed starting from the starting position
//     bool enclosed = isEnclosed(startRow, startCol);

//     // Output the result
//     if (enclosed) {
//         printf("The map is enclosed starting from (%d, %d).\n", startRow, startCol);
//     } else {
//         printf("The map is not enclosed starting from (%d, %d).\n", startRow, startCol);
//     }

//     return 0;
// }

#include <stdio.h>

// Function to fill a contiguous region of pixels with a given color
void flood_fill(int x, int y, char map[][10], int width, int height)
{
    // Check if the current pixel is within the bounds of the image
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    // Check if the current pixel is of the old color
    if (map[y][x] != '#') {
        return ;
    }

    // Fill the current pixel with the new color
    map[y][x] = 'V';

    // Fill the adjacent pixels recursively
    flood_fill(x + 1, y, map, width, height);
    flood_fill(x - 1, y, map, width, height);
    flood_fill(x, y + 1, map, width, height);
    flood_fill(x, y - 1, map, width, height);
}

int main()
{
    // int map[10][10] = {
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    //     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    //     {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //     {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    // };
	char map[10][10] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '.', '#', '#', '#', '.', '#'},
    {'#', '.', '#', '.', '.', '.', '.', '#', '.', '#'},
    {'#', '.', '#', '.', '#', '.', '.', '#', '.', '#'},
    {'#', '.', '#', '.', '#', '.', '.', '#', '.', '#'},
    {'#', '.', '#', '.', '#', '.', '.', '#', '.', '#'},
    {'#', '.', '.', '.', '#', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
	};

    int width = 10;
    int height = 10;


    // Fill the region starting from (1, 1)
    flood_fill(0, 0, map, width, height);

    // Print the updated image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }

    return 0;
}