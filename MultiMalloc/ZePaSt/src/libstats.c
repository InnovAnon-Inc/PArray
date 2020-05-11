#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <stats.h>

#ifdef TEST

/* override this with a version that uses memset and no loop */
__attribute__ ((leaf, nonnull (1), nothrow))
void init_stats (
   stats_t s[], size_t nstat,
   size_t nval) {
   size_t si;
	#pragma GCC ivdep
   for (si = 0; si != /*s->*/nstat; s++)
      s->init (s->stats[si], nval);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void update_stats (
   stats_t s[], size_t nstat,
   unigram_t val, size_t nval) {
   size_t si;
	#pragma GCC ivdep
   for (si = 0; si != /*s->*/nstat; s++)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
      s->update (s->stats[si], val, nval);
	#pragma GCC diagnostic pop
}

/*__attribute__ ((leaf, nonnull (1, 2), nothrow))
void updates_stats0 (
   stats_t *restrict s,
   unigram_t vals[], size_t nval) {
   size_t si;
	#pragma GCC ivdep
   for (si = 0; si != s->nstat; s++)
      s->updates (s->stats[si], vals, nval);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void updates_stats1 (
   stats_t *restrict s,
   unigram_t vals[], size_t nval) {
   size_t vi;
	#pragma GCC ivdep
   for (vi = 0; vi != nval; vi++)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wtraditional-conversion"
      update_stats (s, vals[vi], nval);
	#pragma GCC diagnostic pop
}*/

__attribute__ ((leaf, nonnull (1), nothrow)) ;
void finish_stats (stats_t s[], size_t nstat, size_t nval) {
   size_t si;
   for (si = 0; si != s->nstat; s++)
      s->finish (s->stats[si], nval);
}

#endif
