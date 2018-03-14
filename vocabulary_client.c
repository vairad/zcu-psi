/* RPC - vytvareni vzdaleneho slovniku - klient
 * Zpracoval: Radek Vais, A17N0093P
 * Verze: 12.03.2018
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "vocabulary.h"

#define SERVER "localhost"

#define SERVER_ERROR 55
#define SUCCESS 0


#define ADD 445544
#define GENERATE 554444
#define FIND 444455
#define SUPER_ASK 334455

int task;

char* binary_name;

char global_char = 'A';

void halt_error(char *s1, char *s2)
{
    fprintf(stderr, "%s: %s\n", s1, s2);
    exit(1);
}
void help()
{
    printf("About RPC vocabulary example:\n");
    printf("use one of these options\n");
    printf("add -a to run additional mode\n");
    printf("add -f to run in finding mode\n");
    printf("add -g to run in example generation mode\n");
    printf("add -m to run in example asking mode\n");
}

short read_args(int argc, char *argv[])
{
    binary_name = argv[0];

    if(argc == 1)
    {
        help();
        return 0;
    }

    //zpracovani prepinacu
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' || argv[i][0] == '/') {
            switch (argv[i][1]) {
                case 'h': // zobrazení nápovědy ==================
                case 'H':
                    help();
                    break;

                case 'a': // běh s výchozími parametry =============
                case 'A':
                    task = ADD;
                    break;
                case 'g': // běh s výchozími parametry =============
                case 'G':
                    task = GENERATE;
                    break;

                case 'F': // běh s výchozími parametry =============
                case 'f':
                    task = FIND;
                    break;

                case 'M': // běh s výchozími parametry =============
                case 'm':
                    task = SUPER_ASK;
                    break;

                default : printf("Ignore unknown option %s", argv[i]);
            }
        }
    }
    return 0; //success

}

void doOtherStuff(){
    printf("Do some important job\n");
    fflush(stdout);
    sleep(rand() % 15);
    printf("Some important job done\n");
    fflush(stdout);
}

int run_task_add(int silent)
{
    CLIENT *client;
    WORD_RECORD record;

    if(!silent)
    {
        printf("Type single word: ");
        scanf("%s", record.word);
        printf("Type it's translation: ");
        scanf("%s", record.translation);
    }else
    {
        record.word[0] = ++global_char;
        record.translation[0] = ++global_char;
        record.word[1] = ++global_char;
        record.translation[1] = ++global_char;
        record.word[2] = 0;
        record.translation[2] = 0;
    }


    if ((client = clnt_create(SERVER, VOCABULARY, VOCABULARY_VERSION, "udp")) == NULL) {
        clnt_pcreateerror(binary_name);
        return SERVER_ERROR;
    }

    printf("Send request\n");

    short * res = add_word_to_vocab_1(&record, client);
    if(*res != VOCAB_ACCEPTED){
        printf("Request failed %d\n", *res);
    }

    clnt_destroy(client);
    return SUCCESS;
}

int run_task_find(int silent)
{
    CLIENT *client;
    WORD_RECORD record;

    if(!silent){
        printf("Type single word to translate: ");
        scanf("%s", record.word);
    }
    else{
        strcpy(record.word, "ahoj");
    }

    if ((client = clnt_create(SERVER, VOCABULARY, VOCABULARY_VERSION, "udp")) == NULL) {
        clnt_pcreateerror(binary_name);
        exit(SERVER_ERROR);
    }

    printf("Sending request\n");

    REQUEST * req = find_word_in_vocab_1(&record, client);
    REQUEST my_req;
    memcpy(&my_req, req, sizeof(REQUEST));
    if(my_req.state == REQ_FALSE){
        printf("My handle is broken: %d\n", my_req.handle);
    }
    printf("My handle is: %d\n", my_req.handle);

    doOtherStuff();

    WORD_RECORD * wor = get_find_result_1(&my_req, client);
    WORD_RECORD my_word;
    memcpy(&my_word, wor, sizeof(WORD_RECORD));

    if(my_word.find == VOCAB_ACCEPTED){
        printf("Translation is: %s\n", my_word.translation);
    } else if(my_word.find == VOCAB_COMPUTING){
        printf("Translation in progress.\n");
    } else{
        printf("No translation found.\n");
    }

    clnt_destroy(client);
    return SUCCESS;
}

void * gen_func(){
    run_task_add(1);
}

int run_task_generate(){
    pthread_t threads[6];
    for(int i= 0; i <6; ++i){
        pthread_create(&threads[i], NULL, gen_func, NULL);
    }
    for(int i= 0; i <6; ++i){
        void *data;
        pthread_join(threads[i], data);
    }
    return SUCCESS;
}

void *ask_func(){
    run_task_find(1);
}

int run_task_multiple_ask(){
    pthread_t threads[6];
    for(int i= 0; i <6; ++i){
        pthread_create(&threads[i], NULL, ask_func, NULL);
    }
    for(int i= 0; i <6; ++i){
        void *data;
        pthread_join(threads[i], data);
    }
    return SUCCESS;
}

int run_task(){
    switch(task){
        case ADD:
            return run_task_add(0);
        case FIND:
            return run_task_find(0);
        case GENERATE:
            return run_task_generate();
        case SUPER_ASK:
            return run_task_multiple_ask();
    }
}

int main(int argc, char *argv[])
{
    read_args(argc,argv);
	return run_task();
}
