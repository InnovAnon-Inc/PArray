#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <stat_off.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_stat_off (stat_off_t *restrict s) {
   /*init_stat (&(s->stat));*/
   /*s->init (&(s->stat));*/
   init_stat (s->stat);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void update_stat_off (stat_off_t *restrict s,
   unigram_t left, unigram_t right) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
   unigram_t val = s->diff (left, right);
   /*update_stat (&(s->stat), val);*/
   /*s->update (&(s->stat), val));*/
   update_stat (s->stat, val);
	#pragma GCC diagnostic pop
}

__attribute__ ((leaf, nonnull (1), nothrow))
void finish_stat_off (stat_off_t *restrict s) {
   /*finish_stat (&(s->stat));*/
   /*s->finish (&(s->stat));*/
   finish_stat (s->stat);
}

__attribute__ ((nonnull (1, 2), nothrow))
void ez_stat_off (
   TODO (this should be stat_t*)
   stat_off_t *restrict s,
   unigram_t const vals[], size_t nval, size_t offset) {
   size_t vi;
   /*s->init   = init_stat;
   s->update = update_stat;
   s->finish = finish_stat;*/
   init_stat_off (s);
   /* offset must evenly divide nval */
   for (vi = 0; vi != nval - offset; vi++) {
#ifndef NDEBUG
      printf ("vals[%d]:%d %c\n", (int) vi, (int) (vals[vi]), (char) (vals[vi])); fflush (stdout);
      printf ("vals[%d]:%d %c\n", (int) (vi + offset), (int) (vals[vi + offset]), (char) (vals[vi + offset])); fflush (stdout);
#endif
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
      update_stat_off (s, vals[vi], vals[vi + offset]);
	#pragma GCC diagnostic pop
      /*update_stat (s, vals[vi]);*/
   }
   /* otherwise */
   /*for ( ;      vi != nval;          vi++)
      update_stat (s, vals[vi]);*/
   finish_stat_off (s);
}
