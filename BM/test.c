#include <stdio.h>
#include <time.h>
struct timeval start_time;

int main(int argc, char const *argv[]) {
  time_t tBegin = time(NULL);
  int bf = 0;
  for (int i = 0; i < 9000; i++) {
    bf++;
  }
  time_t tEnd = time(NULL);
  printf("%ld - %ld\n", tBegin, tEnd);
  return 0;
}
