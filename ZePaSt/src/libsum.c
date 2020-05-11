#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <sum.h>

__attribute__ ((leaf, nonnull (1), nothrow))
void init_sum (void *restrict _dest) {
   sum_t *restrict dest = (sum_t *restrict) _dest;
   *dest = 0;
#ifndef NDEBUG
   printf ("dest:%d\n", (int) dest); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1), nothrow))
void update_sum (void *restrict _dest, unigram_t val) {
   sum_t *restrict dest = (sum_t *restrict) _dest;
   TODO (check overflow)
#ifndef NDEBUG
   printf ("sum:%d\n", (int) (*dest)); fflush (stdout);
#endif
   *dest += val;
#ifndef NDEBUG
   printf (">sum:%d\n", (int) (*dest)); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1), nothrow))
void finish_sum (void *restrict _dest) {
   sum_t *restrict dest = (sum_t *restrict) _dest;
#ifndef NDEBUG
   printf ("sum:%d\n", (int) (*dest)); fflush (stdout);
#endif
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_sum_stat (stat_t *restrict stat, sum_t *restrict sum) {
   stat->init   = init_sum;
   stat->update = update_sum;
   stat->finish = finish_sum;
   stat->stat   = sum;
}

__attribute__ ((nonnull (1, 2), nothrow))
void ez_sum (
   sum_t *restrict sum,
   unigram_t const vals[], size_t nval) {
   stat_t s;
   init_sum_stat (&s, sum);
   ez_stat (&s, vals, nval);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
sum_t ezr_sum (unigram_t const vals[], size_t nval) {
   sum_t sum;
   ez_sum (&sum, vals, nval);
   return sum;
}
