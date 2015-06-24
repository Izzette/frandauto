#include <time.h>
#include <stdbool.h>

#define FRA_BIT_P_SCH 7U

#undef fra_err_t
typedef int fra_err_t;

#undef fra_init
/* RET:
	EINVAL if size is not atleast 5
	ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_init (
	const unsigned int size // length of automaton
);

#undef fra_is_init
bool fra_is_init ();

#undef fra_size
/* RET:
	automaton size
	0 if not init
*/
unsigned int fra_size ();

#undef fra_free
// frees automaton
void fra_free ();

#undef fra_seed
// Generates full length seed using lrand48
void fra_seed (
	time_t seed // seed used with srand48
);

#undef fra_is_seed
/* RET:
	true on initialized
	false othersize
*/
bool fra_is_seed ();

#undef fra_step
// steps automaton according to __fra_rule by iter
void fra_step (
	const unsigned int iter // number of steps
);

#undef fra_get_states
/* RET:
	ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_get_states (
	unsigned char **out // array of states 1 or 0
);

#undef fra_to_bytes
/* RET:
	ENOMEM: failed to (m/re)allocate *out
*/
fra_err_t fra_to_bytes (
	const unsigned int sc, // length of sv to use (bits)
	const unsigned char *sv, // array of bits
	unsigned char **out // to pointer to (m/re)allocate
);

#undef fra_to_ascii
/* RET:
	actual length of string (w/o null) 
*/
unsigned int fra_to_ascii (
	const unsigned int sc, // length of sv to use (bits)
	const unsigned char *sv, // array of bits
	/*
	ascii string, null terminated
	must already be allocated
	skips characters not within IMIN_SCH to IMAX_SCH
	*/
	char *out
);

#undef fra_next_ascii
/* RET:
	EINVAL: various conditions
	ENOMEM: (m/re)alloc returned NULL pointer
*/
fra_err_t fra_next_ascii (
	const unsigned int len, // length of string, w/o null byte
	const unsigned int space, // time spacing on automata
	const unsigned int skip, // include only bits where: 0 = bit_index mod skip
	char **out // null terminated string with ascii encoding
);

// vim : set ts=4 sw=4 noet syn=c :
