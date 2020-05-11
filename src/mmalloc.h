#ifndef _MMALLOC_H_
#define _MMALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <dsint.h>
#include <glitter.h>

int mmalloc_naive (void /*const*/ *restrict dests[],
	size_t const eszs[], size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow, warn_unused_result)) ;

void mfree_naive (void /*const*/ *restrict dests[], size_t n)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

int mmalloc (void /*const*/ *restrict dests[],
	size_t const eszs[], size_t sumsz, size_t n)
__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result)) ;

size_t sum_size_t (size_t const x[], size_t n)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

int ez_mmalloc (void /*const*/ *restrict dests[],
	size_t const eszs[], size_t n)
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result)) ;

void mfree (void /*const*/ *restrict dests0[])
__attribute__ ((leaf, nonnull (1), nothrow)) ;

int mmalloc2 (void *restrict *restrict dests[],
	size_t const eszs[], size_t sumsz, size_t n)
__attribute__ ((leaf, nonnull (1), nothrow, warn_unused_result)) ;

void mfree2 (void /*const*/ *restrict dests0)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

int ezmalloc (alloc_t do_alloc, void const *restrict alloc_args,
   stdcb_t cb, free_t do_free)
__attribute__ ((leaf, nonnull (1, 3, 4), nothrow, warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _MMALLOC_H_ */