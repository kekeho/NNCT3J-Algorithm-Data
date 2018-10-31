#include "stdio.h"
int main() {
  int x = -123456;
  unsigned char *p;
  
  p = (unsigned char *)&x;
  printf("%02x %02x %02x %02x\n", *(p+3), *(p+2), *(p+1), *p);
  
  return 0;
}