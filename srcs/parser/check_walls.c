
#include <parser.h>

bool	check_valid_char(char element)
{
	if (element != '1' && element != ' ')
		return (false);
	return (true);
}

int		get_rows_nb(char **map)
{
	int y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

bool	check_adjacent_rows(char **map, int columns, int y)
{
	int	x;

	x = 1;
	while (x < columns - 1)
	{
		if (!check_valid_char(map[y][x]))
			return (false);
		x++;
	}
	return (true);
}

bool	check_adjacent_columns(char **map, int columns, int y)
{
	if (!check_valid_char(map[y][1]) || !check_valid_char(map[y][columns - 2]))
		return (false);
	return (true);
}

bool	check_top_bottom(char **map, int columns, int y)
{
	int	x;

	x = 0;
	while (x < columns)
	{
		if (!check_valid_char(map[y][x]))
			return (false);
		x++;
	}
	return (true);
}

bool	check_left_right(char **map, int columns, int y)
{
	if (!check_valid_char(map[y][0]) || !check_valid_char(map[y][columns - 1]))
		return (false);
	return (true);
}

bool	check_walls(char **map_content)
{
	int	rows;
	int	columns;
	int	y;
	int	x;

	if (!map_content)
		return (false);
	rows = get_rows_nb(map_content);
	y = 0;
	while (y < rows - 1)
	{
		columns = ft_strlen(map_content[y]);
		if (y == 0 || y == rows - 1) 
		{
			if (!check_top_bottom(map_content, columns, y))
				return (false);
		}
		else if (y == 1 || y == rows - 2)
		{
			if (!check_adjacent_rows(map_content, columns, y))
				return (false);
		}
		else
		{
			if (!check_left_right(map_content, columns, y))
				return (false);
			if (!check_adjacent_columns(map_content, columns, rows))
				return (false);
		}
		y++;
	}
	return (true);
}
