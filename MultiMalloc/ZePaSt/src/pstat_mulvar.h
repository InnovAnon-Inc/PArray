#ifndef _PSTAT_MULVAR_H_
#define _PSTAT_MULVAR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>

#include <glitter.h>

#include <pstat.h>

/*typedef __attribute__ ((nonnull (1)))
void (*init_pstat_mulvar_t) (pstat_t *restrict stat) ;

typedef __attribute__ ((nonnull (1, 2)))
void (*update_pstat_mulvar_t) (pstat_t *restrict stat, unigram_t const vals[]) ;

typedef __attribute__ ((nonnull (1)))
void (*finish_pstat_mulvar_t) (pstat_t *restrict stat) ;

typedef __attribute__ ((const, nonnull (1), warn_unused_result))
unigram_t (*pstat_mulvar_combine_t) (unigram_t const vals[]) ;*/

typedef struct {
   /*init_pstat_mulvar_t    init;
   update_pstat_mulvar_t  update;
   finish_pstat_mulvar_t  finish;*/
   pstat_t                  *restrict stat;
   /*void *restrict stat;*/
   /*pstat_mulvar_combine_t combine;*/
} pstat_mulvar_t;

void init_pstat_mulvar (pstat_mulvar_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_pstat_mulvar (pstat_mulvar_t *restrict s,
   unigram_t const vars[])
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void finish_pstat_mulvar (pstat_mulvar_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void ez_pstat_mulvar (
   pstat_t *restrict s,
   unigram_t const *restrict vals[], size_t nval,
   unigram_t vars[], size_t nvar)
__attribute__ ((nonnull (1, 2, 4), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _PSTAT_MULVAR_H_ */