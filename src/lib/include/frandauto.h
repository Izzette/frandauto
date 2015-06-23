#include <time.h>
#include <stdbool.h>

#undef fra_err_t
typedef int fra_err_t;

#undef fra_init
/* RET:
0 on success
ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_init (unsigned int);

#undef fra_is_init
/* RET:
true on initialized
false othersize
*/
bool fra_is_init ();

#undef fra_size
/* RET:
true on initialized
false othersize
*/
unsigned int fra_size ();

#undef fra_free
void fra_free ();

#undef fra_seed
/* RET:
0 on success
Generates seed from lrand48
*/
fra_err_t fra_seed (time_t);

#undef fra_is_seed
/* RET:
true on initialized
false othersize
*/
bool fra_is_seed ();

#undef fra_step
void fra_step (unsigned int);

#undef fra_get_states
/* RET:
0 on success
ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_get_states (unsigned char **);

// vim : set ts=4 sw=4 noet syn=c :
