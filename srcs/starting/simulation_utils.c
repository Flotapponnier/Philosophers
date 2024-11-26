#include "../../includes/philosopher.h"



bool	has_simulation_stopped(t_table *table)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&table->sim_stop_lock);
	if (table->sim_stop == true)
		r = true;
	pthread_mutex_unlock(&table->sim_stop_lock);
	return (r);
}
/* print_status:
*	Prints a philosopher's status in plain text as required by the project
*	subject:
*		timestamp_in_ms X status
*/
static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->id + 1, str);
}

/* write_status:
*	Prints the status of a philosopher as long as the simulation is
*	still active. Locks the write mutex to avoid intertwined messages
*	from different threads.
*
*	If DEBUG_FORMATTING is set to 1 in philo.h, the status will
*	be formatted with colors and extra information to help with debugging.
*	Otherwise the output will be the regular format required by the project
*	subject.
*/
void	write_status(t_philo *philo, t_status status)
{
	static int die = 0;

	pthread_mutex_lock(&philo->table->write_lock);
	if (!die)
	{
	if (status == DIED)
	{
		die = 1;
		print_status(philo, "died");
	}
	else if (status == EATING)
	{
		print_status(philo, "is eating");
		printf("number eating : %ld", philo->times_ate);
		if(philo->times_ate == philo->table->times_should_eat)
				die =1;
	}
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == GOT_FORK_1 || status == GOT_FORK_2)
		print_status(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->table->write_lock);
}
