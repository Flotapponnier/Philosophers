#include "../../includes/philosopher.h"

static void	*one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, GOT_FORK_1);
	philosopher_sleeping(philo->table, philo->table->time_to_die);
	write_status(philo, DIED);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	return (NULL);
}

void *philosopher(void *data)
{

	t_philo *philo = (t_philo*)data;
	bool simulation_false;

	simulation_false = get_bool(&philo->table->sim_stop_lock, &philo->table->sim_stop);
	if(philo->table->times_should_eat == 0)
		return (NULL);
	set_long(&philo->meal_time_lock, &philo->last_meal_time, philo->table->start_time);
	sim_start_synchro(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->num_of_philos == 1)
		return one_philo_routine(philo);
	if(philo->id % 2)
		philosopher_thinking(philo, true);
	while (has_simulation_stopped(philo->table) == false)
		{
			printf("%d \n", simulation_false);
			philosopher_eat(philo);	
			philosopher_thinking(philo, false);
			simulation_false = get_bool(&philo->table->sim_stop_lock, &philo->table->sim_stop);
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
	if (table->num_of_philos > 1)
	{
		printf("HOHHOH");
		if (pthread_create(&table->monitor, NULL,
				monitor, table) != 0)
			return (exit_philo(table, "Problem with creation of monitor thread"));
	}
	return true;
}
