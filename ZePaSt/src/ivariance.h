#ifndef _IVARIANCE_H_
#define _IVARIANCE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

#include <stat.h>

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpadded"
typedef struct {
   size_t sum;
   size_t df;
   double res;
   unigram_t ct; /* central tendency */
} ivariance_t;
	#pragma GCC diagnostic pop

void init_ivariance (void *restrict ivariance)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_ivariance (void *restrict ivariance, unigram_t val)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void finish_ivariance (void *restrict ivariance)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void init_ivariance_stat (
   stat_t *restrict stat, ivariance_t *restrict ivariance)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void ez_ivariance (
   ivariance_t *restrict ivariance,
   unigram_t const vals[], size_t nval)
__attribute__ ((nonnull (1, 2), nothrow)) ;

double ezr_ivariance (
   unigram_t ct, size_t df,
   unigram_t const vals[], size_t nval)
__attribute__ ((nonnull (3), nothrow, pure, warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _IVARIANCE_H_ */