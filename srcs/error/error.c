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

bool exit_philo(t_table *table, char *s)
{
    if (table)
        free(table);
    write(STDERR_FILENO, ERROR_MESSAGE, 6);
	ft_putstr_fd(s, STDERR_FILENO);
	return (false);
}
