#include "philo.h"

/*
** Function: get_time_ms
** ----------------------
** Get the current time in milliseconds.
**
** Returns: The current time in milliseconds.
*/
long long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

/*
** Function: sleep_ms
** ------------------
** Sleep for the specified number of milliseconds.
**
** Parameters:
**   - duration: The duration to sleep in milliseconds.
*/
void sleep_ms(long long duration)
{
    struct timespec ts;
    ts.tv_sec = duration / 1000;
    ts.tv_nsec = (duration % 1000) * 1000000;
    nanosleep(&ts, NULL);
}