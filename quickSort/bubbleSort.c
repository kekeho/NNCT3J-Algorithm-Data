#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_LENGTH 100000

int inputArray[ARRAY_LENGTH];

void init(){
    //ソートする配列の用意
    int s;
    srand(time(NULL));
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        inputArray[i] = rand() % 1000; //0~1000
    }
}

void bubbleSort(){
    int j, flag;
    
    do {
        flag = 0;
        for (int i = 0; i < ARRAY_LENGTH - 1; i++) {
            if(inputArray[i] > inputArray[i+1]){
                flag = 1;
                j = inputArray[i];
                inputArray[i] = inputArray[i+1];
                inputArray[i+1] = j;
            }
        }
    } while(flag == 1);
}

int main(){
    init();
    
    printf("元データ: [ ");
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", inputArray[i]);
    }
    printf("]\n");
    
    bubbleSort();
    
    printf("ソート済みデータ: [ ");
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", inputArray[i]);
    }
    printf("]\n");
    
}
