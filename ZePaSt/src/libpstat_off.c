#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <pstat_off.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_pstat_off (pstat_off_t *restrict s) {
   init_pstat (s->stat);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void update_pstat_off (pstat_off_t *restrict s,
   unigram_t val[]) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
   /* TODO */
   /*void *restrict val = s->diff (left, right);*/
   update_pstat (s->stat, val);
	#pragma GCC diagnostic pop
}

__attribute__ ((leaf, nonnull (1), nothrow))
void finish_pstat_off (pstat_off_t *restrict s) {
   finish_pstat (s->stat);
}

__attribute__ ((nonnull (1, 2), nothrow))
void ez_pstat_off (
   TODO (this should be pstat *)
   pstat_off_t *restrict s,
   unigram_t const vals[], size_t nval, size_t offset) {
   size_t vi;
   unigram_t val[2];
   init_pstat_off (s);
   /* offset must evenly divide nval */
   for (vi = 0; vi != nval - offset; vi++) {
#ifndef NDEBUG
      printf ("vals[%d]:%d %c\n", (int) vi, (int) (vals[vi]), (char) (vals[vi])); fflush (stdout);
      printf ("vals[%d]:%d %c\n", (int) (vi + offset), (int) (vals[vi + offset]), (char) (vals[vi + offset])); fflush (stdout);
#endif
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
      /* it's up to you to make sure you don't overlap your memory addresses */
      val[0] = vals[vi];
      val[1] = vals[vi + offset];
      update_pstat_off (s, val);
	#pragma GCC diagnostic pop
      /*update_stat (s, vals[vi]);*/
   }
   /* otherwise */
   /*for ( ;      vi != nval;          vi++)
      update_stat (s, vals[vi]);*/
   finish_pstat_off (s);
}
