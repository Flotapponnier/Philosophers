#include "../../includes/philosopher.h"

static void	*one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	philosopher_sleeping(philo->table, philo->table->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

void *philosopher(void *data) {

	t_philo *philo = (t_philo*)data;  // Cast the data to the correct type (philosopher)
	
	if(philo->table->times_should_eat == 0)
		return (NULL);
	set_long(&philo->meal_time_lock, &philo->last_meal_time, philo->table->start_time);
	sim_start_synchro(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->num_of_philos == 1)
		return one_philo_routine(philo);
	//TO DO : ONE PHILO
	if(philo->id % 2)
		philosopher_thinking(philo);
	    while (stop_simulation() != 0)
	{
			philosopher_eat(philo);	
			philosopher_thinking(philo);
	}
	return (NULL);
}

bool	starting_simulation(t_table *table)
{
    unsigned int i;

	printf("Hello");
    if(table->times_should_eat == 0)
			return (NULL); 
    table->start_time = get_time_in_ms() + (table->num_of_philos * 2 * 10);
    i = 0;
    while (i < table->num_of_philos)
    {
	if (!safe_thread(&table->philos[i]->thread, philosopher, table->philos[i], CREATE))
            return (exit_philo(table, "Problem with creation of thread"));
        printf("Thread philosopher %d created with success\n", i + 1);
        i++;
    }
	i = 0;
	while(i < table->num_of_philos)
	{
		if (!safe_thread(&table->philos[i]->thread, NULL, NULL, JOIN))
			return (exit_philo(table, "Problem with joining thread"));
		printf("Thread philosopher %d Join succesfully\n", table->philos[i]->id);
		i++;	
	}
	return true;
}
