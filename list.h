/* RPC - vytvareni vzdaleneho slovniku - jednoduchý seznam rozhraní
 * Zpracoval: Radek Vais, A17N0093P
 * Verze: 12.03.2018
 */

#ifndef LIST_H_345
#define LIST_H_345

#include "vocabulary.h"

int addToList(WORD_RECORD *rec);
WORD_RECORD *find(WORD_RECORD *rec);
void printList();

#endif
