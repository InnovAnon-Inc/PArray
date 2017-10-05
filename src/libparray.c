#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include <mmalloc.h>
#include <swap.h>

#include <parray.h>

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t pdatasz (size_t n) { return sizeof (void *) * n; }

__attribute__ ((const, nothrow, warn_unused_result))
size_t parraysz (size_t n) {
	return sizeof (parray_t) + pdatasz (n);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
size_t parraysz2 (parray_t const *restrict parray) {
	return parraysz (parray->n);
}

__attribute__ ((/*alloc_align (1),*/ /*alloc_size (1, 2),*/ /*malloc,*/
	nothrow, warn_unused_result))
parray_t *ez_alloc_parray (size_t n) {
	void *restrict *restrict combined[2];
	size_t eszs[2];
	parray_t *restrict caq;
	void *restrict data;

	eszs[0] = sizeof (parray_t);
	eszs[1] = pdatasz  (n);
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
   combined[0] = (void *restrict *restrict) &caq;
   combined[1] = (void *restrict *restrict) &data;
	#pragma GCC diagnostic pop
	error_check (mmalloc2 (combined, eszs,
		eszs[0] + eszs[1], ARRSZ (eszs)) != 0)
		return NULL;

   init_parray (caq, data, n);
	return caq;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void ez_free_parray (parray_t *restrict parray) {
	/*free_parray (parray);*/
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
	mfree ((void *restrict) parray);
	#pragma GCC diagnostic pop
}

__attribute__ ((/*alloc_align (1),*/ /*alloc_size (1, 2),*/ /*malloc,*/
	nothrow, warn_unused_result))
parray_t *ez_alloc_parray2 (size_t n) {
	parray_t *restrict parray = malloc (sizeof (parray_t));
	error_check (parray == NULL) return NULL;
	error_check (alloc_parray (parray, n) != 0) {
		free (parray);
		return NULL;
	}
	return parray;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void ez_free_parray2 (parray_t *restrict parray) {
	free_parray (parray);
	free (parray);
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void **index_parray (parray_t const *restrict array, size_t i) {
	assert (i < array->n || (i == 0 && array->n == 0));
	return array->data + i;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_parray (parray_t *restrict array,
	void *data[], size_t n) {
	array->data = data;
	array->n    = n;
}

__attribute__ ((nonnull (1, 2), nothrow))
void init_parray2 (parray_t *restrict array,
	parray_t const *restrict src, size_t min, size_t max) {
	init_parray (array, index_parray (src, min),
		/*max - min*/ range (min, max));
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int alloc_parray (parray_t *restrict array,
	size_t n) {
	void **restrict data;
	data = malloc (pdatasz (n));
	error_check (data == NULL) return -1;
	init_parray (array, data, n);
	return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int realloc_parray (parray_t *restrict array, size_t n) {
	void **restrict new_data;
	assert (n != 0);
	new_data = realloc (array->data, pdatasz (n));
	error_check (new_data == NULL) return -1;
	array->data = new_data;
	array->n = n;
	return 0;
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void *get_parray (parray_t const *restrict array, size_t i) {
	return *(index_parray (array, i));
	/*assert (i < array->n || (i == 0 && array->n == 0));
	return array->data[i];*/
}

__attribute__ ((nonnull (1, 3), nothrow))
void gets_parray (parray_t const *restrict array, size_t i,
	void *e[], size_t n) {
	void /*const*/ **restrict src;
	/*assert (i + n < array->n);*/
	assert (i + n <= array->n);
	if (n == 0) return;
	src = index_parray (array, i);
	(void) memcpy (e, src, pdatasz (n));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 3), nothrow))
void set_parray (parray_t const *restrict array, size_t i,
	void *restrict e) {
	/*assert (i < array->n || (i == 0 && array->n == 0));
	array->data[i] = e;*/
	*(index_parray (array, i)) = e;
}

__attribute__ ((nonnull (1, 3), nothrow))
void sets_parray (parray_t const *restrict array, size_t i,
	void *e[], size_t n) {
	void **restrict dest;
	assert (i + n <= array->n);
	if (n == 0) return;
	dest = index_parray (array, i);
	memcpy (dest, e, pdatasz (n));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1), nothrow))
void cp_parray (parray_t const *restrict array, size_t i, size_t j) {
	void **restrict src  = index_parray (array, i);
	void **restrict dest = index_parray (array, j);
	*dest = *src;
	assert (memcmp (src, dest, sizeof (void *)) == 0);
}

/* src and dest should not overlap */
__attribute__ ((nonnull (1), nothrow))
void cps_parray (parray_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void const *restrict src;
	void *restrict dest;
	/*assert (i + n < array->n);
	assert (j + n < array->n);
	assert (i + n < j || j + n < i);*/
	assert (i + n <= array->n);
	assert (j + n <= array->n);
	assert (i + n <= j || j + n <= i);
	src  = index_parray (array, i);
	dest = index_parray (array, j);
	memcpy (dest, src, pdatasz (n));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1), nothrow))
void mvs_parray (parray_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void **src;
	void **dest;
	/*assert (i + n < array->n);
	assert (j + n < array->n);*/
	assert (i + n <= array->n);
	assert (j + n <= array->n);
	if (n == 0) return;
	src  = index_parray (array, i);
	dest = index_parray (array, j);
	memmove (dest, src, pdatasz (n));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 4), nothrow))
void swap_parray (parray_t const *restrict array,
	size_t i, size_t j, void *restrict tmp) {
	void **restrict src  = index_parray (array, i);
	void **restrict dest = index_parray (array, j);
	swap (src, dest, tmp, sizeof (void *));
	TODO (verify that data is correctly copied)
}

__attribute__ ((nonnull (1, 5), nothrow))
void swaps_parray (parray_t const *restrict array,
	size_t i, size_t j, size_t n, void *tmp[]) {
	void **restrict src;
	void **restrict dest;
	/*assert (i + n < array->n);
	assert (j + n < array->n);*/
	assert (i + n <= array->n);
	assert (j + n <= array->n);
	src  = index_parray (array, i);
	dest = index_parray (array, j);
	swaps (src, dest, tmp, sizeof (void *), n);
	TODO (verify that data is correctly copied)
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1), nothrow))
void swap_parray2 (parray_t const *restrict array,
	size_t i, size_t j) {
	void **restrict src  = index_parray (array, i);
	void **restrict dest = index_parray (array, j);
	swap2 (src, dest, sizeof (void *));
	TODO (verify that data is correctly copied)
}

/* src and dest should not overlap ? */
__attribute__ ((nonnull (1), nothrow))
void swaps_parray2 (parray_t const *restrict array,
	size_t i, size_t j, size_t n) {
	void **restrict src  = index_parray (array, i);
	void **restrict dest = index_parray (array, j);
	swaps2 (src, dest, sizeof (void *), n);
	TODO (verify that data is correctly copied)
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_parray (parray_t const *restrict array) {
	free (array->data);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
size_t indexOf_parray (parray_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void **restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		/*if (array->data[i] == e) return i;*/
		tmp = index_parray (array, i);
		if (*tmp == e)
			return i;
	}
	assert (false);
	__builtin_unreachable ();
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
bool contains_parray (parray_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void **restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_parray (array, i);
		if (*tmp == e)
			return true;
	}
	return false;
}

__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result))
ssize_t indexOf_parray_chk (parray_t const *restrict array,
	void const *restrict e) {
	size_t i;
	void **restrict tmp;
	TODO (is this pragma ok ?)
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_parray (array, i);
		if (*tmp == e)
			return (ssize_t) i;
	}
	return (ssize_t) -1;
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void frees_parray (parray_t const *restrict array, free_t f) {
	size_t i;
	void **restrict tmp;
	#pragma GCC ivdep
	for (i = 0; i != array->n; i++) {
		tmp = index_parray (array, i);
		f (*tmp);
	}
}

/*
typedef __attribute__ ((nonnull (1, 3), warn_unused_result))
size_t (*print_elem_t) (char buf[], size_t bufsz,
	void const *restrict e) ;

typedef __attribute__ ((nonnull (1), warn_unused_result))
size_t (*print_sep_t) (char buf[], size_t bufsz) ;

TODO (maybe change to toString_data())

__attribute__ ((leaf, nonnull (1, 3, 4, 5), nothrow, warn_unused_result))
size_t toString_array (char buf[], size_t busfz,
	print_elem_t print_elem, print_sep_t print_sep,
	array_t const *restrict array) {
	size_t i, prt;
	void *restrict e;
	if (array->n == 0) return ?;

	e   = index_array (array, 0);
	prt = print_elem (buf + prt, bufsz - prt, e);

	for (i = 1; i != array->n && prt != bufsz; i++) {
		prt += print_sep  (buf + prt, bufsz - prt);
		if (prt == bufsz) break;
		e = index_array (array, i);
		prt += print_elem (buf + prt, bufsz - prt, e);
	}
	return prt;
}
*/

/* one version takes a statically allocated array */
/* another allocates it for you, based on the number of separators */
/*
__attribute__ ((leaf, nonnull (1, 3, 4), nothrow, warn_unused_result))
size_t fromString_array (array_t *restrict array,
	char const buf[], size_t busfz,
	parse_elem_t parse_elem) {
	TODO ()
	size_t i, prt;
	void *restrict e;
	if (array->n == 0) return;

	e   = index_array (array, 0);
	prt = print_elem (buf + prt, bufsz - prt, e);

	for (i = 1; i != array->n && prt != bufsz; i++) {
		prt += print_sep  (buf + prt, bufsz - prt);
		if (prt == bufsz) break;
		e = index_array (array, i);
		prt += print_elem (buf + prt, bufsz - prt, e);
	}
	return prt;
}
*/
/*
void toStdint_array (void *restrict buf, array_t const *restrict array) {
	*((uint64_t *) buf++) = array->n;
	*((uint64_t *) buf++) = array->esz;
	(void) memcpy (buf, array->data, datasz (array->esz, array->n));
}

void fromStdint_array (array_t *restrict array, void const *restrict buf) {
	array->n   = *((uint64_t *) buf++);
	array->esz = *((uint64_t *) buf++);
	(void) memcpy (array->data, buf, datasz (array->esz, array->n));
}
*/
