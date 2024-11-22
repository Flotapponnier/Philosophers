#include "../../includes/philosopher.h"

void exit_philo(t_philo *philosopher)
{
    if (philosopher)
        free(philosopher);
    write(STDERR_FILENO, ERROR_MESSAGE, 6);
    exit(1);
}
