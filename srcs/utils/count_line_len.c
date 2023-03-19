#include <utils.h>

int	get_max_line_len(const char **map)
{
	int	y;
	int	max_len;
	int	curr_len;

	if (!map)
		return (ERROR);
	y = 0;
	max_len = 0;
	curr_len = 0;
	while (map[y])
	{
		curr_len = ft_strlen(map[y]);
		if (curr_len > max_len)
			max_len = curr_len;
		y++;
	}
	return (max_len);
}
