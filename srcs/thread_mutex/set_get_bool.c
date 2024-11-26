#include "../../includes/philosopher.h"

void	set_bool(pthread_mutex_t	*mutex, bool *dst, bool value)
{
	safe_mutex(mutex, LOCK);
	*dst = value;
	safe_mutex(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	retrieved;

	safe_mutex(mutex, LOCK);
	retrieved = *value;
	safe_mutex(mutex, UNLOCK);
	return (retrieved);
}

void	set_long(pthread_mutex_t *mutex, long *dst, long value)
{
	safe_mutex(mutex, LOCK);
	*dst = value;
	safe_mutex(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	retrieve;

	safe_mutex(mutex, LOCK);
	retrieve = *value;
	safe_mutex(mutex, UNLOCK);
	return (retrieve);
}
