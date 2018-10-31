#include "stdio.h"

#define STEPS 15 //4段
struct heap_template{
    int box[STEPS];
    int size; //次に値を挿入する場所
};
typedef struct heap_template heap;

void InitHeap(heap *h){
    for (int i = 0; i < STEPS; i++){
		h->box[i] = 0;
	}
    h->size = 0;
}

void InsertHeap(heap *h, int x){
    h->box[h->size] = x;
    h->size++;
    
    int now = h->size-1;
    while (1) {
        int mother = (now-1)/2;
        if (now == 0) {
            break;
        } else if (h->box[mother] < h->box[now]) {
            int m = h->box[mother];
            h->box[mother] = h->box[now];
            h->box[now] = m;
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
        printf("%d\n", h->box[i]);
    }
    return 0;
}

void DeleteHeap(heap *h){
    int now = h->size-1;
    h->box[0] = h->box[now];
    now = 0;
    h->size--;
        
    while (1) {
        int leftson = h->box[now*2+1];
        int rightson = h->box[now*2+2];
        int bigson;
        int bigsonSize;
        
        //左右でどちらが大きい子か判定
        if (leftson < rightson) {
            bigson = rightson;
            bigsonSize = now*2+2;
        } else {
            bigson = leftson; //子がどちらも同じ値だった場合の処理は左優先とした
            bigsonSize = now*2+1;
        }
        
        //入れ替え処理
        if (bigson > h->box[now]){
            int b = bigson;
            bigson = h->box[now];
            h->box[now] = b;
            now = bigsonSize;
        } else {
            break;
        }
    }
    
    //pop操作
    for(int i = 0; i < h->size; i++){
        h->box[i] = h->box[i+1];
    }
}

int main() {
    heap h;
    InitHeap(&h);
    InsertHeap(&h, 9);
    InsertHeap(&h, 8);
    InsertHeap(&h, 5);
    InsertHeap(&h, 7);
    InsertHeap(&h, 3);
    InsertHeap(&h, 2);
    InsertHeap(&h, 4);
    InsertHeap(&h, 6);
    InsertHeap(&h, 1);
    int top = TopHeap(&h);
    printf("TOPHEAP: %d\n", top);
    PrintAllHeap(&h);
    puts("------");
    DeleteHeap(&h);
    DeleteHeap(&h);
    DeleteHeap(&h);
    DeleteHeap(&h);
    PrintAllHeap(&h);
    return 0;
}
