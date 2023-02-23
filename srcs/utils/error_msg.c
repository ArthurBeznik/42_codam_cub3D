
#include <utils.h>

bool	error_msg(const char *message)
{
	ft_putstr_fd("Error", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_putchar_fd('\t', STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (false);
}
