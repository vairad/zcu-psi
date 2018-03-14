/* RPC - vytvareni vzdaleneho slovniku - jobs interface
 * Zpracoval: Radek Vais, A17N0093P
 * Verze: 12.03.2018
 */


#ifndef SERVER_JOBS_3946
#define SERVER_JOBS_3946

#include <pthread.h>
#include "vocabulary.h"

#define MAX_JOBS 128

typedef enum {
    FREE,
    COMPUTING,
    DONE,
    FAILED
} REQUEST_STATE;

typedef struct{
    pthread_t thread;
    REQUEST_STATE state;
    WORD_RECORD *input;
    WORD_RECORD *result;
} JOBS;

extern JOBS jobs[MAX_JOBS];
extern int initialisedFlag;

//==============================================================
void initialiseJOBS();
int getJobIndex();

#endif