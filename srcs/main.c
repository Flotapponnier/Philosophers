#include "../includes/philosopher.h"


void print_table(t_table *table)
{
    unsigned int i;

    // Check table initialization
    if (!table)
    {
        printf("Error: Table not initialized.\n");
        return;
    }
    printf("Table Initialized:\n");
    printf("  Number of Philosophers: %u\n", table->num_of_philos);
    printf("  Time to Die: %ld ms\n", table->time_to_die);
    printf("  Time to Eat: %ld ms\n", table->time_to_eat);
    printf("  Time to Sleep: %ld ms\n", table->time_to_sleep);
    printf("  Times Philosophers Should Eat: %d\n", table->times_should_eat);
    printf("  Simulation Stop Flag: %s\n", table->sim_stop ? "True" : "False");
    // Check fork locks
    if (!table->fork_locks)
    {
        printf("Error: Fork locks not initialized.\n");
        return;
    }
    printf("  Fork Locks Initialized: Yes\n");
    // Check philosophers
    if (!table->philos)
    {
        printf("Error: Philosophers not initialized.\n");
        return;
    }
    printf("Philosophers Initialized:\n");
    for (i = 0; i < table->num_of_philos; i++)
    {
        t_philo *philo = table->philos[i];
        if (!philo)
        {
            printf("  Philosopher %u: Error (Not Initialized)\n", i);
            continue;
        }
        printf("  Philosopher %u:\n", i + 1);
        printf("    ID: %u\n", philo->id);
        printf("    Times Ate: %d\n", philo->times_ate);
        printf("    Last Meal Time: %lld\n", philo->last_meal_time);
        printf("    Forks: [%d, %d]\n", philo->fork[0], philo->fork[1]);
    }
    // Check global mutexes
    printf("Global Mutexes:\n");
    printf("  Simulation Stop Lock: Initialized\n");
    printf("  Write Lock: Initialized\n");
}


int main(int argc, char **argv)
{
	t_table *table;
	

    if(!is_valid_input(argc, argv))
		return (1);
	table = initialising_table(argc, argv);
	ft_printf("valid argument");
	print_table(table);
	printf("Hello");
	starting_simulation(table);
    return (0);
}
