/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftapponn <ftapponn@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:26:01 by ftapponn          #+#    #+#             */
/*   Updated: 2024/11/27 16:26:05 by ftapponn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

/*
void	print_table(t_table *table)
{
	unsigned int	i;
	t_philo			*philo;

	// Check table initialization
	if (!table)
	{
		printf("Error: Table not initialized.\n");
		return ;
	}
	printf("Table Initialized:\n");
	printf("  Number of Philosophers: %u\n", table->num_of_philos);
	printf("  Time to Die: %ld ms\n", table->time_to_die);
	printf("  Time to Eat: %ld ms\n", table->time_to_eat);
	printf("  Time to Sleep: %ld ms\n", table->time_to_sleep);
	printf("  Times Philosophers Should Eat: %ld\n", table->times_should_eat);
	printf("  Simulation Stop Flag: %s\n", table->sim_stop ? "True" : "False");
	// Check fork locks
	if (!table->fork_locks)
	{
		printf("Error: Fork locks not initialized.\n");
		return ;
	}
	printf("  Fork Locks Initialized: Yes\n");
	// Check philosophers
	if (!table->philos)
	{
		printf("Error: Philosophers not initialized.\n");
		return ;
	}
	printf("Philosophers Initialized:\n");
	for (i = 0; i < table->num_of_philos; i++)
	{
		philo = table->philos[i];
		if (!philo)
		{
			printf("  Philosopher %u: Error (Not Initialized)\n", i);
			continue ;
		}
		printf("  Philosopher %u:\n", i + 1);
		printf("    ID: %u\n", philo->id);
		printf("    Times Ate: %ld\n", philo->times_ate);
		printf("    Last Meal Time: %ld\n", philo->last_meal_time);
		printf("    Forks: [%ld, %ld]\n", philo->fork[0], philo->fork[1]);
	}
	// Check global mutexes
	printf("Global Mutexes:\n");
	printf("  Simulation Stop Lock: Initialized\n");
	printf("  Write Lock: Initialized\n");
}
*/

int	main(int argc, char **argv)
{
	t_table	*table;

	if (!is_valid_input(argc, argv))
		return (1);
	if (!initialising_table(argc, argv, &table))
		return (1);
	if (!starting_simulation(table))
		return (1);
	stop_simulation(table);
	return (0);
}
