#include "stdio.h"
#include "float.h"

int main(int argc, char const *argv[]) {
  float floatE = 1.0;
  while (1) {
    if (1.0 + floatE == 1.0) {
      break;
    } else {
      floatE = floatE/2;
    }
  }
  
  double doubleE = 1.0;
  while (1) {
    if (1.0 + doubleE == 1.0) {
      break;
    } else {
      doubleE = doubleE/2;
    }
  }
  
  
  printf("float result: %10.10e\n", floatE);
  printf("FLT_EPSILON: %10.10e\n", FLT_EPSILON);
  printf("double result: %10.10e\n", doubleE);
  printf("DBL_EPSILON: %10.10e\n", DBL_EPSILON);
  return 0;
}