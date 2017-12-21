/*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
  出席番号: 424
  氏名   : 竹村 太希
  課題内容: クイックソートのC言語による実装
      0以上1000未満の数値50個をランダムに決め、これを
      クイックソートによりソートして出力するプログラムを作成する。
*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_LENGTH 5

int fstArray[ARRAY_LENGTH];
int finalArray[ARRAY_LENGTH];
int finalCount = 0;

void init(){
    //ソートする配列の用意
    int s;
    srand(time(NULL));
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        fstArray[i] = rand() % 1000; //0~1000
    }
}

int takePivot(int *inputArray, int min, int middle, int max){
      if (inputArray[min] >= inputArray[middle])
         if (inputArray[middle] >= inputArray[max])
             return middle;
         else if (inputArray[min] <= inputArray[max])
             return middle;
         else
             return max;
      else if (inputArray[min] > inputArray[max])
             return min;  
      else if (inputArray[middle] > inputArray[max])
              return max;
      else
              return middle;
}

int quickSort(int *inputArray,int nowArrayLength){
    if (nowArrayLength <= 1) {
        finalArray[finalCount] = inputArray[0];
        finalCount++;
        return 0;
    }
    
    //pivotの取得
    int pivot = takePivot(inputArray, 0, nowArrayLength/2, nowArrayLength-1);
    
    while(1){    
        //leftの取得
        int left = 0;
        while(inputArray[pivot] >= inputArray[left]){
            left++;
        }
        
        //rightの取得
        int right = nowArrayLength-1;
        while (inputArray[pivot] <= inputArray[right]) {
            right--;
        }
        
        if (left >= right) {
            //leftとrightが逆転した場所で区切る            
            int leftLength = right;
            int rightLength = nowArrayLength - right;
            int leftArray[leftLength];
            int rightArray[rightLength];
            for (int i = 0; i < leftLength; i++) {
                leftArray[i] = inputArray[i];
                printf("%d\n", leftArray[i]);
            }
            putchar('-');
            putchar('\n');
            for (int i = 0; i < rightLength ; i++) {
                rightArray[i] = inputArray[leftLength + i];
            }
            
            quickSort(leftArray, leftLength);
            quickSort(rightArray, rightLength);
            break;
        }else{
            //値の入れ替え
            int logBox = inputArray[left];
            inputArray[left] = inputArray[right];
            inputArray[right] = logBox;
        }
    }
    
}

int main() {
    init();
    quickSort(fstArray, ARRAY_LENGTH);
    
    printf("FIN!\n");
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", finalArray[i]);
    }
    putchar('\n');
    return 0;
}
