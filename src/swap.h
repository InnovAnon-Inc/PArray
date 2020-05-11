#ifndef _SWAP_H_
#define _SWAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

/* https://stackoverflow.com/questions/8862136/is-there-a-built-in-swap-function-in-c */
#define SWAP(x,y) do {   \
   typeof((x)) _x = (x); \
   typeof((y)) _y = (y); \
   (x) = _y;             \
   (y) = _x;             \
} while (0)

void swap (void *restrict a, void *restrict b,
	void *restrict tmp, size_t esz)
__attribute__ ((leaf, nonnull (1, 2, 3), nothrow)) ;

void swaps (void *restrict a, void *restrict b,
	void *restrict tmp, size_t esz, size_t n)
__attribute__ ((nonnull (1, 2, 3), nothrow)) ;

/* src and dest should not overlap ? */
void swap2 (void *restrict a, void *restrict b, size_t esz)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

/* src and dest should not overlap ? */
void swaps2 (void *restrict a, void *restrict b, size_t esz, size_t n)
__attribute__ ((nonnull (1, 2), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _SWAP_H_ */