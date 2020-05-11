#ifndef _PSTAT_H_
#define _PSTAT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>

#include <glitter.h>

#include <stat-common.h>

typedef __attribute__ ((nonnull (1)))
void (*init_pstat_t) (void *restrict stat) ;

/* change unigram_t[] to void * */
typedef __attribute__ ((nonnull (1, 2)))
void (*update_pstat_t) (void *restrict stat, unigram_t const vals[]) ;

typedef __attribute__ ((nonnull (1)))
void (*finish_pstat_t) (void *restrict stat) ;

TODO (validate(stat_t*) functions)

typedef struct {
   init_pstat_t    init;
   update_pstat_t  update;
   finish_pstat_t  finish;
   void *restrict stat;
} pstat_t;

void init_pstat (pstat_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_pstat (pstat_t *restrict s, unigram_t const vals[])
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void finish_pstat (pstat_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;
/*
void ez_pstat_offset (
   pstat_t *restrict s,
   unigram_t const vals[], size_t nval, size_t offset)
__attribute__ ((nonnull (1, 2), nothrow)) ;

void ez_pstat_ngram (
   pstat_t *restrict s,
   unigram_t const vals[], size_t nval, size_t n)
__attribute__ ((nonnull (1, 2), nothrow)) ;

void ez_pstat_mulvar (
   pstat_t *restrict s,
   unigram_t const *restrict vals[], size_t nval,
   unigram_t vars[], size_t nvar)
__attribute__ ((nonnull (1, 2, 4), nothrow)) ;

void ez_pstat_mulvar_alloc (
   pstat_t *restrict s,
   unigram_t const *restrict vals[], size_t nval, size_t nvar)
__attribute__ ((nonnull (1, 2), nothrow)) ;
*/
#ifdef __cplusplus
}
#endif

#endif /* _PSTAT_H_ */