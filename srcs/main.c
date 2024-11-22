#include "../includes/philosopher.h"

int main(int argc, char **argv)
{
    t_philo *philosopher;

    philosopher = initialising_philosopher(argc, argv);
	ft_printf("%d", philosopher->num_of_philos);
    free(philosopher);
    return (0);
}
