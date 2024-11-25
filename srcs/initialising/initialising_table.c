/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialising_table.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:18:25 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/24 16:50:55 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

static pthread_mutex_t	*init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!forks)
		return (exit_philo(NULL, NULL), NULL);
	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (exit_philo(NULL, NULL), NULL);
		i++;
	}
	return (forks);
}

/* assign_forks:
*	Assigns two fork ids to each philosopher. Even-numbered philosophers
*	get their fork order switched. This is because the order in which
*	philosophers take their forks matters.
*
*	For example with 3 philos:
*		Philo #1 (id: 0) will want fork 0 and fork 1
*		Philo #2 (id: 1) will want fork 1 and fork 2
*		Philo #3 (id: 2) will want fork 2 and fork 0
*	If philo #1 takes fork 0, philo #2 takes fork 1 and philo #3 takes fork 2,
*	there is a deadlock. Each will be waiting for their second fork which is
*	in use by another philo.
*
*	Making even id philos "left-handed" helps:
*		Philo #1 (id: 0) takes fork 1 and then fork 0
*		Philo #2 (id: 1) takes fork 1 and then fork 2
*		Philo #3 (id: 2) takes fork 0 and then fork 2
*	Now, philo #1 takes fork 1, philo #3 takes fork 0 and philo #2 waits patiently.
*	Fork 2 is free for philo #3 to take, so he eats. When he is done philo #1 can
*	take fork 0 and eat. When he is done, philo #2 can finally get fork 1 and eat.
*/
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

/* init_philosophers:
*	Allocates memory for each philosopher and initializes their values.
*	Returns a pointer to the array of philosophers or NULL if
*	initialization failed.
*/
static t_philo	**init_philosophers(t_table *table)
{
	t_philo			**philos;
	unsigned int	i;

	philos = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!philos)
		return (exit_philo(table, ERROR_MALLOC), NULL);
	i = 0;
	while (i < table->num_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i])
			return (exit_philo(NULL,NULL), NULL);
		if (pthread_mutex_init(&philos[i]->meal_time_lock, 0) != 0)
			return (exit_philo(table, NULL), NULL);
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->times_ate = 0;
		assign_forks(philos[i]); i++; }
	return (philos);
}

/* init_global_mutexes: Initializes mutex locks for forks, writing and the stop simulation
*	flag.
*	Returns true if the initalizations were successful, false if
*	initilization failed.
*/
static bool	init_global_mutexes(t_table *table)
{
	table->fork_locks = init_forks(table);
	if (!table->fork_locks)
		return (false);
	if (pthread_mutex_init(&table->sim_stop_lock, 0) != 0)
		return (exit_philo(table, NULL), NULL);
	if (pthread_mutex_init(&table->write_lock, 0) != 0)
		return (exit_philo(table, NULL), NULL);
	return (true);
}


t_table *initialising_table(int ac, char **av)
{
    t_table *table;

    table = malloc(sizeof(t_table));
    if (!table)
        return (exit_philo(NULL, "MALLOC FAILED"), NULL);
    table->num_of_philos = integer_atoi(av[1]);
    table->time_to_die = integer_atoi(av[2]);
    table->time_to_eat = integer_atoi(av[3]);
    table->time_to_sleep = integer_atoi(av[4]);
    table->times_should_eat = -1;
    if (ac == 6)
        table->times_should_eat = integer_atoi(av[5]);

    // Initialize philosophers
    table->philos = init_philosophers(table);
    if (!table->philos)
        return (exit_philo(table, "PHILOSOPHER INIT FAILED"), NULL);

    // Initialize global mutexes (forks, locks, etc.)
    if (!init_global_mutexes(table))
        return (exit_philo(table, "MUTEX INIT FAILED"), NULL);

    // Set simulation stop flag
    table->sim_stop = false;

    return (table);
}
