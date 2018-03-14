/* RPC - vytvareni vzdaleneho slovniku - server
 * Zpracoval: Radek Vais, A17N0093P
 * Verze: 12.03.2018
 */

#include <pthread.h>
#include <string.h>
#include <rpc/rpc.h>
#include <sched.h>
#include <stdio.h>

#include "vocabulary.h"
#include "server_jobs.h"
#include "list.h"

//===============================================================

void *add_th_func(void *local_record)
{
    fprintf(stdout, "Run adding procedure\n");
  //  fprintf(stderr, "Run adding procedure\n");

    JOBS * job = (JOBS *)local_record;
    WORD_RECORD *new_record = job->input;
    WORD_RECORD *old = find(new_record);

    if(old == NULL){
        addToList(new_record);
        fprintf(stdout, "Word was succesfully added\n");
 //       fprintf(stderr, "Word was succesfully added\n");
    }else{
        strcpy(old->translation, new_record->translation);
        fprintf(stdout, "Word was succesfully updated\n");
  //      fprintf(stderr, "Word was succesfully updated\n");
    }

    printList();
    job->state = FREE;
}

void *find_th_func(void *local_record)
{
    fprintf(stdout, "Running fing procedure\n");
    //  fprintf(stderr, "Run adding procedure\n");

    JOBS * job = (JOBS *)local_record;
    WORD_RECORD *new_record = job->input;

    WORD_RECORD *old = find(new_record);
    if(old == NULL){
        job->state = FAILED;
        fprintf(stdout, "Word not found\n");
    }else{
        fprintf(stdout, "Word was succesfully found\n");
        job->result = old;
        job->state = DONE;
    }
    printList();
}


short *add_word_to_vocab_1_svc(WORD_RECORD * word,struct svc_req *b)
{
    static short res;

    initialiseJOBS();
    int job_index = getJobIndex();
    if(job_index == -1){
        fprintf(stdout,"Not enough jobs\n");
        res = VOCAB_NO_JOB;
        return &res;
    }

  //  fprintf(stdout,"Recieved word: \"%s\" and translation: \"%s\"\n", word->word, word->translation);

    //check buffer attack
    word->word[WORD_LEN-1]=0;
    word->translation[WORD_LEN-1]=0;

    if(strlen(word->word) && strlen(word->translation))
    {
        fprintf(stdout,"Accepted record: \"%s\" and translation: \"%s\"\n", word->word, word->translation);
        res = VOCAB_ACCEPTED;
        WORD_RECORD *my_rec = malloc(sizeof(WORD_RECORD));
        memcpy(my_rec, word, sizeof(WORD_RECORD));
        jobs[job_index].input = my_rec;
        pthread_create(&jobs[job_index].thread, NULL,add_th_func, &jobs[job_index]);
    }
    else
    {
        res = VOCAB_EMPTY;
    }
    return &res;
}

REQUEST *find_word_in_vocab_1_svc(WORD_RECORD * word, struct svc_req *b)
{
    static REQUEST stat_req;
    REQUEST *req = &stat_req;// = malloc(sizeof(REQUEST));
    initialiseJOBS();
    int job_index = getJobIndex();
    if(job_index == -1)
    {
        req->handle = job_index;
        req->state = REQ_FALSE;
    }

    fprintf(stdout,"Recieved word: \"%s\"\n", word->word);

    //check buffer attack
    word->word[WORD_LEN-1]=0;
    word->translation[WORD_LEN-1]=0;

    if(strlen(word->word))
    {
        fprintf(stdout,"Looking up translation for: \"%s\" \n", word->word);
        WORD_RECORD *my_rec = malloc(sizeof(WORD_RECORD));
        memcpy(my_rec, word, sizeof(WORD_RECORD));
        jobs[job_index].input = my_rec;
        pthread_create(&jobs[job_index].thread, NULL,find_th_func, &jobs[job_index]);
    }

    req->handle = job_index;
    req->state = REQ_TRUE;
    fprintf(stdout,"Look up request added\n");
    return req;
}

WORD_RECORD *get_find_result_1_svc(REQUEST * req, struct svc_req *b)
{
    fprintf(stdout,"Get result req: %d\n", req->handle);
    static WORD_RECORD founded;
    switch(jobs[req->handle].state){
        case DONE:
            fprintf(stdout,"Done handle: %d\n", req->handle);
            memcpy(&founded, jobs[req->handle].result, sizeof(WORD_RECORD));
            founded.find = VOCAB_ACCEPTED;
            break;
        case FAILED:
            fprintf(stdout,"Failed handle: %d\n", req->handle);
            memset(&founded, 0, sizeof(WORD_RECORD));
            founded.find = VOCAB_EMPTY;
            break;
        default:
            fprintf(stdout,"Default way for handle: %d\n", req->handle);
            memset(&founded, 0, sizeof(WORD_RECORD));
            founded.find = VOCAB_COMPUTING;
            break;

    }
    jobs[req->handle].state = FREE;
    return &founded;
}
