#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mulprec.c"

#ifndef True
#define True 1
#endif
#ifndef False
#define False 0
#endif
#ifndef bool
#define bool int
#endif

int main() {
  struct NUMBER a;
  clearByZero(&a);
  setInt(&a, 10);
  // dispNumber(&a);
  return 0;
}