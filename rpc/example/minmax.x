/* RPC - vyber maximalniho a minimalniho cisla ze 3 zadanych
 * Zpracoval: Jan Jezek, FAV 5. rocnik, 2001
 */
 
/* struktura pro predani mnoziny 3 cisel serverove funkci */
struct THREE_NUMBERS {
	int a;
	int b;
	int c;
};

/* struktura pro vraceni minima a maxima */
struct MIN_MAX {
	int state;
	int min;
	int max;
};

/* struktura pro ID pozadavku */
struct REQUEST {
	int handle;
};


program MINMAX {
	version MINMAX_VERSION {
		REQUEST calc_min_max(THREE_NUMBERS) = 1;
		MIN_MAX get_min_max_result(REQUEST) = 2;
  } = 1;
} = 0x0ABECEDA;
