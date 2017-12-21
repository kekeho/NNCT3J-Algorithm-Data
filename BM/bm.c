#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHARNUM 95

//文字列のカウント関数。文字列が与えられなかった場合は-1を返す。

void makeSkipTable(char const str[], int table[]){
  int strCnt;
  //文字列カウント
  if (str != NULL) {
    strCnt = strlen(str);
  } else {
    exit(-1);
  }

  //初期化
  for (int i = 0; i < CHARNUM; i++) {
    table[i] = strCnt;
  }

  for (int i = 0; i < strCnt-1; i++) {
    table[str[i] - 0x20] = strCnt - (i+1);
  }
}

void displayTable(int table[]) {
  int rtn = 1;
  for (int i = 0; i < CHARNUM; i++) {
    printf("%c(%d)\t", 0x20+i, table[i]);
    if (rtn == 8) {
      putchar('\n');
      rtn = 0;
    }
    rtn++;
  }
  putchar('\n');
}

int bmSearch(char const text[], char const pattern[], int const table[]){
	int textLen = strlen(text);
	int patternLen = strlen(pattern);
  int i, j;

  //エラー処理
  if (textLen < patternLen) {
    printf("ERROR: 検索文字列が被検索文字列より長いです。検索中止。\n");
    exit(-1);
  }
  //不明な文字コードは排除
  for (i = 0; i < textLen; i++) {
    if (text[i] < 0x20 || text[i] > 0x7e) {
      printf("ERROR: 被検索文字列に扱えない文字コードが含まれています。検索中止。\n");
      exit(-1);
    }
  }
  for (i = 0; i < patternLen; i++) {
    if (pattern[i] < 0x20 || pattern[i] > 0x7e) {
      printf("ERROR: 検索文字列に扱えない文字コードが含まれています。検索中止。\n");
      exit(-1);
    }
  }

  //検索
	i = patternLen - 1;
	while(i < textLen){
		for (j = 0; j < patternLen; j++){
			if (text[i - j] != pattern[patternLen - 1 - j]){
				int flag = 0;
				int k;
				int place;

				for (k = 0; k < patternLen; k++){
					if (text[i - j] == pattern[patternLen - 1 -k]){
						place = (i - (patternLen -1)) + table[pattern[patternLen - 1 -k] - 0x20];
						flag = 1;
					}
				}

				if (flag != 1){
					place = (i - (patternLen -1)) + table[text[i-j] - 0x20];
				}

				if (place <= i)
					i++;
				else
					i = place;

				break;
			}

			if (j == patternLen - 1){
				return i - (patternLen - 1);
			}
		}
	}

	return -1;
}

int powerSearch(char const text[], char const pattern[]){
  int flag = 0;
  int textLen = strlen(text);
  int patternLen = strlen(pattern);

  for (int i = 0; i < textLen; i++) {
    for (int j = 0; j < patternLen; j++) {
      if (text[i+j] == pattern[j]){
        flag++;
      } else {
        flag--;
      }
    }
    if(flag == patternLen){
      return i;
    } else {
      flag = 0;
    }
  }
  return -1;
}

int main(int argc, char const *argv[]) {
  if (argc == 4 && argv[3][1] == 'p') {
    printf("OPTION: 力任せ法で検索します...\n");
    int result = powerSearch(argv[1], argv[2]);
    if (result == -1) {
      printf("ERROR: \"%s\"は含まれていません\n", argv[2]);
    } else{
      printf("検索結果: %d文字目\n", result);
    }
    return 0;
  } else if (argc == 3) {
    int skipTable[CHARNUM];
    makeSkipTable(argv[2], skipTable);
    printf("=====SKIP TABLE=====\n");
    displayTable(skipTable);

    int result = bmSearch(argv[1], argv[2], skipTable);
    if (result == -1) {
      printf("ERROR: \"%s\"は含まれていません\n", argv[2]);
    } else{
      printf("検索結果: %d文字目\n", result);
    }
    return 0;
  } else if (argc == 2 && argv[1][1] == 'h'){
    //help
    printf("HELP\n$ Usage:\n\tj15316.c 被検索文字列 検索キーワード [option]\n");

  } else {
    printf("引数を正しく指定してください\n$ Usage:\n\tj15316.c 被検索文字列 検索キーワード [option]\n");
  }
}
