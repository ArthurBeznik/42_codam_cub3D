
#include <parser.h>

bool is_valid(int y, int x, char **map, int rows)
{
	int cols;
	
	cols = ft_strlen(map[y]);
	if (y >= 0 && y < rows && x >= 0 && x < cols && map[y][x] == '0')
		return (true);
	return (false);
}

void flood_fill(int y, int x, char **map, bool *is_enclosed, int rows)
{
	int cols;
	
	cols = ft_strlen(map[y]);
	if (y == 0 || y == rows - 1 || x == 0 || x == cols - 1 || map[y][x] == '1')
	{
		*is_enclosed = false;
		return ;
	}
	map[y][x] = 'V';
	if (is_valid(y - 1, x, map, rows))
		flood_fill(y - 1, x, map, is_enclosed, rows);
	if (is_valid(y + 1, x, map, rows))
		flood_fill(y + 1, x, map, is_enclosed, rows);
	if (is_valid(y, x - 1, map, rows))
		flood_fill(y, x - 1, map, is_enclosed, rows);
	if (is_valid(y, x + 1, map, rows))
		flood_fill(y, x + 1, map, is_enclosed, rows);
}
