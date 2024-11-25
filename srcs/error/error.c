#include "../../includes/philosopher.h"

void exit_philo(t_table *table, char *s)
{
    if (table)
        free(table);
    write(STDERR_FILENO, ERROR_MESSAGE, 6);
	ft_putstr_fd(s, STDERR_FILENO);
    exit(1); 
}
