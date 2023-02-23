
#include <parser.h>
#include <stdio.h> // ? testing

int		get_size(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

bool	check_walls(char **map_content)
{
	int x;
	int y;
	int	line_len;
	int	y_size;

	y_size = get_size(map_content);
	// printf("map size: %d\n", y_size); // ? testing
	y = 0;
	while (map_content[y])
	{
		line_len = ft_strlen(map_content[y]);
		// printf("line_len: %d\n", line_len); // ? testing
		x = 0;
		while (map_content[y][x])
		{
			// printf("char: %c\n", map_content[y][x]);
			if (y == 0 && (map_content[y][x] != '1' && map_content[y][x] != ' ')) // first line
				return (false);
			else if (map_content[y][0] != '1' && map_content[y][line_len - 1] != '1') // other lines
				return (false);
			else if (y == y_size - 1 && (map_content[y][x] != '1' && map_content[y][x] != ' ')) // last line
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}


