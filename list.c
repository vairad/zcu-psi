/* RPC - vytvareni vzdaleneho slovniku - jednoduchý seznam slov implementace
 * Zpracoval: Radek Vais, A17N0093P
 * Verze: 12.03.2018
 */

#include "list.h"

#include <stdio.h>

typedef struct leaf
{
    WORD_RECORD * word;
    struct leaf * next;
} LEAF;

LEAF *head = NULL;

int addToList(WORD_RECORD *rec)
{
//    printf("ADD to list\n");
    if(head == NULL){
//        printf("ADD head\n");
        LEAF *l = malloc(sizeof(LEAF));
        l->word = rec;
        l->next = NULL;
        head = l;
    }else{
//        printf("ADD to leaf\n");
        LEAF *now = head;
        while(now->next != NULL){
            now = now->next;
        }
        LEAF *l = malloc(sizeof(LEAF));
        l->word = rec;
        l->next = NULL;
        now->next = l;
    }
}

WORD_RECORD *find(WORD_RECORD *rec)
{
    if(head == NULL){
        return NULL;
    } else{
        LEAF *now = head;
        if(strcmp(now->word->word, rec->word) == 0)
        {
            return now->word;
        }
        while(now->next != NULL){
            now = now->next;
            if(strcmp(now->word->word, rec->word) == 0)
            {
                return now->word;
            }
        }
        return NULL;
    }
}

void printList()
{
    fprintf(stdout, "Print list\n");
    if(head == NULL){
        fprintf(stdout, "==EMPTY==\n");
     //   fprintf(stderr, "==EMPTY==\n");
    }else{
        LEAF *now = head;
        fprintf(stdout, "%s > %s \n", now->word->word, now->word->translation);
      //  fprintf(stdout, "%s > %s \n", now->word->word, now->word->translation);

        while(now->next != NULL){
            now = now->next;
            fprintf(stdout, "%s > %s \n", now->word->word, now->word->translation);
         //   fprintf(stdout, "%s > %s \n", now->word->word, now->word->translation);
            fprintf(stdout, "===\n");
        //    fprintf(stdout, "===");

        }
    }
}