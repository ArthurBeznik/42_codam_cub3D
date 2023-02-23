
#include <parser.h>

int		st_get_rows_nb(char **map)
{
	int y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

int	check_prev(int prev_y, int prev_x, int y, int x)
{
	if (prev_y == y && prev_x == x - 1)
		return (7);
	return (0);
}

bool	moore_neighbor(char **map)
{
	int	rows;
	int	columns;
	int	y;
	int	x;
	int	start_x;
	int	start_y;
	int curr_x;
	int curr_y;
	int moore_x;
	int moore_y;
	bool stop;
	bool found;
	int prev_x;
	int prev_y;
	int	m_prev_x;
	int	m_prev_y;

	stop = true;
	found = false;
	if (!map)
		return (false);
	rows = st_get_rows_nb(map);
	columns = ft_strlen(map[0]);
	y = 0;
	while (y < rows - 1)
	{
		x = 0;
		while (x < columns - 1)
		{
			if (map[y][x] == '1')
			{
				moore_x = x;
				moore_y = y;
				start_x = x;
				start_y = y;
				curr_x = x;
				curr_y = y;
				map[y][x] = 'V';
				while (stop && !found)
				{
					int jump_to = check_prev(m_prev_y, m_prev_x, curr_y, curr_x);
					if (map[curr_y - 1][curr_x] == '1' && (jump_to == 1 || jump_to == 0))
					{
						m_prev_y = curr_y;
						m_prev_x = curr_x;
						prev_x = curr_x;
						prev_y = curr_y;
						curr_y = curr_y - 1;
						map[curr_y][curr_x] = 'V';
					}
					else if (map[curr_y - 1][curr_x - 1] == '1' && (jump_to == 2 || jump_to == 0))
					{
						m_prev_y = curr_y - 1;
						m_prev_x = curr_x;
						prev_x = curr_x;
						prev_y = curr_y;
						curr_y = curr_y - 1;
						curr_x = curr_x - 1;
						map[curr_y][curr_x] = 'V';
					}
					else if (map[curr_y][curr_x - 1] == '1' && (jump_to == 3 || jump_to == 0))
					{
						m_prev_y = curr_y - 1;
						m_prev_x = curr_x - 1;
						prev_x = curr_x;
						prev_y = curr_y;
						curr_y = curr_y;
						curr_x = curr_x - 1;
						map[curr_y][curr_x] = 'V';
					}
					else if (map[curr_y + 1][curr_x - 1] == '1' && (jump_to == 4 || jump_to == 0))
					{
						m_prev_y = curr_y;
						m_prev_x = curr_x - 1;
						prev_x = curr_x;
						prev_y = curr_y;
						curr_y = curr_y + 1;
						curr_x = curr_x - 1;
						map[curr_y][curr_x] = 'V';
					}
					else if (map[curr_y + 1][curr_x] == '1' && (jump_to == 5 || jump_to == 0))
					{
						m_prev_y = curr_y + 1;
						m_prev_x = curr_x - 1;
						prev_x = curr_x;
						prev_y = curr_y;
						curr_y = curr_y + 1;
						curr_x = curr_x;
						map[curr_y][curr_x] = 'V';
					}
					else if (map[curr_y + 1][curr_x + 1] == '1' && (jump_to == 6 || jump_to == 0))
					{
						m_prev_y = curr_y + 1;
						m_prev_x = curr_x;
						prev_x = curr_x;
						prev_y = curr_y;
						curr_y = curr_y + 1;
						curr_x = curr_x + 1;
						map[curr_y][curr_x] = 'V';
					}
					else if (map[curr_y][curr_x + 1] == '1' && (jump_to == 7 || jump_to == 0)) // ! here
					{
						m_prev_y = curr_y - 1; // good
						m_prev_x = curr_x + 1; // good
						prev_x = curr_x;
						prev_y = curr_y;
						curr_y = curr_y;
						curr_x = curr_x + 1;
						map[curr_y][curr_x] = 'V';
					}
					else if (map[curr_y - 1][curr_x + 1] == '1' && (jump_to == 8 || jump_to == 0))
					{
						m_prev_y = curr_y;
						m_prev_x = curr_x + 1;
						prev_x = curr_x;
						prev_y = curr_y;
						curr_y = curr_y - 1;
						curr_x = curr_x + 1;
						map[curr_y][curr_x] = 'V';
					}
					else
					{
						stop = false;
					}
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}
