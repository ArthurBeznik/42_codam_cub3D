#include <parser.h>

bool	check_ext(char *file_name, char	*extension)
{
	int	ext_len;
	int	name_len;

	if (!extension)
		return (error_msg("No extension given"));
	if (!file_name)
		return (error_msg("No file name given"));
	ext_len = ft_strlen(extension);
	name_len = ft_strlen(file_name);
	if (ext_len == ERROR || name_len == ERROR)
		return (error_msg("strlen"));
	while (ext_len > 0)
	{
		if (file_name[name_len--] != extension[ext_len--])
			return (error_msg("Incorrect file extension"));
	}
	return (true);
}
