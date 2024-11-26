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
	safe_mutex(&philo->table->fork_locks[philo->fork[0]], LOCK);
	write_status(philo, false, GOT_FORK_1);
	safe_mutex(&philo->table->fork_locks[philo->fork[1]], LOCK);
	write_status(philo, false, GOT_FORK_2);
	write_status(philo, false, EATING);
	set_long(&philo->meal_time_lock, &philo->last_meal_time, get_time_in_ms());
	philosopher_sleeping(philo->table, philo->table->time_to_eat);
	if (has_simulation_stopped(philo->table) == false)
		set_long(&philo->meal_time_lock, &philo->times_ate, philo->times_ate + 1);
	write_status(philo, false, SLEEPING);
	safe_mutex(&philo->table->fork_locks[philo->fork[1]], UNLOCK);
	safe_mutex(&philo->table->fork_locks[philo->fork[0]], UNLOCK);
	philosopher_sleeping(philo->table, philo->table->time_to_sleep);
}

void	*philosopher_thinking(t_philo *philo)
{
	time_t time_thinking;
	time_t last_meal_time;

	last_meal_time = get_long(&philo->meal_time_lock, &philo->last_meal_time);
	time_thinking = philo->table->time_to_die - (get_time_in_ms() - last_meal_time) - philo->table->time_to_eat / 2;
	if (time_thinking < 0)
		time_thinking= 0;
	if (time_thinking > 600)
		time_thinking = 200;
	printf("Philosopher %d is thinking...\n", philo->id);
	write_status(philo, false, THINKING);
	philosopher_sleeping(philo->table, time_thinking);
	return (philo);
}
