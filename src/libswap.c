#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <assert.h>

#include <string.h>

#include <swap.h>

__attribute__ ((leaf, nonnull (1, 2, 3), nothrow))
void swap (void *restrict a, void *restrict b,
	void *restrict tmp, size_t esz) {
	memcpy (tmp, a,   esz);
	memcpy (a,   b,   esz);
	memcpy (b,   tmp, esz);
}

__attribute__ ((nonnull (1, 2, 3), nothrow))
void swaps (void *restrict a, void *restrict b,
	void *restrict tmp, size_t esz, size_t n) {
	size_t eszs = esz * n;
	swap (a, b, tmp, eszs);
}

/* src and dest should not overlap ? */
__attribute__ ((leaf, nonnull (1, 2), nothrow))
void swap2 (void *restrict a, void *restrict b, size_t esz) {
	char *restrict ac;
	char *restrict bc;
	size_t k;
	assert (a != b);
	ac = (char *restrict) a;
	bc = (char *restrict) b;
	/*uint64_t *restrict src64  = (uint64_t *restrict) src;
	uint64_t *restrict dest64 = (uint64_t *restrict) dest;*/
	/*
	#pragma GCC ivdep
	for (k = 0; k != array->esz / sizeof (uint64_t); k++) {
		src64[k]  ^= dest64[k];
		dest64[k] ^= src64[k];
		src64[k]  ^= dest64[k];
	}
	#pragma GCC ivdep
	for (k = array->esz - array->esz % sizeof (uint64_t); k != array->esz; k++) {

	}
	*/
	TODO (complete that implementation ^^^ )
	#pragma GCC ivdep
	for (k = 0; k != esz; k++) {
		ac[k] ^= bc[k];
		bc[k] ^= ac[k];
		ac[k] ^= bc[k];
	}
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1, 2), nothrow))
void swaps2 (void *restrict a, void *restrict b, size_t esz, size_t n) {
	char *restrict ac;
	char *restrict bc;
	size_t k;
	assert (a != b);
	ac = (char *restrict) a;
	bc = (char *restrict) b;
	TODO (see above)
	#pragma GCC ivdep
	for (k = 0; k != n; k++)
		swap2 (ac + k * esz, bc + k * esz, esz);
}
