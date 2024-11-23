#include "../../includes/philosopher.h"

void exit_philo(t_philo *philosopher, char *s)
{
    if (philosopher)
        free(philosopher);
    write(STDERR_FILENO, ERROR_MESSAGE, 6);
	ft_putstr_fd(s, STDERR_FILENO);
    exit(1); 
}
