#include <errno.h>
#include <stdlib.h>

#include "./include/frandauto.h"

// return minimum value
#define MIN(a, b) (a <= b ? a : b)

/* RET:
	EINVAL: various conditions
	ENOMEM: (m/re)alloc returned NULL pointer
*/
fra_err_t fra_next_ascii (
	const unsigned int len, // length of string, w/o null byte
	const unsigned int space, // time spacing on automata
	const unsigned int skip, // include only bits where: 0 = bit_index mod skip
	char **out // null terminated string with ascii encoding
) {
	if (! len || ! space || ! skip || ! out) return EINVAL;

	unsigned int
		k, // count for skip loop
		n, // number of characters remaining
		c = 0, // current character count
		s = fra_size (), // automata size
		v = s / skip // length of automata states after skip
	;

	// Must have atleast 7 bits, or else cannot produce a single character
	if (FRA_BIT_P_SCH > v) return EINVAL;

	unsigned char
		l[v], // automata states after skip
		*a = NULL // raw automata states, passed to fra_get_states
	;

	if (*out) {
		*out = realloc (*out, len + 1);
	} else {
		*out = malloc (len + 1);
	}

	if (! *out) return ENOMEM;

	int e; // for errors

	do {
		fra_step (space);

		e = fra_get_states (&a);
		if (e) return e;

		n = (len - c) * FRA_BIT_P_SCH;

		if (1 < skip) {
			// copy states not skipped to l
			for (k = 0; s > k; k += skip) {
				l[k / skip] = a[k];
			}

			// append string, increment character count accordingly
			c += fra_to_ascii (MIN (v, n), l, (*out) + c);
		} else {
			c += fra_to_ascii (MIN (v, n), a, (*out) + c);
		}
	} while (len > c);

	(*out)[len] = '\0';

	// a was allocated by fra_get_states
	free (a);

	return 0;
}
// vim : set ts=4 sw=4 noet syn=c :
