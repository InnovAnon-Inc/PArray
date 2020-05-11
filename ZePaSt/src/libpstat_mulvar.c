#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <pstat_mulvar.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_pstat_mulvar (pstat_mulvar_t *restrict s) {
   init_pstat (s->stat);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void update_pstat_mulvar (pstat_mulvar_t *restrict s, unigram_t const val[]) {
   /*ngram_t val = s->combine (ngram);*/
   update_pstat (s->stat, val);
}

__attribute__ ((leaf, nonnull (1), nothrow))
void finish_pstat_mulvar (pstat_mulvar_t *restrict s) {
   finish_pstat (s->stat);
}

__attribute__ ((nonnull (1, 2, 4), nothrow))
void ez_pstat_mulvar (
   pstat_t *restrict stat,
   unigram_t const *restrict vals[], size_t nval,
   unigram_t vars[], size_t nvar) {
   size_t vali, vari;
   pstat_mulvar_t s;
   s.stat = stat;
   /*s->init   = init_pstat_mulvar;
   s->update = update_pstat_mulvar;
   s->finish = finish_pstat_mulvar;*/
   TODO (e.g. cache-aware loop-blocking)
   TODO (if nval is really big... i.e. vals[*][vali])
   TODO (then it will be slow to load the models vals)
   init_pstat_mulvar (&s);
   for (vali = 0; vali != nval; vali++)
      for (vari = 0; vari != nvar; vari++) {
         vars[vari] = vals[vari][vali];
         update_pstat_mulvar (&s, vars);
         /*stat_update (s, vals[0][vali]);*/
      }
   finish_pstat_mulvar (&s);
}
