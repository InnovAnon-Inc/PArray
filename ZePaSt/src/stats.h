#ifndef _STATS_H_
#define _STATS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stat.h>

#ifdef TEST

typedef __attribute__ ((nonnull (1)))
void (*init_stats_t) (
   stat_t stats[], size_t nstat,
   size_t nval) ;

typedef __attribute__ ((nonnull (1)))
void (*update_stats_t) (
   stat_t stats[], size_t nstat,
   unigram_t val, size_t nval) ;

/*typedef __attribute__ ((nonnull (1, 2)))
void (*updates_stats_t) (
   stats_t *restrict stat, unigram_t val[], size_t nval) ;*/

typedef __attribute__ ((nonnull (1)))
void (*finish_stats_t) (
   stat_t stat[], size_t nstat,
   size_t nval) ;

TODO (validate(stats_t*) functions)

typedef struct {
   init_stats_t   init;
   update_stats_t update;
   /*updates_stats_t updates;*/
   finish_stats_t finish;
   stat_t *restrict stats;
   /*size_t nstats;*/
} stats_t;

void init_stats (stats_t *restrict s, size_t nval)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_stats (
   stats_t *restrict s,
   unigram_t val, size_t nval)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

/*void updates_stats0 (
   stats_t *restrict s,
   unigram_t val[], size_t nval)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void updates_stats1 (
   stats_t *restrict s,
   unigram_t val[], size_t nval)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;*/

void finish_stats (stats_t *restrict s, size_t nval)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

#endif

#ifdef __cplusplus
}
#endif

#endif /* _STATS_H_ */
