#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define KETA 30

struct NUMBER{
  int n[KETA]; //各桁の値
  int sign; //符号変数(1なら正or0, -1なら負)
};

void setSign(struct NUMBER *a, int s);

int getSign(const struct NUMBER *a);

void clearByZero(struct NUMBER *a);

void dispNumber(const struct NUMBER *a);

void dispNumberZeroSuppress(const struct NUMBER *a);

//aの下位k桁に乱数値をセットする
void setRnd(struct NUMBER *a, int k);

void copyNumber(const struct NUMBER *a, struct NUMBER *b);

void getAbs(const struct NUMBER *a, struct NUMBER *b);

int isZero(const struct NUMBER *a);
//aを10倍した値をbに代入する
int mulBy10(const struct NUMBER *a, struct NUMBER *b);

int divBy10(const struct NUMBER *a, struct NUMBER *b);

int setInt(struct NUMBER *a, int x);

int getInt(const struct NUMBER *a, int *x);

int numComp(const struct NUMBER *a, const struct NUMBER *b);

//加算
//a + b = c
int add(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c);

//減算
//a - b = c
int sub(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c);

//インクリメント
//a + 1 = b
int increment(const struct NUMBER *a,struct NUMBER *b);

int decrement(const struct NUMBER *a, struct NUMBER *b);

void swap(struct NUMBER *a, struct NUMBER *b);

//正誤判定
void diff(int count);

int simpleMultiple(int a, int b, int *c);

int multiple(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c);

int divide(struct NUMBER *a, struct NUMBER *b, struct NUMBER *c, struct NUMBER *d);
