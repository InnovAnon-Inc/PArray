#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <assert.h>
#include <stdlib.h>

#include <mmalloc.h>

__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result))
int mmalloc_naive (void /*const*/ *restrict dests[],
	size_t const eszs[], size_t n) {
	size_t i, j;
	#pragma GCC ivdep
	for (i = 0; i != n; i++) {
		dests[i] = (void /*const*/ *restrict) malloc (eszs[i]);
		error_check (dests[i] != NULL) {
			for (j = 0; j != i; j++) free (dests[j]);
			return -1;
		}
	}
	return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void mfree_naive (void /*const*/ *restrict dests[], size_t n) {
	size_t i;
	#pragma GCC ivdep
	for (i = 0; i != n; i++)
		free (dests[i]);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result))
int mmalloc (void /*const*/ *restrict dests[],
	size_t const eszs[], size_t sumsz, size_t n) {
	size_t i, cumsum;
	char /*const*/ *restrict tmp;

	tmp = (char /*const*/ *restrict) malloc (sumsz);
	error_check (tmp == NULL) return -1;

	for (i = cumsum = 0; i != n; cumsum += eszs[i], i++)
		dests[i] = (void /*const*/ *restrict) (tmp + cumsum);

	assert (sumsz == cumsum);
	return 0;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result))
int mmalloc2 (void *restrict *restrict dests[],
	size_t const eszs[], size_t sumsz, size_t n) {
	size_t i, cumsum;
	char /*const*/ *restrict tmp;

	tmp = (char /*const*/ *restrict) malloc (sumsz);
	error_check (tmp == NULL) return -1;

	for (i = cumsum = 0; i != n; cumsum += eszs[i], i++)
		*(dests[i]) = (void /*const*/ *restrict) (tmp + cumsum);

	assert (sumsz == cumsum);
	return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void mfree (void /*const*/ *restrict dests0[]) {
	free (*dests0);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void mfree2 (void /*const*/ *restrict dests0) {
	free (dests0);
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
size_t sum_size_t (size_t const x[], size_t n) {
	size_t i, sum;
	for (i = sum = 0; i != n; i++)
		sum += x[i];
	return sum;
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int ez_mmalloc (void /*const*/ *restrict dests[],
	size_t const eszs[], size_t n) {
	size_t sumsz = sum_size_t (eszs, n);
	return mmalloc (dests, eszs, sumsz, n);
}


__attribute__ ((leaf, nonnull (1, 3, 4), nothrow, warn_unused_result))
int ezmalloc (alloc_t do_alloc, void const *restrict alloc_args,
   stdcb_t cb, free_t do_free) {
   void *restrict ds = do_alloc (alloc_args);
   error_check (ds == NULL) return -1;
   error_check (cb (ds) != 0) return -2;
   do_free (ds);
   return 0;
}
