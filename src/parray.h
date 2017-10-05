#ifndef _PARRAY_H_
#define _PARRAY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sys/types.h>

#include <dsint.h>
#include <glitter.h>

typedef struct {
   void **restrict data;
   size_t n;
} parray_t;

size_t pdatasz (size_t n)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t parraysz (size_t n)
__attribute__ ((const, nothrow, warn_unused_result)) ;

size_t parraysz2 (parray_t const *restrict parray)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

parray_t *ez_alloc_parray (size_t n)
__attribute__ ((/*alloc_align (1),*/ /*alloc_size (1, 2),*/ /*malloc,*/
	nothrow, warn_unused_result)) ;

void ez_free_parray (parray_t *restrict parray)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

parray_t *ez_alloc_parray2 (size_t n)
__attribute__ ((/*alloc_align (1),*/ /*alloc_size (1, 2),*/ /*malloc,*/
	nothrow, warn_unused_result)) ;

void ez_free_parray2 (parray_t *restrict parray)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void **index_parray (parray_t const *restrict parray, size_t i)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result)) ;

void init_parray (parray_t *restrict parray,
	void *data[], size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void init_parray2 (parray_t *restrict parray,
	parray_t const *restrict src, size_t min, size_t max)
__attribute__ ((nonnull (1, 2), nothrow)) ;

int alloc_parray (parray_t *restrict parray, size_t n)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;

int realloc_parray (parray_t *restrict parray, size_t n)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;

void *get_parray (parray_t const *restrict parray, size_t i)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

void gets_parray (parray_t const *restrict array, size_t i,
	void *e[], size_t n)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void set_parray (parray_t const *restrict parray, size_t i,
	void *restrict e)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void sets_parray (parray_t const *restrict parray, size_t i,
	void *e[], size_t n)
__attribute__ ((nonnull (1, 3), nothrow)) ;

void free_parray (parray_t const *restrict parray)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void cp_parray (parray_t const *restrict parray, size_t i, size_t j)
__attribute__ ((nonnull (1), nothrow)) ;

/* src and dest should not overlap */
void cps_parray (parray_t const *restrict parray,
	size_t i, size_t j, size_t n)
__attribute__ ((nonnull (1), nothrow)) ;

void mvs_parray (parray_t const *restrict parray,
	size_t i, size_t j, size_t n)
__attribute__ ((nonnull (1), nothrow)) ;

void swap_parray (parray_t const *restrict parray,
	size_t i, size_t j, void *restrict tmp)
__attribute__ ((nonnull (1, 4), nothrow)) ;

void swaps_parray (parray_t const *restrict parray,
	size_t i, size_t j, size_t n, void *tmp[])
__attribute__ ((nonnull (1, 5), nothrow)) ;

/* src and dest should not overlap ? */
void swap_parray2 (parray_t const *restrict parray,
	size_t i, size_t j)
__attribute__ ((nonnull (1), nothrow)) ;

/* src and dest should not overlap ? */
void swaps_parray2 (parray_t const *restrict parray,
	size_t i, size_t j, size_t n)
__attribute__ ((nonnull (1), nothrow)) ;

size_t indexOf_parray (parray_t const *restrict parray,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

bool contains_parray (parray_t const *restrict parray,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

ssize_t indexOf_parray_chk (parray_t const *restrict parray,
	void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

void frees_parray (parray_t const *restrict array, free_t cb)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _PARRAY_H_ */