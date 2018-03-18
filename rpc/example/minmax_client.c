#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "minmax.h"

#define SERVER "localhost"
#define REQUEST_COUNT 10

void halt_error(char *s1, const char *s2)
{
	fprintf(stderr, "%s: %s\n", s1, s2);
	exit(1);
}

int main(int argc, char *argv[])
{
	CLIENT *client;
	THREE_NUMBERS abc;
	REQUEST request_table[REQUEST_COUNT];
	REQUEST *request;
	MIN_MAX *minmax;
        int i;
	
	if ((client = clnt_create(SERVER, MINMAX, MINMAX_VERSION, "udp")) == NULL) {
		clnt_pcreateerror(argv[0]);
		exit(0);
	}
	
	srand(time(NULL));
	
	for (i = 0; i <= REQUEST_COUNT; i++) {
		
		abc.a = (int)(1000.0 * ((double)rand() / RAND_MAX));
		abc.b = (int)(1000.0 * ((double)rand() / RAND_MAX));
		abc.c = (int)(1000.0 * ((double)rand() / RAND_MAX));
		
		printf("%3i: Posilam pozadavek: A = %3i, B = %3i, C = %3i\n",
			i, abc.a, abc.b, abc.c);
		
		request = calc_min_max_1(&abc, client);
		if (request == NULL)
			halt_error(argv[0], "Vzdalene volani (calc_min_max) selhalo.");
		if (request->handle < 0)
			halt_error(argv[0], "Server nema zadne volne handly.");
			
		memcpy(&request_table[i], request, sizeof(REQUEST));
	}
	
	for (i = 0; i <= REQUEST_COUNT; i++) {
		minmax = get_min_max_result_1(&request_table[i], client);
		if (minmax == NULL)
			halt_error(argv[0], "Vzdalene volani (get_min_max_result) selhalo.");
		if (minmax->state == 0)
			halt_error(argv[0], "Server odmitnul vratit vysledek pozadavku.");
		printf("%3i: Vysledek pozadavku: MIN = %3i, MAX = %3i\n",
			i, minmax->min, minmax->max);
	}
	
	clnt_destroy(client);
	return 0;	
}
