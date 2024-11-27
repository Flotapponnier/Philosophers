/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_simulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:32:16 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/27 16:32:20 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

void	stop_simulation(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (!safe_thread(&table->philos[i]->thread, NULL, NULL, JOIN))
			exit_philo(table, ERROR_TPHILO);
		i++;
	}
	if (table->num_of_philos > 1)
	{
		if (!safe_thread(&table->monitor, NULL, NULL, JOIN))
			exit_philo(table, ERROR_TPHILO);
	}
	exit_philo(table, NULL);
}

static void	*one_philo_routine(t_philo *philo)
{
	safe_mutex(&philo->table->fork_locks[philo->fork[0]], LOCK);
	write_status(philo, GOT_FORK_1);
	philosopher_sleeping(philo->table, philo->table->time_to_die);
	write_status(philo, DIED);
	safe_mutex(&philo->table->fork_locks[philo->fork[0]], UNLOCK);
	return (NULL);
}

void	*philosopher(void *data)
{
	t_philo	*philo;
	bool	simulation_false;

	philo = (t_philo *)data;
	simulation_false = get_bool(&philo->table->sim_stop_lock,
			&philo->table->sim_stop);
	if (philo->table->times_should_eat == 0)
		return (NULL);
	set_long(&philo->meal_time_lock, &philo->last_meal_time,
		philo->table->start_time);
	sim_start_synchro(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->num_of_philos == 1)
		return (one_philo_routine(philo));
	if (philo->id % 2)
		philosopher_thinking(philo, true);
	while (check_simulation(philo->table) == false)
	{
		philosopher_eat(philo);
		philosopher_thinking(philo, false);
		simulation_false = get_bool(&philo->table->sim_stop_lock,
				&philo->table->sim_stop);
	}
	return (NULL);
}

bool	starting_simulation(t_table *table)
{
	unsigned int	i;

	if (table->times_should_eat == 0)
		return (NULL);
	table->start_time = get_time_in_ms() + (table->num_of_philos * 2 * 10);
	i = 0;
	while (i < table->num_of_philos)
	{
		if (!safe_thread(&table->philos[i]->thread, philosopher,
				table->philos[i], CREATE))
			return (exit_philo(table, ERROR_TPHILO));
		i++;
	}
	if (table->num_of_philos > 1)
	{
		if (!safe_thread(&table->monitor, monitor, table, CREATE))
			return (exit_philo(table, ERROR_TMONITOR));
	}
	return (true);
}
