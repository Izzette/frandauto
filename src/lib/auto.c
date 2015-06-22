#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "./include/globals.h"

#define LRAND_BITCNT 31
#define CLR_BIT 0x10

typedef unsigned char uchar_t;

typedef struct __cell {
	// state must be 0x0 or 0x4
	uchar_t state;
	struct __cell *next;
} cell_t;

cell_t *automata = NULL;
unsigned int auto_size;

bool is_init = false;
bool is_seed = false;

/* RET:
0 on success
ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_init (unsigned int size) {
	auto_size = size;

	if (automata) {
		automata = realloc (automata, auto_size * sizeof (cell_t));
	} else {
		automata = malloc (auto_size * sizeof (cell_t));
	}

	if (! automata) return ENOMEM;

	cell_t *cur = automata;
	int i = 0;
	while (auto_size > i) {
		cur->state = 0;
		(cur++)->next = automata + (++i) % auto_size;
	}

	is_init = true;

	return 0;
}

/* RET:
0 on success
Generates seed from lrand48
*/
fra_err_t fra_seed (time_t seed) {
	srand48 (seed);

	long v = 0;
	cell_t *cur = automata;

	int i;
	for (i = 0; auto_size > i; ++i) {
		if (! i % LRAND_BITCNT) v = lrand48 ();

		cur->state = ((uchar_t)(v & 0x1) ? CLR_BIT : 0x0);
		v >>= 1;
	}

	is_seed = true;

	return 0;
}

/* RET:
true on initialized
false othersize
*/
bool fra_is_init () {
	return is_init;
}

/* RET:
true on initialized
false othersize
*/
bool fra_size () {
	return auto_size;
}

/* RET:
true on initialized
false othersize
*/
bool fra_is_seed () {
	return is_seed;
}

// vim : set ts=4 sw=4 noet syn=c :
