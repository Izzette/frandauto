#include <time.h>
#include <stdlib.h>

typedef struct __cell {
	unsigned char state;
	struct __cell *next;
} cell_t;

cell_t *automata = NULL;
unsigned char *last_state;
unsigned int auto_size;

// 0 on success, -1 on failure
int auto_init (unsigned int size) {
	auto_size = size;

	if (automata) {
		automata = realloc (automata, auto_size * sizeof (cell_t));
	} else {
		automata = malloc (auto_size * sizeof (cell_t));
	}

	if (! automata) return -1;

	cell_t *cur = automata;
	int i = 0;
	while (auto_size > i) {
		cur->state = 0;
		(cur++)->next = automata + (++i) % auto_size;
	}
	last_state = &(cur - 1)->state;

	return 0;
}

// vim : set ts=4 sw=4 noet syn=c :
