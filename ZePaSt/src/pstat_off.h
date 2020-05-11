#ifndef _PSTAT_OFF_H_
#define _PSTAT_OFF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>

#include <glitter.h>

/*#include <stat-common.h>*/
#include <pstat.h>

/*TODO (negative signs)
typedef __attribute__ ((const, returns_nonnull, warn_unused_result))
void *restrict (*pstat_off_diff_t) (
   void *restrict left, void *restrict right) ;*/

typedef struct {
   pstat_t *restrict  stat;
   /*pstat_off_diff_t    diff;*/
} pstat_off_t;

void init_pstat_off (pstat_off_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void update_pstat_off (pstat_off_t *restrict s,
   unigram_t vals[])
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void finish_pstat_off (pstat_off_t *restrict s)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

void ez_pstat_off (
   pstat_off_t *restrict s,
   unigram_t const vals[], size_t nval, size_t offset)
__attribute__ ((nonnull (1, 2), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _PSTAT_OFF_H_ */