#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#define MAX_PHILOSOPHER 200
#define INT_MAX_NUMBER 2147483647
#define INT_MIN_NUMBER -2147483648 
#define ERROR_MESSAGE "ERROR\n"

#include "libft.h"
#include <pthread.h>
#include <stdio.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

t_philo *initialising_philosopher(int argc, char **argv);
void exit_philo(t_philo *philosopher);

#endif
