#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "./include/globals.h"

#define LRAND_BITCNT 31
#define CLR_BIT 0x10

typedef unsigned char __fra_uchar_t;

typedef struct __fra_cell {
	// state must be 0x0 or 0x4
	__fra_uchar_t state;
	struct __fra_cell *next;
} __fra_cell_t;

__fra_cell_t *automata = NULL;
unsigned int __fra_auto_size;

bool __fra_is_init = false;
bool __fra_is_seed = false;

/* RET:
0 on success
ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_init (unsigned int size) {
	__fra_auto_size = size;

	if (automata) {
		automata = realloc (automata, __fra_auto_size * sizeof (__fra_cell_t));
	} else {
		automata = malloc (__fra_auto_size * sizeof (__fra_cell_t));
	}

	if (! automata) return ENOMEM;

	__fra_cell_t *cur = automata;
	int i = 0;
	while (__fra_auto_size > i) {
		cur->state = 0;
		(cur++)->next = automata + (++i) % __fra_auto_size;
	}

	__fra_is_init = true;

	return 0;
}

/* RET:
0 on success
Generates seed from lrand48
*/
fra_err_t fra_seed (time_t seed) {
	srand48 (seed);

	long v = 0;
	__fra_cell_t *cur = automata;

	int i;
	for (i = 0; __fra_auto_size > i; ++i) {
		if (! i % LRAND_BITCNT) v = lrand48 ();

		cur->state = ((__fra_uchar_t)(v & 0x1) ? CLR_BIT : 0x0);
		v >>= 1;
	}

	__fra_is_seed = true;

	return 0;
}

/* RET:
true on initialized
false othersize
*/
bool fra_is_init () {
	return __fra_is_init;
}

/* RET:
true on initialized
false othersize
*/
bool fra_size () {
	return __fra_auto_size;
}

/* RET:
true on initialized
false othersize
*/
bool fra_is_seed () {
	return __fra_is_seed;
}

// vim : set ts=4 sw=4 noet syn=c :
