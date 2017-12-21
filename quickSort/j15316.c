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

int array[ARRAY_LENGTH];
int swapCount = 0;
int cmpCount = 0;

void init(){
    //ソートする配列の用意
    int s;
    srand(time(NULL));
    for (int i = 0; i < ARRAY_LENGTH; i++) {
        array[i] = rand() % 1000; //0~1000
    }
}

void display(int array[], int start, int end, int opt){
    int i;
    printf("[ ");
    if (opt == 0) {
        //ふつう
        for(i = start; i < end + 1; i++){
            printf("%d ", array[i]);
        }
    } else {
        //down表示
        for(i = end; i >= start; i--){
            printf("%d ", array[i]);
        }
    }
    printf(" ]");   
}

int takePivot(int *inputArray, int min, int middle, int max){
      if (inputArray[min] >= inputArray[middle])
         if (inputArray[middle] >= inputArray[max])
             return array[middle];
         else if (inputArray[min] <= inputArray[max])
             return array[middle];
         else
             return array[max];
      else if (inputArray[min] > inputArray[max])
             return array[min];  
      else if (inputArray[middle] > inputArray[max])
              return array[max];
      else
              return array[middle];
}


// 二つの値を交換する関数
void swap(int* num1, int* num2){
	if (*num1 != *num2){
		int logBox = *num1;
        *num1 = *num2;
        *num2 = logBox;
	}
}

void quickSort(int array[], int start, int end){
	if (start != end && start < end){
		int pivot;

		pivot = takePivot(array, start, (end-start)/2, end);
        printf("Pivot: %d\n", pivot);

		int left = start;
		int right = end;

		while (1){
			while (left <= end){
				if (array[left] >= pivot){
                    cmpCount++;
					break;			
				}
                cmpCount++;
				left++;
			}

			while (right >= start){
				if (array[right] < pivot){
                    cmpCount++;
					break;
				}
                cmpCount++;
				right--;
			}

			if (left == right + 1){
				if (right < start){
					right = start;
					left = start + 1;

					if (array[start] > array[end]){
						swap(&array[start], &array[end]);
					}
                    cmpCount++;
				}
                cmpCount+=2;
				break;
			}else{
				swap(&array[left], &array[right]);
                swapCount++;
			}
		}
        
        display(array, start, right, 0);
        printf("\x1b[31m");
        printf("|");
        printf("\x1b[39m");
        display(array, left, end, 0);
        putchar('\n');
        
		quickSort(array, start, right );
		quickSort(array, left, end);		
	}else{
        printf("pivot: %d\n [ %d ]\n\n", array[start], array[start]);
    }
}

void main(int argc, char const *argv[]){
    if (argc > 1) {
        if (argv[1][1] == 'd') {
            init();
            printf("元データ: [ ");
            for (int i = 0; i < ARRAY_LENGTH; i++) {
                printf("%d ", array[i]);
            }
            printf("]\n");
            
            quickSort(array, 0, ARRAY_LENGTH);
            printf("Result of sort\n");
            display(array, 0, ARRAY_LENGTH-1, 1);
        }
    } else{
        init();
        printf("元データ: [ ");
        for (int i = 0; i < ARRAY_LENGTH; i++) {
            printf("%d ", array[i]);
        }
        printf("]\n");
        
        quickSort(array, 0, ARRAY_LENGTH);
        printf("\nソート結果\n");
        display(array, 1, ARRAY_LENGTH, 0);
        putchar('\n');
        printf("交換回数: %d回\n", swapCount);
    }
}
