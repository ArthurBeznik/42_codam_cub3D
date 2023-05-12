#include <parser.h>

bool	check_color_range(const int r, const int g, const int b)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		return (true);
	return (false);
}

bool	check_rgb_values(const char **rgb_values)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb_values[i][j])
		{
			if (!ft_isdigit(rgb_values[i][j]) && !(rgb_values[i][j] == ' '))
				return (error_msg("Invalid color value"));
			j++;
		}
		i++;
	}
	return (true);
}
