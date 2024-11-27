#include "../../includes/philosopher.h"

static bool mutex_error_check(int status)
{
    if (status != 0)
    {
        return false;
    }
    return true;
}

bool safe_mutex(pthread_mutex_t *mutex, t_code code)
{
    int status = 0;

    if (code == LOCK)
        status = pthread_mutex_lock(mutex);
    else if (code == UNLOCK)
        status = pthread_mutex_unlock(mutex);
    else if (code == INIT)
        status = pthread_mutex_init(mutex, NULL);
    else if (code == DESTROY)
        status = pthread_mutex_destroy(mutex);
    else
        return (false);
    return mutex_error_check(status);
}

static bool thread_error_check(int status, t_code code)
{
    if (status != 0 && (code == CREATE || code == JOIN || code == DETACH))
        return (false);
    return (true);
}

bool safe_thread(pthread_t *thread_info, void *(*foo)(void *),
                 void *t_data, t_code code)
{
    int status = 0;

    if (code == CREATE)
        status = pthread_create(thread_info, NULL, foo, t_data);
    else if (code == JOIN)
        status = pthread_join(*thread_info, NULL);
    else if (code == DETACH)
        status = pthread_detach(*thread_info);
    else
        return (false);
    return (thread_error_check(status, code));
}
