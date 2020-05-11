#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#define NDEBUG 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*#include <mean.h>*/
#include <sum.h>
#include <variance.h>
#include <stat_off_diff.h>

__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   sum_t sum;
   variance_t variance;
   stat_t sum_stat;
   stat_t var_stat;
   size_t offset = 2; /* cant' be odd until I fix a TODO */

   char const str[] = "Hello, World!";
   unigram_t vals[sizeof (str) * sizeof (char)];
   size_t vi;

   /*(void) memcpy (vals, str, sizeof (str));*/
   TODO (check overflow)
#ifndef NDEBUG
   printf ("ARRSZ (vals):%d\n", (int) ARRSZ (vals)); fflush (stdout);
#endif
	#pragma GCC ivdep
   for (vi = 0; vi != ARRSZ (vals); vi++) {
      vals[vi] = (unigram_t) str[vi];
#ifndef NDEBUG
      printf ("vals[%d]:%d %c\n", (int) vi,
         (int) (vals[vi]), (char) (vals[vi])); fflush (stdout);
#endif
   }
   /*sum_stat.init   = init_sum;
   sum_stat.update = update_sum;
   sum_stat.finish = finish_sum;
   sum_stat.stat   = &sum;*/
   init_sum_stat (&sum_stat, &sum);
   ez_stat_off_diff (&sum_stat, vals, ARRSZ (vals), offset);

#ifndef NDEBUG
   (void) printf ("sum:%d\n",  (int) (mean.sum));
   (void) printf ("mean:%g\n", mean.res);
#endif

   /*variance.ct = mean.res;*/
   variance.ct = (double) sum / (double) ARRSZ (vals);
   if (ARRSZ (vals) >= 30) variance.df = ARRSZ (vals) - 1;
   else                    variance.df = ARRSZ (vals);
   /*var_stat.init   = init_variance;
   var_stat.update = update_variance;
   var_stat.finish = finish_variance;
   var_stat.stat = &variance;*/
   init_variance_stat (&var_stat, &variance);
   ez_stat_off_diff (&var_stat, vals, ARRSZ (vals), offset);

   (void) printf ("variance:%g\n", variance.sum);
   (void) printf ("stddev:%g\n",   variance.res);

   return EXIT_SUCCESS;
}
