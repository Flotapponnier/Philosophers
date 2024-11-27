/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:26:40 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/27 16:28:19 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

static void	set_sim_stop_flag(t_table *table, bool state)
{
	set_bool(&table->sim_stop_lock, &table->sim_stop, state);
}

static bool	set_philo_die(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal_time) >= philo->table->time_to_die)
	{
		set_sim_stop_flag(philo->table, true);
		write_status(philo, DIED);
		safe_mutex(&philo->meal_time_lock, UNLOCK);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->num_of_philos)
	{
		safe_mutex(&table->philos[i]->meal_time_lock, LOCK);
		if (set_philo_die(table->philos[i]))
			return (true);
		if (table->times_should_eat != -1)
			if (table->philos[i]->times_ate < table->times_should_eat)
				all_ate_enough = false;
		safe_mutex(&table->philos[i]->meal_time_lock, UNLOCK);
		i++;
	}
	if (table->times_should_eat != -1 && all_ate_enough == true)
	{
		set_sim_stop_flag(table, true);
		return (true);
	}
	return (false);
}

void	*monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	if (table->times_should_eat == 0)
		return (NULL);
	set_sim_stop_flag(table, false);
	sim_start_synchro(table->start_time);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
