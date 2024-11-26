#include "../../includes/philosopher.h"

static void mutex_error_message(const char *error_msg)
{
    fprintf(stderr, MAGENTA "%s\n" RESET, error_msg);
}

static bool mutex_error_check(int status)
{
    if (status != 0)
    {
        mutex_error_message("Mutex error");
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
    {
        mutex_error_message("Code options: LOCK, UNLOCK, INIT, DESTROY");
        return (false);
    }
    return mutex_error_check(status);
}
