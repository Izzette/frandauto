#include <time.h>
#include <errno.h>

#undef fra_err_t
typedef int fra_err_t;

#undef fra_init
/* RET:
0 on success
ENOMEM if (re/m)alloc ret NULL
*/
fra_err_t fra_init (unsigned int size);

#undef fra_seed
/* RET:
0 on success
*/
// Generates seed from lrand48
fra_err_t fra_seed (time_t seed);

// vim : set ts=4 sw=4 noet syn=c :

