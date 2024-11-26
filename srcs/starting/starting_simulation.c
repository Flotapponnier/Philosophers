#include "../../includes/philosopher.h"


void *philosopher(void *data) {

	t_philo *philo = (t_philo*)data;  // Cast the data to the correct type (philosopher)
	//

	if(philo->id % 2)
		philosopher_thinking(philo);
    while (stop_simulation() != 0)
	{
			philosopher_eat(philo);	
			philosopher_thinking(philo);
	}
	return (philosopher);
}

bool	starting_simulation(t_table *table)
{
    unsigned int i;

	printf("Hello");
    if(table->times_should_eat == 0)
			return (NULL); 
	// Set the start time for the simulation
    table->start_time = get_time_in_ms() + (table->num_of_philos * 2 * 10);
    i = 0;

    // Create a thread for each philosopher
    while (i < table->num_of_philos)
    {
        if (pthread_create(&table->philos[i]->thread, NULL, philosopher, table->philos[i]) != 0)
            return (exit_philo(table, "Problem with creation of thread"), true);
        printf("Thread philosopher %d created with success\n", i + 1);

        i++;
    }
	i = 0;
	while(i < table->num_of_philos)
	{
		if(pthread_join(table->philos[i]->thread, NULL) != 0)
			return (exit_philo(table, "Problem with joining thread"), true);
		printf("Thread philosopher %d Join succesfully\n", table->philos[i]->id);
		i++;	
	}
	return true;
}
