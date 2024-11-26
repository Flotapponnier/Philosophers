#include "../../includes/philosopher.h"

void	philosopher_sleeping(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	bool simulation_false;

	simulation_false = get_bool(&table->sim_stop_lock, &table->sim_stop);
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
	write_status(philo, GOT_FORK_1);
	safe_mutex(&philo->table->fork_locks[philo->fork[1]], LOCK);
	write_status(philo, GOT_FORK_2);
	write_status(philo, EATING);
	set_long(&philo->meal_time_lock, &philo->last_meal_time, get_time_in_ms());
	philosopher_sleeping(philo->table, philo->table->time_to_eat);
	if (has_simulation_stopped(philo->table) == false)
		set_long(&philo->meal_time_lock, &philo->times_ate, philo->times_ate + 1);
	write_status(philo, SLEEPING);
	safe_mutex(&philo->table->fork_locks[philo->fork[1]], UNLOCK);
	safe_mutex(&philo->table->fork_locks[philo->fork[0]], UNLOCK);
	philosopher_sleeping(philo->table, philo->table->time_to_sleep);
}

void	*philosopher_thinking(t_philo *philo, bool silent)
{
	time_t time_thinking;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_thinking = (philo->table->time_to_die
			- (get_time_in_ms() - philo->last_meal_time)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_thinking < 0)
		time_thinking= 0;
	if (time_thinking == 0 && silent == true)
		time_thinking = 1;
	if (time_thinking > 600)
		time_thinking = 200;
	if(silent == false)
		write_status(philo, THINKING);
	philosopher_sleeping(philo->table, time_thinking);
	return (philo);
}
