/* RPC - vytvareni vzdaleneho slovniku - jobs implementation
 * Zpracoval: Radek Vais, A17N0093P
 * Verze: 12.03.2018
 */

#include "server_jobs.h"

#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

JOBS jobs[MAX_JOBS];
int initialisedFlag = 0;

void initialiseJOBS()
{
    pthread_mutex_lock(&mutex);
    if(initialisedFlag)
    {
        pthread_mutex_unlock(&mutex);
        return;
    }

    for (int i = 0; i < MAX_JOBS; ++i) {
        jobs[i].state = FREE;
        jobs[i].result = 0;
    }
    initialisedFlag = 1;
    pthread_mutex_unlock(&mutex);
}

int getJobIndex()
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < MAX_JOBS; ++i) {
        if(jobs[i].state == FREE)
        {
            jobs[i].state = COMPUTING;
            pthread_mutex_unlock(&mutex);
            return i;
        }
    }
    pthread_mutex_unlock(&mutex);
    return -1;
}