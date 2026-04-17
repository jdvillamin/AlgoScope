#include <stdio.h>
#include <string.h>

struct dice {
	int N[6];
	char num[5];
};
struct dice DICE = { 1, 2, 3, 4, 5, 6, 4, 3, 0, 2, 1 };

void check_a(int l1, char *str);
void check_b(int l1, char *str);
void rot(char *str);

int main(void) {
	char str[100];
	char v[2][24];
	int i, num;
	scanf("%d%d%d%d%d%d", &DICE.N[0], &DICE.N[1], &DICE.N[2], &DICE.N[3], &DICE.N[4], &DICE.N[5]);
	for (i = 0; i < 6; i++) {							//6面の値の取得
		if (DICE.N[i] < 0) { DICE.N[i] = 0; }			//0以下の場合は0とする
		if (DICE.N[i] > 100) { DICE.N[i] = 100; }		//100以上の場合は100とする
	}
	getchar();											//改行の読み飛ばし
	scanf("%d", &num);									//質問数の取得
	if (num < 1) { num = 1; }							//質問数の下限値は1
	if (num > 24) { num = 24; }							//質問数の上限値は24
	getchar();											//改行の読み飛ばし
	for (i = 0; i < num; i++) {
//		scanf("%d%d", &v[0][i], &v[1][i]);				//上面と前面の値の取得
//		getchar();										//改行の読み飛ばし
	}
	for (i = 0; i < num; i++) {

		scanf("%d%d", &v[0][i], &v[1][i]);				//上面と前面の値の取得
		getchar();										//改行の読み飛ばし

		check_a(v[0][i], str);							//上面の位置取得
		rot(str);										//
		check_b(v[1][i], str);							//前面の位置取得
		rot(str);										//
		printf("%d\n", DICE.N[DICE.num[3]]);			//右面の値
	}
	return 0;
}
void check_a(int l1, char *str) {
	int i, j = 0, k = 5;
	for (i = 0; i < 6; i++) {							//求めたい値が何番目に格納されているか調べる
		if (l1 == DICE.N[i]) {
			j = i;
			break;
		}
	}
	for (i = 0; i < 5; i++) {							//上で一致した番号がダイスのどの位置にあるか調べる
		if (j == DICE.num[i]) {
			k = i;
			break;
		}
	}
	switch (k) {
	case 0:
		strcpy(str, "");
		break;
	case 1:
		strcpy(str, "EN");
		break;
	case 2:
		strcpy(str, "N");
		break;
	case 3:
		strcpy(str, "WN");
		break;
	case 4:
		strcpy(str, "NN");
		break;
	default:
		strcpy(str, "S");
		break;
	}
}
void check_b(int l1, char *str) {
	int i, j = 0, k = 5;
	for (i = 0; i < 6; i++) {							//求めたい値が何番目に格納されているか調べる
		if (l1 == DICE.N[i]) {
			j = i;
			break;
		}
	}
	for (i = 0; i < 5; i++) {							//上で一致した番号がダイスのどの位置にあるか調べる
		if (j == DICE.num[i]) {
			k = i;
			break;
		}
	}
	switch (k) {
	case 0:
		strcpy(str, "");
		break;
	case 1:
		strcpy(str, "E");
		break;
	case 2:
		strcpy(str, "");
		break;
	case 3:
		strcpy(str, "W");
		break;
	case 4:
		strcpy(str, "");
		break;
	default:
		strcpy(str, "EE");
		break;
	}
}
void rot(char *str) {
	int i = 0;
	while (str[i] != '\0') {
		switch (str[i]) {
		case 'N':
			DICE.num[0] = DICE.num[2];
			DICE.num[2] = DICE.num[4];
			DICE.num[4] = 5 - DICE.num[0];
			break;
		case 'S':
			DICE.num[4] = DICE.num[2];
			DICE.num[2] = DICE.num[0];
			DICE.num[0] = 5 - DICE.num[4];
			break;
		case 'E':
			DICE.num[3] = DICE.num[2];
			DICE.num[2] = DICE.num[1];
			DICE.num[1] = 5 - DICE.num[3];
			break;
		case 'W':
			DICE.num[1] = DICE.num[2];
			DICE.num[2] = DICE.num[3];
			DICE.num[3] = 5 - DICE.num[1];
			break;
		default:
			break;
		}
		i++;
	}
}
