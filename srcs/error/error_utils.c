#include "../../includes/philosopher.h"

int ft_strlen (char *str)
{
	int i = 0;

	while(str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}
