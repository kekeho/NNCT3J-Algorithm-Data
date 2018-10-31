#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mulprec.h"

int main(int argc, char const *argv[]) {
  struct NUMBER a, b;
  setRnd(&a, 10);
  dispNumber(&a);
  printf("\n");
  setRnd(&b, 10);
  dispNumber(&b);
  printf("\n");
  printf("%d\n", numComp(&a, &b));
  
}