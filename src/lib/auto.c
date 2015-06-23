#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "./include/frandauto.h"

typedef unsigned char __fra_uchar_t;

typedef struct __fra_cell {
	__fra_uchar_t state;
	struct __fra_cell *next;
} __fra_cell_t;

__fra_cell_t *__fra_automata = NULL;
unsigned int __fra_auto_size;

bool __fra_is_init = false;
bool __fra_is_seed = false;

#define RULE_LEN 32
#define CLR_BIT 0x10
#define BLK_BIT 0x00

// Rule number 1436965290
__fra_uchar_t __fra_rule[RULE_LEN] = {
	BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, CLR_BIT, BLK_BIT, BLK_BIT, CLR_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, BLK_BIT, CLR_BIT, CLR_BIT, BLK_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT
};

/* RET:
0 on success
ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_init (unsigned int size) {
	__fra_auto_size = size;

	if (__fra_is_init) {
		__fra_automata = realloc (__fra_automata, __fra_auto_size * sizeof (__fra_cell_t));
	} else {
		__fra_automata = malloc (__fra_auto_size * sizeof (__fra_cell_t));
	}

	if (! __fra_automata) return ENOMEM;

	__fra_cell_t *cur = __fra_automata;

	unsigned int i;
	for (i = 1; __fra_auto_size > i; ++i) {
		cur->state = 0;
		cur->next = cur + 1;
		++cur;
	}

	cur->state = 0;
	cur->next = __fra_automata;

	__fra_is_init = true;

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
unsigned int fra_size () {
	return __fra_auto_size;
}

void fra_free () {
	free (__fra_automata);
	__fra_is_init = false;
}

#define LRAND_BITCNT 31U

/* RET:
0 on success
Generates seed from lrand48
*/
fra_err_t fra_seed (time_t seed) {
	srand48 (seed);

	long v = 0;
	__fra_cell_t *cur = __fra_automata;

	unsigned int i;
	for (i = 0; __fra_auto_size > i; ++i) {
		if (! i % LRAND_BITCNT) v = lrand48 ();

		cur->state = ((__fra_uchar_t)(v & 0x1) ? CLR_BIT : BLK_BIT);
		v >>= 1;
cur = cur->next; } 
	__fra_is_seed = true;

	return 0;
}

/* RET:
true on initialized
false othersize
*/
bool fra_is_seed () {
	return __fra_is_seed;
}

#define NH_LEN 5U

#define ROTATE(h, l, f) { f = l; l = h; h = h->next; }

void fra_step (unsigned int iter) {
	__fra_uchar_t nh = 0, fin;

	__fra_cell_t *head, *last, *full;
	head = __fra_automata; last = NULL; full = NULL;

	unsigned int i, j;
	for (j = 0; iter > j; ++j) {
		for (i = 1; NH_LEN > i; ++i) {
			nh >>= 1;
			nh |= head->state;

			ROTATE (head, last, full);
		}

		nh >>= 1;
		nh |= head->state;

		fin = full->state;
		full->state = __fra_rule[nh];

		ROTATE (head, last, full);

		for (i = 2; __fra_auto_size > i; ++i) {
			nh >>= 1;
			nh |= head->state;

			full->state = __fra_rule[nh];

			ROTATE (head, last, full);
		}

		nh >>= 1;
		nh |= fin;

		full->state = __fra_rule[nh];

		ROTATE (head, last, full);
	}
}

/* RET:
0 on success
ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_get_states (unsigned char **out) {
	if (*out) {
		*out = realloc (*out, __fra_auto_size);
	} else {
		*out = malloc (__fra_auto_size);
	}

	if (! *out) return ENOMEM;

	__fra_cell_t *cur = __fra_automata;

	unsigned int i;
	for (i = 0; __fra_auto_size > i; ++i) {
		*(*out + i) = (cur->state ? 1 : 0);
		cur = cur->next;
	}

	return 0;
}

// vim : set ts=4 sw=4 noet syn=c :
