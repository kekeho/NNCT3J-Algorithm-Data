#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef True
#define True 1
#endif
#ifndef False
#define False 0
#endif
#ifndef bool
#define bool int
#endif

int seeds[6] = {3, 5, 7 ,11, 13, 17};

int GetFactor(int n, int seed);
bool IsPrime(int num);
int f(int x, int n, int seed);
int Gcd(int a, int b);

int GetFactor(int n, int seed) {
  if (n % 2 == 0) {
    return 2;
  }
  if (IsPrime(n)) {
    return n;
  }
  int x = 2;
  int y = 2;
  int d = 1;
  int count = 0;
  while (d == 1) {
    count++;
    x = f(x, n, seed);
    y = f(f(y, n, seed), n, seed);
    d = Gcd(abs(x - y), n);
  }
  //見つからない場合はシードを変えてチャレンジ
  if (d == n) {
    return GetFactor(n, seed+1);
  }
  //素数でない場合再度チャレンジ
  return GetFactor(d, 1);
}

int f(int x, int n, int seed){
  return (seeds[seed % 6] * x + seed) % n;
}

int Gcd(int a, int b){
  if (a < b) {
    return Gcd(b, a);
  }
  if(b == 0){
    return a;
  }
  int d = 0;
  do {
    d = a % b;
    a = b;
    b = d;
  } while(d != 0);
  return a;
}

bool IsPrime(int number){
  int boundary = floor(sqrt(number));
  if (number == 1) {
    return False;
  }
  if (number == 2) {
    return True;
  }
  for (int i = 2; i <= boundary; i++) {
    if (number % i == 0){
      return False;
    }
  }
  return True;
}

int main(int argc, char const *argv[]) {
  int n = atoi(argv[1]);
  while (n > 1) {
    int factor = GetFactor(n, 1);
    printf("%d\n", factor);
    n = n / factor;
  }
  return 0;
}