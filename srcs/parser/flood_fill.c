#include <parser.h>

bool	is_valid(int y, int x, char **map, int rows)
{
	int	cols;

	cols = ft_strlen(map[y]);
	if (y >= 0 && y < rows && x >= 0 && x < cols
		&& (map[y][x] == '0' || map[y][x] == ' '))
		return (true);
	return (false);
}

void	flood_fill(int y, int x, t_map_data *map_data, bool *is_enclosed)
{
	int	rows;
	int	cols;

	rows = map_data->rows_count;
	cols = ft_strlen(map_data->copy[y]);
	if (y == 0 || y == map_data->rows_count - 1 || x == 0 || x == cols - 1)
	{
		*is_enclosed = false;
		return ;
	}
	map_data->copy[y][x] = 'V';
	if (is_valid(y - 1, x, map_data->copy, rows))
		flood_fill(y - 1, x, map_data, is_enclosed);
	if (is_valid(y + 1, x, map_data->copy, rows))
		flood_fill(y + 1, x, map_data, is_enclosed);
	if (is_valid(y, x - 1, map_data->copy, rows))
		flood_fill(y, x - 1, map_data, is_enclosed);
	if (is_valid(y, x + 1, map_data->copy, rows))
		flood_fill(y, x + 1, map_data, is_enclosed);
}
