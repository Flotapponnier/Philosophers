#include "../../includes/philosopher.h"

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
