#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include "./include/frandauto.h"

#define RULE_LEN 32 // 5 neighboured, two color
#define CLR_BIT 0x10 // color bit "1"
#define BLK_BIT 0x00 // blank bit "0"

// Rule number 1436965290
unsigned char __fra_rule[RULE_LEN] = {
	BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, CLR_BIT, BLK_BIT, BLK_BIT, CLR_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, BLK_BIT, CLR_BIT, CLR_BIT, BLK_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT, CLR_BIT, BLK_BIT
};


// cell in automata, linked list node
typedef struct __fra_cell {
	unsigned char state; // state BLK_BIT or CLR_BIT
	struct __fra_cell *next; // next cell
} __fra_cell_t;

// automaton, linked list
__fra_cell_t *__fra_automaton = NULL;

// size of automaton, 0 if not init
unsigned int __fra_auto_size = 0;

bool __fra_is_init = false;
bool __fra_is_seed = false;

/* RET:
	EINVAL if size is not atleast 5
	ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_init (
	const unsigned int size // length of automaton
) {
	if (5 > size) return EINVAL;

	__fra_auto_size = size;

	if (__fra_is_init) {
		__fra_automaton = realloc (__fra_automaton, __fra_auto_size * sizeof (__fra_cell_t));
	} else {
		__fra_automaton = malloc (__fra_auto_size * sizeof (__fra_cell_t));
	}

	if (! __fra_automaton) return ENOMEM;

	// current cell in automaton
	__fra_cell_t *cur = __fra_automaton;

	unsigned int i; // counter, starts at 1 bc the last node links to the first (__fra_automaton)
	for (i = 1; __fra_auto_size > i; ++i) {
		cur->state = 0;
		cur->next = cur + 1;
		++cur;
	}

	cur->state = 0;
	cur->next = __fra_automaton;

	__fra_is_init = true;

	return 0;
}

bool fra_is_init () {
	return __fra_is_init;
}

/* RET:
	automaton size
	0 if not init
*/
unsigned int fra_size () {
	return __fra_auto_size;
}

// frees automaton
void fra_free () {
	free (__fra_automaton);
	__fra_is_init = false;
	__fra_auto_size = 0;
}

// bit count of lrand48
#define LRAND_BITCNT 31U

// Generates full length seed using lrand48
void fra_seed (
	time_t seed // seed used with srand48
) {
	srand48 (seed);

	long v = 0; // value from lrand48

	// working cell in automaton
	__fra_cell_t *cur = __fra_automaton;

	unsigned int i;
	for (i = 0; __fra_auto_size > i; ++i) {
		// if v is empty, get next
		if (! i % LRAND_BITCNT) v = lrand48 ();

		// instead of one, we need CLR_BIT or BLK_BIT
		cur->state = ((unsigned char)(v & 0x1) ? CLR_BIT : BLK_BIT);
		v >>= 1;

		cur = cur->next;
	} 

	__fra_is_seed = true;
}

bool fra_is_seed () {
	return __fra_is_seed;
}

// neighbourhood length
#define NH_LEN 5U

// move cell history buffer by 1
#define ROTATE(h, l, f) { f = l; l = h; h = h->next; }

// steps automaton according to __fra_rule by iter
void fra_step (
	const unsigned int iter // number of steps
) {
	unsigned char
		nh = 0, // working neighbourhood
		fin // cache of first cell, before applying rule
	;

	__fra_cell_t
		*head, // current cell
		*last, // previous cell, just for mem
		*full // cell that we have computed the nh for
	;

	head = __fra_automaton; last = NULL; full = NULL;

	unsigned int
		i, // various counters
		j // step counter
	;

	for (j = 0; iter > j; ++j) {
		// initialize the neighbourhood
		for (i = 1; NH_LEN > i; ++i) {
			nh >>= 1;
			nh |= head->state;

			ROTATE (head, last, full);
		}

		// make final step for initialization, but cache the state of full before changing
		nh >>= 1;
		nh |= head->state;

		fin = full->state;
		full->state = __fra_rule[nh];

		ROTATE (head, last, full);

		// apply rule to remaining cells, except last
		for (i = 2; __fra_auto_size > i; ++i) {
			nh >>= 1;
			nh |= head->state;

			full->state = __fra_rule[nh];

			ROTATE (head, last, full);
		}

		// apply rule from last, but use fin
		nh >>= 1;
		nh |= fin;

		full->state = __fra_rule[nh];

		ROTATE (head, last, full);
	}
}

/* RET:
	ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_get_states (
	unsigned char **out // array of states 1 or 0
) {
	if (*out) {
		*out = realloc (*out, __fra_auto_size);
	} else {
		*out = malloc (__fra_auto_size);
	}

	if (! *out) return ENOMEM;

	// working cell in automaton
	__fra_cell_t *cur = __fra_automaton;

	unsigned int i;
	for (i = 0; __fra_auto_size > i; ++i) {
		// use 1 and 0, instead of CLR_BIT and BLK_BIT
		*(*out + i) = (cur->state ? 1 : 0);
		cur = cur->next;
	}

	return 0;
}

// vim : set ts=4 sw=4 noet syn=c :
