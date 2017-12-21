#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int main(int argc, char const *argv[]) {
  struct NUMBER a, b, c, d, e;
  int r;
  
  srandom(time(NULL));
  
  clearByZero(&a);
  printf("a = ");
  dispNumber(&a);
  printf("\n");
  
  setRnd(&b, 10);
  printf("b = ");
  dispNumber(&b);
  printf("\n");
  
  copyNumber(&b, &c);
  printf("b = ");
  dispNumber(&c);
  printf("\n");
  
  r = mulBy10(&b, &d);
  printf("b * 10 = ");
  dispNumber(&d);
  printf(", r = %d\n", r);
  
  r = divBy10(&c, &e);
  printf("c / 10 =");
  dispNumber(&e);
  printf(", r = %d\n", r);
  
  printf("a == 0? --> %d\n", isZero(&a));
  printf("b == 0? --> %d\n", isZero(&b));
  printf("c == 0? --> %d\n", isZero(&c));
  printf("d == 0? --> %d\n", isZero(&d));
  printf("e == 0? --> %d\n", isZero(&e));
  return 0;
}