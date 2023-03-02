#include <utils.h>

int	ft_count_rows(const char **scene)
{
	int	i;

	if (!scene)
		return (ERROR);
	i = 0;
	while (scene[i])
		i++;
	return (i);
}
