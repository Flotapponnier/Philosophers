/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:06 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/27 16:36:08 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

bool	check_simulation(t_table *table)
{
	bool	check_simulation;

	check_simulation = false;
	safe_mutex(&table->sim_stop_lock, LOCK);
	if (table->sim_stop == true)
		check_simulation = true;
	safe_mutex(&table->sim_stop_lock, UNLOCK);
	return (check_simulation);
}

static void	print_status(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->id
		+ 1, str);
}

void	write_status(t_philo *philo, t_status status)
{
	static int	die = 0;

	safe_mutex(&philo->table->write_lock, LOCK);
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
			if (philo->times_ate == philo->table->times_should_eat)
				die = 1;
		}
		else if (status == SLEEPING)
			print_status(philo, "is sleeping");
		else if (status == THINKING)
			print_status(philo, "is thinking");
		else if (status == GOT_FORK_1 || status == GOT_FORK_2)
			print_status(philo, "has taken a fork");
	}
	safe_mutex(&philo->table->write_lock, UNLOCK);
}
