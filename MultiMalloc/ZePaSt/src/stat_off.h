#ifndef _STAT_OFF_H_
#define _STAT_OFF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>

#include <glitter.h>

/*#include <stat-common.h>*/
#include <stat.h>

/*typedef __attribute__ ((nonnull (1)))
void (*init_stat_off_t) (stat_t *restrict stat) ;

typedef __attribute__ ((nonnull (1, 2)))
void (*update_stat_off_t) (stat_t *restrict stat, unigram_t const vals[]) ;

typedef __attribute__ ((nonnull (1)))
void (*finish_stat_off_t) (stat_t *restrict stat) ;*/

TODO (negative signs)
typedef __attribute__ ((const, warn_unused_result))
unigram_t (*stat_off_diff_t) (unigram_t left, unigram_t right) ;

typedef struct {
   /*init_stat_off_t    init;
   update_stat_off_t  update;
   finish_stat_off_t  finish;*/
   stat_t *restrict  stat;
   /*void *restrict stat;*/
   stat_off_diff_t    diff;
} stat_off_t;

void init_stat_off (stat_off_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_stat_off (stat_off_t *restrict s,
   unigram_t left, unigram_t right)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void finish_stat_off (stat_off_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void ez_stat_off (
   stat_off_t *restrict s,
   unigram_t const vals[], size_t nval, size_t offset)
__attribute__ ((nonnull (1, 2), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _STAT_OFF_H_ */