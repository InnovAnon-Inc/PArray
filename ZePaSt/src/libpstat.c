#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <pstat.h>

/*
stat_off_update (val1, val2):
	val = diff (val1, val2);
	stat_update (val);

stat_ngram_update (vals[], nval):
	ngram = combine (vals, nval)
	pstat_update (&ngram)

stat_mulvar_update (vals[], nval):
	ngram = combine (vals, nval)
	pstat_update (&ngram)
*/

__attribute__ ((leaf, nonnull (1), nothrow))
void init_pstat (pstat_t *restrict s) {
   s->init (s->stat);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void update_pstat (pstat_t *restrict s, unigram_t const vals[]) {
   s->update (s->stat, vals);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void finish_pstat (pstat_t *restrict s) {
   s->finish (s->stat);
}

#ifdef TEST
__attribute__ ((nonnull (1, 2), nothrow))
void ez_pstat_offset (
   pstat_t *restrict s,
   unigram_t const vals[], size_t nval, size_t offset) {
   size_t vi;
   /*s->init   = init_pstat_offset;
   s->update = update_pstat_offset;
   s->finish = finish_pstat_offset;*/
   init_pstat (s);
   /* offset must evenly divide nval */
   for (vi = 0; vi != nval - offset; vi++) {
      unigram_t p[2];
#ifndef NDEBUG
      printf ("vals[%d]:%d %c\n", (int) vi, (int) (vals[vi]), (char) (vals[vi])); fflush (stdout);
      printf ("vals[%d]:%d %c\n", (int) (vi + offset), (int) (vals[vi + offset]), (char) (vals[vi + offset])); fflush (stdout);
#endif
      p[0] = vals[vi];
      p[1] = vals[vi + offset];
      update_pstat (s, p);
      /*stat_off_update (vals[vi], vals[vi + offset]);*/
      /*update_stat (s, vals[vi]);*/
   }
   /* otherwise */
   /*for ( ;      vi != nval;          vi++)
      update_stat (s, vals[vi]);*/
   finish_pstat (s);
}
#endif

TODO (correlate ngrams of different vectors)
/*TODO (correlate offsets of different vectors ?)*/
TODO (diff between ngrams at offsets... correlate diffs for different vectors)
