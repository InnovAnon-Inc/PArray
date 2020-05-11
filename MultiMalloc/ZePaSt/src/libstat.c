#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <stat.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_stat (stat_t *restrict s) {
   s->init (s->stat);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void update_stat (stat_t *restrict s, unigram_t val) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
   s->update (s->stat, val);
	#pragma GCC diagnostic pop
}

/* naive implementation */
/*__attribute__ ((leaf, nonnull (1, 2), nothrow))
void updates_stat_naive (
   stat_t *restrict s,
   unigram_t val[], size_t nval) {
   size_t vi;
   for (vi = 0; vi != nval; vi++)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
      update_stat (s, val[vi], nval);
	#pragma GCC diagnostic pop
}*/

/* assuming your alternative implementation for multiple updates
 * can do better than multiplying the Big-Theta by n,
 * where n is the number of updates (i.e., nval) */
/*__attribute__ ((leaf, nonnull (1, 2), nothrow))
void updates_stat (
   stat_t *restrict s,
   unigram_t vals[], size_t nval) {
   s->updates (s->stats, vals, nval);
}*/

__attribute__ ((leaf, nonnull (1), nothrow))
void finish_stat (stat_t *restrict s) {
   s->finish (s->stat);
}

__attribute__ ((nonnull (1, 2), nothrow))
void ez_stat (
   stat_t *restrict s,
   unigram_t const vals[], size_t nval) {
   size_t vi;
   init_stat (s);
   for (vi = 0; vi != nval; vi++) {
#ifndef NDEBUG
      printf ("vals[%d]:%d %c\n", (int) vi, (int) (vals[vi]), (char) (vals[vi])); fflush (stdout);
#endif
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
      update_stat (s, vals[vi]);
	#pragma GCC diagnostic pop
   }
   finish_stat (s);
}

TODO (random sampling for sublinear time)
TODO (dynamic programming parallel version of ez_stat())
