#include <stdio.h>

int main(int argc, char const *argv[]) {
  float a = 1.23456e10;
  float b = 7.89012e-3;
  float c = 7.89012e2;
  float d, e;
  
  d = a + b;
  e = a + c;
  
  printf("a = %25.10f\n", a);
  printf("b = %15.10f\n", b);
  printf("c = %25.10f\n", c);
  printf("a+b = %25.10f\n", d);
  printf("a+c = %25.10f\n", e);
  return 0;
}