#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#define MAX_PHILOS 200
#define MAX_MS 60000
#define ERROR_MESSAGE "ERROR\n"
#define ERROR_DIGIT "ARGUMENT SHOULD CONTAIN ONLY DIGIT"
#define ERROR_NUM_PHILOS "NUMBER PHILOS SHOULD NOT EXCEED 200"
#define ERROR_OVERFLOW_INT "NUMBER IS EXCEEDING THE EXPECTED VALUE"
#define ERROR_ARGUMENT "ARGUMENT FORMAT ./philosopher <number of philosopher> <time to die> <time to eat> <time to sleep> <optional : number of time philosopher should eat>"
#define ERROR_MALLOC "ERROR ALLOCATING MEMORY"

#include "libft.h"
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

typedef struct s_table t_table; 

typedef struct s_philo
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		times_ate;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				last_meal;
	t_table				*table;
}	t_philo;

typedef struct s_table
{
	unsigned int				num_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_should_eat;
	bool		sim_stop;
	pthread_mutex_t sim_stop_lock;
	pthread_mutex_t write_lock;
	pthread_mutex_t *fork_locks;
	t_philo			**philos;
	pthread_mutex_t	*meal_lock;
}					t_table;


//parsing argument
int integer_atoi(char *str);
bool is_valid_input(int ac, char **av);
void exit_philo(t_table *table, char *s);


//initialising
t_table *initialising_table(int ac, char **av);
static bool	init_global_mutexes(t_table *table);
static t_philo	**init_philosophers(t_table *table);
static void	assign_forks(t_philo *philo);
static pthread_mutex_t	*init_forks(t_table *table);
#endif
