#ifndef _MEAN_H_
#define _MEAN_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

#include <stat.h>
#include <sum.h>

typedef struct {
   sum_t  sum;
   size_t cnt;
   double res;
} mean_t;

void init_mean (void *restrict mean)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_mean (void *restrict mean, unigram_t val)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void finish_mean (void *restrict mean)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void init_mean_stat (stat_t *restrict stat, mean_t *restrict mean)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void ez_mean (
   mean_t *restrict mean,
   unigram_t const vals[], size_t nval)
__attribute__ ((nonnull (1, 2), nothrow)) ;

double ezr_mean (
   unigram_t const vals[], size_t nval)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _MEAN_H_ */