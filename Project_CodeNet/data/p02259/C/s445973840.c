#include <stdio.h>

//問題文より、入力されるデータの最大個数
#define MAXCOUNT 100

//ソートの結果と交換回数を出力する関数
void print(int array[], int size, int count);

int main(void)
{
	//i、jは繰り返し変数、countはループの回数を、tempは挿入するデータを格納
	int i, j, count, temp;
	//sizeは配列の要素数を、arrayは入力される数値を格納
	int size;
	int array[MAXCOUNT];

	//データの個数を入力
	scanf("%d", &size);

	//データを入力
	for(i = 0; i < size; i++){
		scanf("%d", &array[i]);
	}

	count = 0;
	//配列の終端の一つ前まで走査
	for(i = 0; i < (size - 1); i++){
		//大きい値から確定していく
		for(j = 0; j < (size - 1 - i); j++){
			//昇順に並び替える
			if(array[j + 1] < array[j]){
				temp = array[j + 1];
				array[j + 1] = array[j];
				array[j] = temp;

				//交換回数を加算する
				count++;
			}
		}
	}

	//結果を出力
	print(array, size, count);

	return 0;
}

void print(int array[], int size, int count)
{
	int i;

	//配列の中身を1行で表示し、最後に改行する
	for(i = 0; i < (size - 1); i++){
		printf("%d ", array[i]);
	}

	printf("%d\n", array[i]);
	//交換回数を表示
	printf("%d\n", count);
}
