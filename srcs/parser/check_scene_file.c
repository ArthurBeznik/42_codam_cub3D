#include <parser.h>

bool	check_scene_file_order(t_file_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (data->scene[i][0] == '1')
			return (error_msg("Scene file starts with map content"));
		i++;
	}
	return (true);
}
