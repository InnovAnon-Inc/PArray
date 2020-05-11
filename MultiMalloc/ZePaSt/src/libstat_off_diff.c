#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#ifndef NDEBUG
#include <stdio.h>
#endif

#include <stat_off_diff.h>

__attribute__ ((const, leaf, warn_unused_result))
unigram_t diff_stat_off (unigram_t left, unigram_t right) {
#ifndef NDEBUG
   printf ("left :%d %c\n", (int) left,  (char) left);  fflush (stdout);
   printf ("right:%d %c\n", (int) right, (char) right); fflush (stdout);
#endif
   return (unigram_t) (right - left);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_stat_off_diff (
   stat_off_t *restrict stat_off,
   stat_t *restrict stat) {
   stat_off->stat = stat;
   stat_off->diff = diff_stat_off;
   /*s.init   = init_stat_off_diff;
   s.update = update_stat_off_diff;
   s.finish = finish_stat_off_diff;*/
}

__attribute__ ((nonnull (1, 2), nothrow))
void ez_stat_off_diff (
   stat_t *restrict stat,
   unigram_t const vals[], size_t nval, size_t offset) {
   stat_off_t s;
   init_stat_off_diff (&s, stat);
   ez_stat_off (&s, vals, nval, offset);
}
