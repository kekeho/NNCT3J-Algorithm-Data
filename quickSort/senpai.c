/****************************************************************************************************************/
/*																												*/
/*	出席番号: 25番																								*/
/*  名前	: 佐々木 浩幸																					    */
/*																												*/
/*	課題内容:																								    */
/*	0以上100未満の数値30個をランダムに決め、これをクイックソートによりソートして出力するプログラムを作成する。	*/
/*  ピボットの値と、数値がきちんとパーティション分割されている様子を表示し、ソートの途中経過が分かるようにする。*/
/*	途中経過の表示とソートがきちんとできることで「正常動作」と見なす。											*/
/*																												*/
/****************************************************************************************************************/

/**************************************/
/*									  */
/*	オプション						　*/
/*									  */
/*	-u 昇順にソートする				  */
/*	-d 降順にソートする				  */
/*	-o 比較回数 交換回数を表示する	  */
/*									  */
/**************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// フラグ管理用定数
#define OPTION_UPSORT 1
#define OPTION_DOWNSORT 2
#define OPTION_SHOW_PROCESS_NUM 4

// ソートするデータの数(配列の長さ)
#define Array_Length 5

unsigned int optionFlag = 0; // オプション機能を管理するフラグ 

unsigned int swapCount = 0; // 交換回数を記録する変数
unsigned int cmpCount = 0; // 比較回数を記録する変数

void QuickSort(int[], int , int);

void Swap(int*, int*);
void ShowArray(int[], int, int);
int GetPivot(int[], int, int);

int main(int argc, char* argv[])
{
	int i; // for文用変数

	// 乱数を使ってソートするデータを生成する
	srand((unsigned)time(NULL));

	int sortArray[Array_Length];

	for (i = 0; i < Array_Length; i++)
	{
		sortArray[i] = rand() % 100;
	}

	if (argc > 1) // コマンドライン引数にオプションが指定されているか調べる
	{	
		// オプションを読み取って各フラグを立てる
		for (i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-u") == 0)
			{
				if ((optionFlag & OPTION_DOWNSORT) == OPTION_DOWNSORT)	// 既に降順を指定してないか調べる
				{
					printf("Error: Don't specify \"-u\" and \"-d\" at the same time\n ");
					return 0;
				}
				else
				{
					optionFlag += optionFlag | OPTION_UPSORT;	// 昇順ソートフラグを立てる
				}
			}
			else if (strcmp(argv[i], "-d") == 0 )
			{
				if ((optionFlag & OPTION_UPSORT) == OPTION_UPSORT)	// 既に昇順を指定してないか調べる
				{
					printf("Error: Don't specify \"-u\" and \"-d\" at the same time\n ");
					return 0;
				}
				else
				{
					optionFlag = optionFlag | OPTION_DOWNSORT;	// 降順ソートフラグを立てる
				}
			}
			else if (strcmp(argv[i], "-o") == 0)
			{
				optionFlag =  optionFlag | OPTION_SHOW_PROCESS_NUM;
			}
			else
			{
				// 指定したオプションが正しくなければ エラーを出して終了
				printf("Error: Not option \"%s\"\n", argv[i]);
				return 0;
			}
		}

		printf("Contents of the array to be sorted\n");
		ShowArray(sortArray, 0, Array_Length - 1);
		printf("\n\n");

		if ((optionFlag & OPTION_UPSORT) == OPTION_UPSORT)
		{
			QuickSort(sortArray, 0, Array_Length - 1);
		}
		else if ((optionFlag & OPTION_DOWNSORT) == OPTION_DOWNSORT)
		{
			QuickSort(sortArray, 0, Array_Length - 1);

			int loopMax = (Array_Length)  / 2;
			// 降順に並び替える
			for (i = 0; i < loopMax; i++)
			{
				Swap(&sortArray[i], &sortArray[Array_Length - 1 - i]);
			}
		}
		else // 昇順,降順が指定されてなかったらエラーを返す
		{
			printf("Please select ascending or descending order");
			return 0;
		}

		printf("\nResult\n");

		// 比較回数と交換回数を表示するフラグが立っていたら表示する
		if ((optionFlag & OPTION_SHOW_PROCESS_NUM) == OPTION_SHOW_PROCESS_NUM)
		{
			printf("The Number of compairisons:%d\nThe Number of a swap: %d\n", cmpCount, swapCount);
		}

		ShowArray(sortArray, 0, Array_Length - 1);
		printf("\n");
	}
	else // オプションの指定が無ければ昇順にソートして結果を表示する
	{		
		printf("Contents of the array to be sorted\n");
		ShowArray(sortArray, 0, Array_Length - 1);
		printf("\n\n");
		QuickSort(sortArray, 0, Array_Length - 1);
		printf("\nResult\n");
		ShowArray(sortArray, 0, Array_Length - 1);
		printf("\n");	
	}

	return 0;
}

// 昇順にクイックソートをする関数
void QuickSort(int array[], int start, int end)
{
	if (start != end && start < end)
	{
		int pivot;

		pivot = GetPivot(array, start, end);

		int left = start;
		int right = end;

		while (1)
		{
			while (left <= end)
			{
				if (array[left] >= pivot)
				{
					cmpCount++;
					break;					
				}
				cmpCount++;
				left++;
			}

			while (right >= start)
			{
				if (array[right] < pivot)
				{
					cmpCount++;
					break;
				}
				cmpCount++;
				right--;
			}

			if (left == right + 1)
			{
				if (right < start)
				{
					right = start;
					left = start + 1;

					if (array[start] > array[end])
					{
						Swap(&array[start], &array[end]);
					}
					cmpCount++;
				}
				cmpCount+=2;

				break;
			}
			else
			{
				Swap(&array[left], &array[right]);
				cmpCount++;
			}
		}

		// ******* バーティション分割の結果を表示 ******* //
		printf("pivot: %d\n",pivot);
		ShowArray(array, start, right);
		ShowArray(array, left, end);
		printf("\n\n");

		// ******* 再帰的にクイックソートをかける ******* //
		QuickSort(array, start, right );
		QuickSort(array, left, end);		
	}
	else
	{
		printf("pivot: %d\n [ %d ]\n\n", array[start], array[start]);
	}
}

// 二つの値を交換する関数
void Swap(int* num1, int* num2)
{
	if (*num1 != *num2)
	{
		*num1 ^= *num2;
		*num2 ^= *num1;
		*num1 ^= *num2;
	}

	swapCount++;
}

// 配列の指定した範囲の要素を[]に囲って表示する関数
void ShowArray(int array[], int start, int end)
{
	int i;

	printf("[ ");

	for (i = start; i < end + 1; i++)
	{
		printf("%d ", array[i]);
	}

	printf("]");
}

// ピボットを取得する関数
int GetPivot(int array[], int start, int end)
{
	int center = (end - start) / 2 + start;

	if (array[start] >= array[center] && array[end] >= array[center])
		{
			if(array[start] >= array[end])
			{
				cmpCount += 3;
				return array[end];
			}
			else
			{
				cmpCount += 3;
				return array[start];
			}
		}
		else if (array[start] <= array[center] && array[end] <= array[center])
		{
			if (array[start] <= array[end])
			{
				cmpCount += 3;
				return array[end];
			}
			else
			{
				cmpCount += 3;
				return array[start];
			}
		}

		cmpCount += 4;
		return array[center];
}
