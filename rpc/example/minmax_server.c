/* RPC - procedury na strane serveru
 * Zpracoval: Jen Jezek, FAV 5. rocnik, 2001
 */

#include <stdio.h>
#include <string.h>
#include <rpc/rpc.h>
#include <thread>
#include <sched.h> /* Funguje jenom na linuixu! */
#include "minmax.h"


#define MAX_REQUESTS 128
#define THREAD_STACK_SIZE 16384

typedef enum {
	RS_FREE = 0,
	RS_COMPUTING,
	RS_FINISHED
} REQUEST_STATE;

typedef struct {
	char stack[THREAD_STACK_SIZE];
	REQUEST_STATE state;
	THREE_NUMBERS input;
	MIN_MAX output;
} REQUEST_ITEM;

#define get_stack(rq_item) \
	((void *)(&(rq_item).stack[THREAD_STACK_SIZE - 1]))

static REQUEST_ITEM request_table[MAX_REQUESTS];


int thread_func(int request_item_index)
{
	printf("Thread running");
	REQUEST_ITEM *request_item = &request_table[(int)request_item_index];
	MIN_MAX *result = &request_item->output;

	#define A (request_item->input.a)
	#define B (request_item->input.b)
	#define C (request_item->input.c)

	if (A < B)
		if (A < C)
			result->min = A;
		else
			result->min = C;
	else
		if (B < C)
			result->min = B;
		else
			result->min = C;

	if (A > B)
		if (A > C)
			result->max = A;
		else
			result->max = C;
	else
		if (B > C)
			result->max = B;
		else
			result->max = C;

	#undef A
	#undef B
	#undef C

	request_item->state = RS_FINISHED;
	printf("%3i: Pozadavek ceka na vyzvednuti vysledku.\n",
		(int)request_item_index);
}


REQUEST *calc_min_max_1_svc(THREE_NUMBERS *abc, struct svc_req *b)
{
	static REQUEST result;
	static int first_run = 1;

	int i;
	int index;

	/* Pri prvnim behu vymazat tabulku pozadavku. */
	if (first_run) {
		first_run = 0;
		for (i = 0; i < MAX_REQUESTS; i++)
			request_table[i].state = RS_FREE;
		printf("Inicializace serveru prave probehla.\n");
	}

	/* Najit volnou pozici pro pozadavek. */
	index = -1;
	for (i = 0; i < MAX_REQUESTS; i++)
		if (request_table[i].state == RS_FREE) {
			index = i;
			break;
		}

	/* Zpustit vlakno pro obsluhu pozadavku. */
	if (index >= 0) {
		printf("%3i: Pozadavek byl zahajen: A = %3i, B = %3i, C = %3i\n",
			index, abc->a, abc->b, abc->c);
		memcpy(&request_table[index].input, abc, sizeof(THREE_NUMBERS));
		request_table[index].state = RS_COMPUTING;
		new std::thread(thread_func, index);
	} else
		printf("%3i: !! Pozadavek nelze zpracovat, je plna fronta.\n", index);

	result.handle = index;
	return &result;
}

MIN_MAX *get_min_max_result_1_svc(REQUEST *request, struct svc_req *b)
{
	static MIN_MAX result;

	/* Pockame, kdyz neni dopocitano. */
	if (request_table[request->handle].state == RS_COMPUTING) {
		printf("%3i: Pozadovan vysledek, ceka se na dopocitani.\n", request->handle);
		while (request_table[request->handle].state == RS_COMPUTING)
			;
	}

	/* Vyzvedneme vysledek. */
	if (request_table[request->handle].state == RS_FINISHED) {
		memcpy(&result, &request_table[request->handle].output, sizeof(MIN_MAX));
		request_table[request->handle].state = RS_FREE;
		result.state = 1;
		printf("%3i: Vyzvednut vysledek.\n", request->handle);
	} else {
		result.state = 0;
		printf("%3i: !! Pozadovan vysledek neexistujiciho pozadavku.\n", request->handle);
	}

	return &result;
}
