#include "../../includes/philosopher.h"

bool	has_simulation_stopped(t_table *table)
{
	table->start_time++;
	table->start_time--;
	return (false);
}

void	philosopher_sleeping(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (has_simulation_stopped(table))
			break ;
		usleep(100);
	}
}

void philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[0]]);
	write_status(philo, false, GOT_FORK_1);
	pthread_mutex_lock(&philo->table->fork_locks[philo->fork[1]]);
	write_status(philo, false, GOT_FORK_2);
	write_status(philo, false, EATING);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philosopher_sleeping(philo->table, philo->table->time_to_eat);
	if (has_simulation_stopped(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->times_ate += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	write_status(philo, false, SLEEPING);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->fork[0]]);
	philosopher_sleeping(philo->table, philo->table->time_to_sleep);
}
void	*philosopher_thinking(t_philo *philo)
{
	time_t time_thinking;
	pthread_mutex_lock(&philo->meal_time_lock);
	time_thinking = (philo->table->time_to_die - (get_time_in_ms() - philo->last_meal_time) - philo->table->time_to_eat / 2); // to understand
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_thinking < 0)
		time_thinking= 0;
	if (time_thinking > 600)
		time_thinking = 200;
	printf("Philosopher %d is thinking...\n", philo->id);
	write_status(philo, false, THINKING);
	philosopher_sleeping(philo->table, time_thinking);
	return (philo);
}

void *philosopher(void *data) {

	t_philo *philo = (t_philo*)data;  // Cast the data to the correct type (philosopher)
	//

	if(philo->id % 2)
		philosopher_thinking(philo);
    while (stop_simulation() != 0)
	{
			philosopher_eat(philo);	
			philosopher_thinking(philo);
	}
	return (philosopher);
}

bool	starting_simulation(t_table *table)
{
    unsigned int i;

	printf("Hello");
    if(table->times_should_eat == 0)
			return (NULL); 
	// Set the start time for the simulation
    table->start_time = get_time_in_ms() + (table->num_of_philos * 2 * 10);
    i = 0;

    // Create a thread for each philosopher
    while (i < table->num_of_philos)
    {
        if (pthread_create(&table->philos[i]->thread, NULL, philosopher, table->philos[i]) != 0)
            return (exit_philo(table, "Problem with creation of thread"), true);
        printf("Thread philosopher %d created with success\n", i + 1);

        i++;
    }
	i = 0;
	while(i < table->num_of_philos)
	{
		if(pthread_join(table->philos[i]->thread, NULL) != 0)
			return (exit_philo(table, "Problem with joining thread"), true);
		printf("Thread philosopher %d Join succesfully\n", table->philos[i]->id);
		i++;	
	}
	return true;
}
