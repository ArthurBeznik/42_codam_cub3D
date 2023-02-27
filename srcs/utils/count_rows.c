
#include <utils.h>

size_t	ft_count_rows(char **scene)
{
	size_t i;

	i = 0;
	while (scene[i])
		i++;
	return (i);
}
