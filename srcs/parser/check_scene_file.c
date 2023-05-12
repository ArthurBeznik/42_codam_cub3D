#include <parser.h>

bool	check_scene_file_order(t_file_data *data, const int nb_rows)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (data->scene[i][0] == '1')
			return (error_msg("Scene file starts with map content"));
		i++;
	}
	if (data->scene[nb_rows - 1][0] != '1')
		return (error_msg("Scene file does not end with map content"));
	return (true);
}
