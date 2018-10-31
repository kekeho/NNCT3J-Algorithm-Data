// 出席番号: 417番
// 氏名: 竹村 太希
// 課題内容: ヒープソートを実装し、ランダムな数列を昇順にソートし出力する。

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define True 1
#define False 0

#define STEPS 30
struct heap_template{
    int box[STEPS];
    int size; //次に値を挿入する場所
};
typedef struct heap_template heap;

void swap(int *i, int *j){
    int temp;
    temp = *i;
    *i = *j;
    *j = temp;
}

void InitHeap(heap *h){
    for (int i = 0; i < STEPS; i++){
		h->box[i] = 0;
	}
    h->size = 0;
}

//実装完了
void InsertHeap(heap *h, int x){
    h->box[h->size] = x;
    h->size++;
    
    int now = h->size-1; //値を挿入した場所
    while (1) {
        int mother = (now-1)/2; //親の格納されている場所
        if (now == 0) { //根に格納
            break;
        } else if (h->box[mother] < h->box[now]) { //子の方が大きい場合
            swap(&h->box[mother], &h->box[now]);
            now = mother;
        } else {
            break;
        }
    }
}

int TopHeap(heap *h){
    return h->box[0];
}

int PrintAllHeap(heap *h){
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->box[i]);
    }
    return 0;
}


void DeleteHeap(heap *h){
    swap(&h->box[h->size-1], &h->box[0]); //rootと末尾要素を交換
    h->size--; //末尾要素を除外

    int focus = 0;

    while(True){
        int leftson_position = focus*2+1; //左の子
        int rightson_position = focus*2+2; //右の子
        int bigson_position;

        //大きい子を判別
        if(h->box[leftson_position] > h->box[rightson_position]){
            bigson_position = leftson_position;
        } else {
            bigson_position = rightson_position;
        }

        if(bigson_position >= h->size){
            break;
        }

        if(h->box[bigson_position] > h->box[focus]){
            swap(&h->box[focus], &h->box[bigson_position]);
            focus = bigson_position;
        } else {
            break;
        }
    }
}

void heap_sort(int *array, int array_length){
    heap h;
    InitHeap(&h);
    
    for(int i = 0; i < array_length; i++){
        InsertHeap(&h, array[i]);
    }

    printf("Array: %d\n", array_length);

    for(int i = array_length-1; i >= 0; i--){
        array[i] = TopHeap(&h);
        DeleteHeap(&h);
        if(i == 0 && array[i] > array[i+1]){
            swap(&array[i], &array[i+1]);
        }
    }
}

int main() {
    int array[STEPS];
    srand((unsigned)time(NULL));

    //配列にに0~100未満の乱数を30個挿入
    for(int i = 0; i < STEPS; i++){
        array[i] =  rand()%100;
    }

    printf("Generated array:\n");
    
    for(int i = 0; i < STEPS; i++){
        printf("%d ", array[i]);
    }
    putchar('\n');
    

    //配列をヒープソート
    heap_sort(array, STEPS);
    
    printf("\nSorted:\n");
    for(int i = 0; i < STEPS; i++){
        printf("%d ", array[i]);
    }
    
    
}
