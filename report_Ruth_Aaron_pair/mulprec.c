#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define KETA 30

#ifndef True
#define True 1
#endif
#ifndef False
#define False 0
#endif
#ifndef bool
#define bool int
#endif

struct NUMBER{
  int n[KETA]; //各桁の値
  int sign; //符号変数(1なら正or0, -1なら負)
};

void setSign(struct NUMBER *a, int s){
  a->sign = s;
}

int getSign(const struct NUMBER *a){
  return a->sign;
}

void clearByZero(struct NUMBER *a){
  for (int i = 0; i < KETA; i++) {
    a->n[i] = 0;
  }
  setSign(a, 1); //符号をプラスにセット
}

void dispNumber(const struct NUMBER *a){
  if (getSign(a) == 1) {
    printf(" +");
  } else if (getSign(a) == -1) {
    printf(" -");
  }
  
  for (int i = KETA-1; i >= 0; i--) {
    printf("%2d", a->n[i]);
  }
}

void dispNumberZeroSuppress(const struct NUMBER *a){
  if (getSign(a) == 1) {
    printf(" +");
  } else if (getSign(a) == -1) {
    printf(" -");
  }
  
  int i = KETA-1;
  while (a->n[i] == 0 && i > 0) {
    i--;
  }
  
  for (; i >= 0; i--) {
    printf("%2d", a->n[i]);
  }
}

//aの下位k桁に乱数値をセットする
void setRnd(struct NUMBER *a, int k){
  clearByZero(a);

	for(int i = 0;i < k; i++){
		a->n[i]=random()%10;
	}

	if(random()%2){
		setSign(a, 1);
	}else{
		setSign(a, -1);
	}
}

//bにaをcopy
void copyNumber(const struct NUMBER *a, struct NUMBER *b){
  setSign(b, getSign(a));
  for (int i = 0; i < KETA; i++) {
    b->n[i] = a->n[i];
  }
}

void getAbs(const struct NUMBER *a, struct NUMBER *b){
  copyNumber(a, b);
  setSign(b, 1);
}

int isZero(const struct NUMBER *a){
  int i = 0;
  while (a->n[i] == 0 && i < KETA) {
    i++;
  }
  if (i == KETA) {
    return 0;
  } else {
    return -1;
  }
}

//aを10倍した値をbに代入する
int mulBy10(const struct NUMBER *a, struct NUMBER *b){
  clearByZero(b);
  for (int i = 0; i < KETA-1; i++) {
    b->n[i+1] = a->n[i];
  }
  if (a->n[KETA-1]) {
    return -1; //オーバーフロー
  } else {
    return 0; //正常終了
  }
}

int divBy10(const struct NUMBER *a, struct NUMBER *b){
  clearByZero(b);
  for (int i = KETA-1; i >= 0; i--) {
    b->n[i-i] = a->n[i];
  }
  return a->n[0]; //余り
}

int setInt(struct NUMBER *a, int x){
  clearByZero(a);
  int memory = x;
  
  //桁数チェック
  int digit = 0;
  while(x!=0){
    x = x / 10;
    ++digit;
  }
  if (digit > KETA) {
    return -1;
  }
  
  //符号チェック
  if (memory < 0) {
    setSign(a, -1);
    memory = abs(memory);
  }
  

  for (int i = 0; i < KETA; i++) {
    a->n[i] = memory%10;
    memory -= a->n[i];
    memory/=10;
  }
  
  return 0;
  
}

int getInt(const struct NUMBER *a, int *x){
  x = 0;
  //桁数チェック
  // int k = KETA; //桁数
  // for (int i = KETA-1; i <= 0; i++) {
  //   if(a->n[i] > 0){
  //     break;
  //   }
  //   k--;
  // }
  
  for (int i = 0; i > KETA-1; i++) {
    x += a->n[i]*10^i;
  }
  
  return 0;
}

//aが大きければ1, bが大きければ-1, 等しければ0;
int numComp(const struct NUMBER *a, const struct NUMBER *b){
  if (getSign(a) > getSign(b)) {
    return 1;
  } else if (getSign(a) < getSign(b)){
    return -1;
  } else {
    //aとbの符号が同じ
    for (int i = KETA-1; i >= 0; i--) {
      if (a->n[i] > b->n[i]) {
        return 1;
      } else if (a->n[i] < b->n[i]) {
        return -1;
      }
    }
    return 0;
  }
}

int add(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c){
	int i;
	int e=0,buf;
	int ret=0;
	struct NUMBER Aabs,Babs;

	clearByZero(c);
	
	if(getSign(a)==1){
		if(getSign(b)==1){
			for(i=0;i<KETA;i++){
				buf=a->n[i]+b->n[i]+e;
				c->n[i]=buf%10;
				e=buf/10;
			}
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=sub(a,&Babs,c);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&Aabs);
			ret=sub(b,&Aabs,c);
		}
		if(getSign(b)==-1){
			getAbs(a,&Aabs);
			getAbs(b,&Babs);
			ret=add(&Aabs,&Babs,c);
			setSign(c,-1);
		}
	}

	if(e){
		ret=-1;
	}

	return ret;
}

int sub(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c){
	int i;
	int h=0,buf;
	int ret=0;
	struct NUMBER Aabs,Babs;

	clearByZero(c);

	if(getSign(a)==1){
		if(getSign(b)==1){
			if(numComp(a,b)==0||numComp(a,b)==1){
				for(i=0;i<KETA;i++){
					if(a->n[i]-h<b->n[i]){
						buf=10+a->n[i]-h-b->n[i];
						h=1;
					}else{
						buf=a->n[i]-h-b->n[i];
						h=0;
					}
					c->n[i]=buf;
				}
			}else{
				ret=sub(b,a,c);
				setSign(c,-1);
			}
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=add(a,&Babs,c);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&Aabs);
			ret=add(&Aabs,b,c);
			setSign(c,-1);
		}
		if(getSign(b)==-1){
			getAbs(b,&Babs);
			ret=add(a,&Babs,c);
		}
	}

	if(h){
		ret=-1;
	}

	return ret;
}

int increment(const struct NUMBER *a,struct NUMBER *b){
	struct NUMBER one;
	int ret;
	
	setInt(&one,1);
	ret=add(a,&one,b);

	return ret;
}

int decrement(const struct NUMBER *a,struct NUMBER *b){
	struct NUMBER one;
	int ret;

	setInt(&one,1);
	ret = sub(a,&one,b);

	return ret;
}

void swap(struct NUMBER *a, struct NUMBER *b){
	struct NUMBER c;
	clearByZero(&c);
	copyNumber(a, &c);
	copyNumber(b, a);
	copyNumber(&c, b);
}

int multiple(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c){
	int ret = 0,r1,r2,r3 = 0;
	int i,j;
	int buf = 0;
	int h = 0;
	struct NUMBER d,e;

	clearByZero(c);

	if(getSign(a)==1){
		if(getSign(b)==1){
			for(i=0;i<KETA;i++){
				clearByZero(&d);
				clearByZero(&e);
				h = 0;

				for(j=0;j<KETA;j++){
					buf = a->n[j]*b->n[i]+h;
					d.n[j] = buf%10;
					h = buf/10;
				}
				for(j=0;j<i;j++){
					r1 = mulBy10(&d,&e);
					swap(&d,&e);
				}

				r2 = add(c,&d,&e);
				copyNumber(&e,c);
			}
			if(h){
				r3 = -1;
			}
		}
		if(getSign(b)==-1){
			getAbs(b,&d);
			ret = multiple(a,&d,c);
			setSign(c,-1);
		}
	}
	if(getSign(a)==-1){
		if(getSign(b)==1){
			getAbs(a,&d);
			ret = multiple(&d,b,c);
			setSign(c,-1);
		}
		if(getSign(b)==-1){
			getAbs(a,&d);
			getAbs(b,&e);
			ret = multiple(&d,&e,c);
		}
	}

	if(r1||r2||r3) ret=-1;

	return ret;
}

int divide(const struct NUMBER *a,const struct NUMBER *b,struct NUMBER *c,struct NUMBER *d){
	struct NUMBER m,n;

	clearByZero(c);
	clearByZero(d);

    if(!isZero(b)) return -1;

	copyNumber(a,&n);

    while(1){
        if(numComp(&n,b)==-1) break;
		increment(c,&m);
		copyNumber(&m,c);
        sub(&n,b,&m);
		copyNumber(&m,&n);
	}
	copyNumber(&n,d);

    return 0;
}

//桁数を返す。array[0]は1桁目でなく0桁目と数える。
int digits_calculation(const struct NUMBER *a){
  int keta;
  for (int i = KETA-1; i >= 0; i--) {
    if (a->n[i] != 0) {
      keta = i;
      return keta;
    }
  }
  return -1; //error
}

//n桁右にシフトする。
int shift(struct NUMBER *a, int up){
  up++;
  int now_digits = digits_calculation(a);
  //オーバーフロー
  if(now_digits+up >= KETA){
    return -1;
  }
  //引き上げていくぅ!
  for (int i = now_digits; i >= 0; i--) {
    a->n[i+up] = a->n[i];
    a->n[i] = 0;
  }
  return 0;
}

void diff(int count){
	int i;
	int x,y,z,w,r;
	struct NUMBER a,b,c,d;

	clearByZero(&a);
	clearByZero(&b);
	clearByZero(&c);

	for(i=0;i<count;i++){
		x=random()%100000000;
		y=random()%100000000;
		setInt(&a,x);
		setInt(&b,y);
		divide(&a,&b,&c,&d);
		getInt(&c,&z);
		getInt(&d,&w);
		if((x/y)!=z||(x%y)!=w){
			printf("mismatched.%d\n",i);
			printf("x = %d,y = %d,x / y = %d,x %% y = %d\n",x,y,x/y,x%y);
			printf("a = ");
			dispNumber(&a);
			printf("\nb = ");
			dispNumber(&b);
			printf("\na / b =");
			dispNumber(&c);
			printf("\na %% b =");
			dispNumber(&d);
			printf("%d,%d\n",z,w);
			putchar('\n');
		}
	}
}