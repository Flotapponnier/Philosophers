#include "../../includes/philosopher.h"

static void free_forks(t_table *table)
{
    unsigned int i = 0;

    if (table->fork_locks)
    {
        while (i < table->num_of_philos)
        {
            pthread_mutex_destroy(&table->fork_locks[i]);
            i++;
        }
        free(table->fork_locks);
    }
}

static void free_philosophers(t_table *table)
{
    unsigned int i = 0;

    if (table->philos)
    {
        while (i < table->num_of_philos)
        {
            if (table->philos[i])
            {
                pthread_mutex_destroy(&table->philos[i]->meal_time_lock);
                free(table->philos[i]);
            }
            i++;
        }
        free(table->philos);
    }
}

static void free_table(t_table *table)
{
    pthread_mutex_destroy(&table->sim_stop_lock);
    pthread_mutex_destroy(&table->write_lock);
    free(table);
}

bool exit_philo(t_table *table, char *s)
{
    if (s)
        ft_putstr_fd(s, STDERR_FILENO);
    if (table)
    {
        free_philosophers(table);
        free_forks(table);
        free_table(table);
    }
    return (false);
}
