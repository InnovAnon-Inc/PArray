#ifndef _PSTAT_NGRAM_H_
#define _PSTAT_NGRAM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>

#include <glitter.h>

#include <pstat.h>

/*typedef __attribute__ ((nonnull (1)))
void (*init_pstat_ngram_t) (pstat_t *restrict stat) ;

typedef __attribute__ ((nonnull (1, 2)))
void (*update_pstat_ngram_t) (pstat_t *restrict stat, unigram_t const vals[]) ;

typedef __attribute__ ((nonnull (1)))
void (*finish_pstat_ngram_t) (pstat_t *restrict stat) ;*/

/*typedef __attribute__ ((const, nonnull (1, 2)))
void (*pstat_ngram_combine_t) (unigram_t val[], unigram_t const vals[]) ;*/

typedef struct {
   /*init_pstat_ngram_t    init;
   update_pstat_ngram_t  update;
   finish_pstat_ngram_t  finish;*/
   pstat_t               *restrict stat;
   /*void *restrict stat;*/
   /*pstat_ngram_combine_t combine;*/
} pstat_ngram_t;

void init_pstat_ngram (pstat_ngram_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_pstat_ngram (
   pstat_ngram_t *restrict s,
   unigram_t const ngram[])
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void finish_pstat_ngram (pstat_ngram_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void ez_pstat_ngram (
   pstat_t *restrict s,
   unigram_t const vals[], size_t nval, size_t n)
__attribute__ ((nonnull (1, 2), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _PSTAT_NGRAM_H_ */