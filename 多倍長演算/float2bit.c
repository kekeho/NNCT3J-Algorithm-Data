#include "stdio.h"

int main(int argc, char const *argv[]) {
  float f = -12.3456; //0xc0490fd0
  unsigned char *p;
  p = (unsigned char *)&f;
  printf("%02x %02x %02x %02x\n", *(p+3), *(p+2), *(p+1), *p; //16進数
  
  return 0;
}