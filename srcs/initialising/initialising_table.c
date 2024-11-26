/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:18:25 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/26 15:55:42 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!forks)
		return (false);
	i = 0;
	while (i < table->num_of_philos)
	{
		if (!safe_mutex(&forks[i], INIT))
			return (false);
		i++;
	}
	return (forks);
}

static void	assign_forks(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->num_of_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->num_of_philos;
		philo->fork[1] = philo->id;
	}
}

static bool	init_philosophers(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!philos)
		return (false);
	table->philos = philos;
	i = 0;
	while (i < table->num_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (false);
		if (!safe_mutex(&philos[i]->meal_time_lock, INIT))
			return (false);
		philos[i]->table = (table);
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]); i++;
	}
	return (true);
}

static bool	init_global_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (!safe_mutex(&table->sim_stop_lock, INIT))
		return false;
	if (!safe_mutex(&table->write_lock, INIT))
		return false;
	return (true);
}

bool initialising_table(int ac, char **av, t_table **table)
{

    (*table) = malloc(sizeof(t_table));
    if (!(*table))
        return (exit_philo(NULL, ERROR_MALLOC), NULL);
 	(*table)->num_of_philos = myphilo_atoi(av[1]);
    (*table)->time_to_die = myphilo_atoi(av[2]);
    (*table)->time_to_eat = myphilo_atoi(av[3]);
    (*table)->time_to_sleep = myphilo_atoi(av[4]);
    (*table)->times_should_eat = -1;
    if (ac == 6) (*table)->times_should_eat = myphilo_atoi(av[5]);
    if(!init_philosophers(*table))
		return(exit_philo((*table), ERROR_INIT_PHILOS));
    if (!init_global_mutexes((*table)))
        return (exit_philo((*table), ERROR_INIT_MUTEX));
    (*table)->sim_stop = false;

    return true;
}
