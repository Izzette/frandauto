#include <errno.h>
#include <stdlib.h>

#include "./include/frandauto.h"

#define BIT_P_BYTE 8U

/* RET:
	ENOMEM: failed to (m/re)allocate *out
*/
fra_err_t fra_to_bytes (
	const unsigned int sc, // length of sv to use (bits)
	const unsigned char *sv, // array of bits
	unsigned char **out // to pointer to (m/re)allocate
) {
	// length of *out
	unsigned int len = sc / BIT_P_BYTE;

	if (*out) {
		*out = realloc (*out, len);
	} else {
		*out = malloc (len);
	}

	if (! *out) return ENOMEM;

	unsigned int
		i, // index on *out
		j, // count on each bit of byte
		c = 0U // index on sv
	;

	for (i = 0U; len > i; ++i) {
		// concat each bit to byte
		for (j = 0U; BIT_P_BYTE > j; ++j) {
			(*out)[i] <<= 1;
			(*out)[i] |= sv[c++];
		}
	}

	return 0;
}

#define IMIN_SCH 32
#define IMAX_SCH 126

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
) {
	// max possible length, if all encountered are in the valid range
	unsigned int len = sc / FRA_BIT_P_SCH;

	unsigned int
		i, // index on out
		j, // count on each bit per char
		c = 0U // index on sv
	;

	for (i = 0U; len > i; ++i) {
		out[i] = 0U; // set all bits to zero

		// concat all bits to 7 bit char
		for (j = 0U; FRA_BIT_P_SCH > j; ++j) {
			out[i] <<= 1U;
			out[i] |= (char)sv[c++];
		}

		// ensure in valid range
		if (IMIN_SCH > out[i] || IMAX_SCH < out[i]) {
			--i; // try that character again
			--len; // max possible length decreased
		}
	}

	out[len] = '\0';

	return len;
}

// vim : set ts=4 sw=4 noet syn=c :
