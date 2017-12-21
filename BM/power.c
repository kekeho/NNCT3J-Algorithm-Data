#include <stdio.h>
#include <stdlib.h>

#define STR 11
#define FINDSTR 3

char str[STR] = "ABABCDEFGHA";
char findStr[FINDSTR] = "ABC";

int main() {
  int flag = 0;
  for (int i = 0; i < STR; i++) {
    for (int j = 0; j < FINDSTR; j++) {
      if (str[i+j] == findStr[j]){
        flag++;
      } else {
        flag--;
      }
    }
    if(flag == FINDSTR){
      printf("DONE! %d番目\n", i);
      return 1;
    } else {
      flag = 0;
    }
  }

  printf("ERROR: -1\nThere is nothing \"%s\"\n", findStr);
  return -1;
}
