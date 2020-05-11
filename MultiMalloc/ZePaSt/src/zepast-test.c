#if HAVE_CONFIG_H
#include <config.h>
#endif

#define _POSIX_C_SOURCE 200112L
#define __STDC_VERSION__ 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <zepast.h>
#include <mean.h>


__attribute__ ((nothrow, warn_unused_result))
int main (void) {

#ifdef TEST

   /*zepast_t z;*/
   /*stats_t ss[1];*/
   stat_t s[1];
   mean_t mean;
   char const str[] = "Hello, World!";
   unigram_t vals[sizeof (str)];
   size_t vi;

   /*z.statss = ss;*/
   /*z.nstats = ARRSZ (ss);*/

   (void) memcpy (vals, str, sizeof (str));

   s[0].init   = init_mean;
   s[0].update = update_mean;
   s[0].finish = finish_mean;
   s[0].stat   = &mean;

   /*ss[0].init   = init_stat;
   ss[0].update = update_stat;
   ss[0].finish = finish_stat;
   ss[0].stats  = s;
   ss[0].nstat  = ARRSZ (s);*/

   init_stats   (ss[0], ARRSZ (vals));
   for (vi = 0; vi != ARRSZ (vals); vi++)
      update_stats (ss[0], vals[vi], ARRSZ (vals));
   finish_stats (ss[0], vals, ARRSZ (vals));

   (void) printf ("mean:%d,%g\n", (int) (mean.sum), mean.res);
   return EXIT_SUCCESS;

#endif

}
