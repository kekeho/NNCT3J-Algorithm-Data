#include <stdio.h>

#define N 900000000

int main(int argc, char const *argv[]) {
  int i;
  double s1 = 0.0;
  double s2 = 0.0;
  double c;
  double t, y;
  
  //単純なループによる総和
  for (int i = 0; i < N; i++) {
    s1 += 0.1;
  }
  
  //kahan way
  c = 0.0;
  for (int i = 0; i < N; i++) {
    y = 0.1 - c;
    t = s2 + y;
    c = (t - s2) - y;
    s2 = t;
  }
  
  printf("SIMPLE WAY: %23.15f\n", s1);
  printf("KAHAN WAY: %23.15f\n", s2);
  
  return 0;
}