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
  struct NUMBER a, b, c, d, _ans;
  setInt(&a, 50);
  setInt(&b, 4);
  divide(&a, &b, &c, &d);
  multiple(&a, &b, &_ans);
  //fastDivide(&a, &b, &c, &d);
  dispNumber(&_ans);
  putchar('\n');
}