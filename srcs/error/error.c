/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:23:30 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/27 16:23:32 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

static void	free_forks(t_table *table)
{
	unsigned int	i;

	i = 0;
	if (table->fork_locks)
	{
		while (i < table->num_of_philos)
		{
			safe_mutex(&table->fork_locks[i], DESTROY);
			i++;
		}
		free(table->fork_locks);
	}
}

static void	free_philosophers(t_table *table)
{
	unsigned int	i;

	i = 0;
	if (table->philos)
	{
		while (i < table->num_of_philos)
		{
			if (table->philos[i])
			{
				safe_mutex(&table->philos[i]->meal_time_lock, DESTROY);
				free(table->philos[i]);
			}
			i++;
		}
		free(table->philos);
	}
}

static void	free_table(t_table *table)
{
	safe_mutex(&table->sim_stop_lock, DESTROY);
	safe_mutex(&table->write_lock, DESTROY);
	free(table);
}

bool	exit_philo(t_table *table, char *s)
{
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	if (table)
	{
		free_philosophers(table);
		free_forks(table);
		free_table(table);
	}
	return (false);
}
