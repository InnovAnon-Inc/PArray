#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <stat.h>
#include <mean.h>
/*#include <variance.h>*/

__attribute__ ((nothrow, warn_unused_result))
int main (void) {
   stat_t s[2];
   mean_t mean;
   /*variance_t variance;*/
   char const str[] = "Hello, World!";
   unigram_t vals[sizeof (str) * sizeof (char)];
   size_t vi;

   /*(void) memcpy (vals, str, sizeof (str));*/
   TODO (check overflow)
	#pragma GCC ivdep
   for (vi = 0; vi != ARRSZ (vals); vi++)
      vals[vi] = (unigram_t) str[vi];

   /*s[0].init   = init_mean;
   s[0].update = update_mean;
   s[0].finish = finish_mean;
   s[0].stat   = &mean;*/
   init_mean (s + 0, &mean);
   ez_stat (s + 0, vals, ARRSZ (vals));

   /*variance.ct = mean.res;
   s[1].init   = init_variance;
   s[1].update = update_mean;
   s[1].finish = finish_mean;
   s[1].stat   = &variance;
   ez_stat (s + 1, vals, ARRSZ (vals));*/

   (void) printf ("sum:%d\n",      (int) (mean.sum));
   (void) printf ("mean:%g\n",     mean.res);
   /*(void) printf ("variance:%g\n", variance.sum);
   (void) printf ("stddev:%g\n",   variance.res);*/
   return EXIT_SUCCESS;
}
