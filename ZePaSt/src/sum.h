#ifndef _SUM_H_
#define _SUM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

#include <stat.h>

typedef size_t sum_t;

void init_sum (void *restrict sum)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_sum (void *restrict sum, unigram_t val)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void finish_sum (void *restrict sum)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void init_sum_stat (stat_t *restrict stat, sum_t *restrict sum)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void ez_sum (
   sum_t *restrict sum,
   unigram_t const vals[], size_t nval)
__attribute__ ((nonnull (1, 2), nothrow)) ;

sum_t ezr_sum (unigram_t const vals[], size_t nval)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _SUM_H_ */