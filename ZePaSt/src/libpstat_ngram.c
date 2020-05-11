#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <pstat_ngram.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_pstat_ngram (pstat_ngram_t *restrict s) {
   init_pstat (s->stat);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void update_pstat_ngram (pstat_ngram_t *restrict s,
   unigram_t const ngram[]) {
   /*s->combine (val, ngram);*/
   update_pstat (s->stat, ngram);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void finish_pstat_ngram (pstat_ngram_t *restrict s) {
   finish_pstat (s->stat);
}

__attribute__ ((nonnull (1, 2), nothrow))
void ez_pstat_ngram (
   pstat_t *restrict stat,
   unigram_t const vals[], size_t nval, size_t n) {
   size_t vi, vj;
   /*s->init   = init_pstat_ngram;
   s->update = update_pstat_ngram;
   s->finish = finish_pstat_ngram;*/
   pstat_ngram_t s;
   s.stat = stat;
   init_pstat_ngram (&s);
   /* n must evenly divide nval */
   for (vi = 0; vi != nval - n; vi += n) {
      update_pstat_ngram (&s, vals + vi);
      /*stat_ngram_update (vals + vi, n);*/
      /*for (vj = 0; vj != n; vj++)
         update_stat (s, vals[vi + vj]);*/
   }
   /* otherwise */
   /*for ( ;      vi != nval;     vi++)
      update_stat (s, vals[vi]);*/
   finish_pstat_ngram (&s);
}
