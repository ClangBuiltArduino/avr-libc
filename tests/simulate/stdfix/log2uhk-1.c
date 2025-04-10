#if defined (USE_AVRTEST) && !defined (__AVR_TINY__)

#include <stdlib.h>
#include <stdint.h>
#include <stdfix.h>

#include "avrtest.h"

// Make sure that the absolute error is in the expected range for
// all values in [1, 2).

void test_log2 (void)
{
  float d_mi = +1000;
  float d_ma = -1000;
  uint32_t cyc = 0;

  for (uint16_t i = 0x100; i <= 0x1ff; ++i)
    {
      // Run for all ua in [1, 2).
      unsigned short accum ua = uhkbits (i);

      avrtest_cycles_call ();
      short accum la = log2uhk (ua);
      uint32_t c = avrtest_cycles ();
      if (c > cyc) cyc = c;

      float f1 = avrtest_log2f (avrtest_ldexpf (i, -8));
      float f2 = la;

      float d = avrtest_subf (f2, f1);

      d_ma = avrtest_fmaxf (d, d_ma);
      d_mi = avrtest_fminf (d, d_mi);
      if (d_ma > +0.008f) exit (__LINE__);
      if (d_mi < -0.008f) exit (__LINE__);
    }

  LOG_FMT_FLOAT ("d_min = % f\n", d_mi);
  LOG_FMT_FLOAT ("d_max = % f\n", d_ma);
  LOG_FMT_U32 ("Cycles = %u\n", cyc);
}

int main (void)
{
  test_log2();

  return 0;
}

#else
int main (void)
{
  return 0;
}
#endif
