/* RPC - vytvareni vzdaleneho slovniku - definice rpc rozhraní
 * Zpracoval: Radek Vais, A17N0093P
 * Verze: 12.03.2018
 */

const WORD_LEN = 256;

const VOCAB_ACCEPTED = 0;
const VOCAB_EMPTY = 1;
const VOCAB_NO_JOB = 2;
const VOCAB_COMPUTING = 3;

const REQ_FALSE = 0;
const REQ_TRUE = 1;

/* struktura pro predani slova pro zaznamenani do slovniku */
struct WORD_RECORD {
	char word[WORD_LEN];
	char translation[WORD_LEN];
	short find;
	short save;
};

/* struktura pro ID pozadavku */
struct REQUEST {
	int handle;
	int state;
};

program VOCABULARY {
	version VOCABULARY_VERSION {
		short add_word_to_vocab(WORD_RECORD) = 1;
		REQUEST find_word_in_vocab(WORD_RECORD) = 2;
		WORD_RECORD get_find_result(REQUEST) = 3;
  } = 1;
} = 0x0ABECEDA;
