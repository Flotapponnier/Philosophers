#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

# define RESET		"\033[0m"
# define MAGENTA	"\033[1;35m"
#define MAX_PHILOS 200
#define MAX_MS 60000
#define ERROR_MESSAGE "ERROR\n"
#define ERROR_DIGIT "ARGUMENT SHOULD CONTAIN ONLY DIGIT"
#define ERROR_NUM_PHILOS "NUMBER PHILOS SHOULD NOT EXCEED 200"
#define ERROR_OVERFLOW_INT "NUMBER IS EXCEEDING THE EXPECTED VALUE"
#define ERROR_ARGUMENT "ARGUMENT FORMAT ./philosopher <number of philosopher> <time to die> <time to eat> <time to sleep> <optional : number of time philosopher should eat>"
#define ERROR_MALLOC "ERROR ALLOCATING MEMORY"
#define ERROR_INIT_PHILOS " PHILOSOPHER INITIALISATION FAILED"
#define ERROR_INIT_MUTEX "ERROR INITIALISING MUTEX"
#define ERROR_TPHILO "ERROR CREATING PHILO THREAD"
#define ERROR_TMONITOR "ERROR CREATING MONITOR THREAD"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h> 
#include <unistd.h>

typedef struct s_table t_table; 

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int    id;                 // Philosopher's ID (0-indexed)
	long             times_ate;          // Count of meals eaten by this philosopher
	long 	      last_meal_time;     // Timestamp of the last meal (in milliseconds)
	long             fork[2];            // Indices of forks this philosopher uses
	pthread_mutex_t meal_time_lock;     // Mutex for meal time access
	t_table         *table;             // Pointer to the shared table structure
} t_philo;

typedef struct s_table
{
	pthread_t		monitor;
	time_t 			start_time;
	unsigned int    num_of_philos;       // Number of philosophers
	time_t    		time_to_die;        // Time (ms) before a philosopher dies without eating
	time_t		    time_to_eat;        // Time (ms) a philosopher spends eating
	time_t    		time_to_sleep;      // Time (ms) a philosopher spends sleeping
	long            times_should_eat;   // Number of meals required for each philosopher (-1 if infinite)
	bool            sim_stop;           // Flag to stop simulation
	pthread_mutex_t sim_stop_lock;      // Mutex for sim_stop flag
	pthread_mutex_t write_lock;         // Mutex for console output
	pthread_mutex_t *fork_locks;        // Array of mutexes for forks
	struct s_philo  **philos;           // Array of pointers to philosopher structs
} t_table;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

typedef enum e_code
{
	INIT,
	CREATE,
	LOCK,
	UNLOCK,
	JOIN,
	DETACH,
	DESTROY,
}			t_code;

//parsing argument
int myphilo_atoi(char *str);
bool is_valid_input(int ac, char **av);
bool exit_philo(t_table *table, char *s);


//initialising
bool initialising_table(int ac, char **av, t_table **table);

//starting_simulation
bool starting_simulation(t_table *table);void *philosopher(void *data);
void	stop_simulation(t_table	*table);
void *philosopher(void *data);

//simulation utils
void	write_status(t_philo *philo, t_status status);
bool	check_simulation(t_table *table);

//philosopher_routine
void	*philosopher_thinking(t_philo *philo, bool silent);
void 	philosopher_eat(t_philo *philo);
void	philosopher_sleeping(t_table *table, time_t sleep_time);

//time
time_t get_time_in_ms();
void	sim_start_synchro(time_t start_time);

//error

//error utils
void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char *str);

//set_get_bool.c
void	set_bool(pthread_mutex_t *mutex, bool *dst, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long *dst, long value);
long	get_long(pthread_mutex_t *mutex, long *value);

//safe_thread_mutex
bool safe_mutex(pthread_mutex_t *mutex, t_code code);
bool safe_thread(pthread_t *thread_info, void *(*foo)(void *), void *t_data, t_code code);

//monitor
void	*monitor(void *data);
#endif
