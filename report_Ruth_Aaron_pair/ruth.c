#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mulprec.c"

int main() {
  struct NUMBER a;
  clearByZero(&a);
  setInt(&a, 10);
  // dispNumber(&a);
  return 0;
}