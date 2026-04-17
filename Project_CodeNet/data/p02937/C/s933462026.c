#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 内部定数
#define D_ARRAY_MAX		100005									// 最大配列数
#define D_CHAR_CNT		26										// 文字種類数

// 内部変数
static FILE *szpFpI;											// 入力
static char sc1Str[D_ARRAY_MAX];								// 文字列
static int si2Pos[D_CHAR_CNT][D_ARRAY_MAX];						// 位置
static int si1PCnt[D_CHAR_CNT];									// 位置数

// 内部変数 - テスト用
#ifdef D_TEST
	static int siRes;
	static FILE *szpFpA;
	static int siTNo;
#endif

// 出力
int
fOut(
	char *pcpLine				// <I> １行
)
{
	char lc1Buf[1024];

#ifdef D_TEST
	fgets(lc1Buf, sizeof(lc1Buf), szpFpA);
	if (strcmp(lc1Buf, pcpLine)) {
		siRes = -1;
	}
#else
	printf("%s", pcpLine);
#endif

	return 0;
}

// 検索
// 戻り値：[>=0]配列番号 [-1]なし
int
fBSrhPN(
	int piVal					// <I> 値
	, int *pipArray				// <I> 配列
	, int piACnt				// <I> 配列数
)
{
	// 初期範囲
	int liSNo = 0;
	int liENo = piACnt - 1;

	// 検索
	while (1) {

		// 中間位置
		int liMNo = (liSNo + liENo) / 2;

		// 一致チェック
		if (piVal == pipArray[liMNo]) {
			return liMNo;
		}

		// 範囲を絞る
		if (piVal < pipArray[liMNo]) {				// 左側へ
			if (liSNo < liMNo) {						// 範囲あり
				liENo = liMNo - 1;
			}
			else {										// 範囲なし
				return liMNo;
			}
		}
		else {										// 右側へ
			if (liENo > liMNo) {						// 範囲あり
				liSNo = liMNo + 1;
			}
			else {										// 範囲なし
				return liMNo + 1;
			}
		}
	}

	return -1;
}

// 実行メイン
long long
fMain(
)
{
	int i;

	// 文字列s - 取得
	fgets(sc1Str, sizeof(sc1Str), szpFpI);

	// 位置 - 取得
	int liCNo, liLen;
	for (i = 0; ; i++) {
		liCNo = sc1Str[i] - 'a';
		if (liCNo < 0 || D_CHAR_CNT <= liCNo) {
			break;
		}

		// 位置 - セット
		si2Pos[liCNo][si1PCnt[liCNo]] = i;
		si1PCnt[liCNo]++;
	}
	liLen = i;

	// 文字列t - 取得
	fgets(sc1Str, sizeof(sc1Str), szpFpI);

	// 文字数 - 取得
	int liRep = 0;
	int liNow = -1;
	for (i = 0; ; i++) {
		liCNo = sc1Str[i] - 'a';
		if (liCNo < 0 || D_CHAR_CNT <= liCNo) {
			break;
		}

		// 文字有無
		if (si1PCnt[liCNo] < 1) {
			return -1;
		}

		// 文字検索
		int liPos;
		liPos = fBSrhPN(liNow + 1, si2Pos[liCNo], si1PCnt[liCNo]);
		if (liPos < si1PCnt[liCNo]) {
			liNow = si2Pos[liCNo][liPos];
		}
		else {
			liRep++;
			liNow = si2Pos[liCNo][0];
		}
	}

	return (long long)liLen * (long long)liRep + (long long)liNow + 1;
}

// １回実行
int
fOne(
)
{
	long long llRet;
	char lc1Buf[1024];

	// データ - 初期化
	memset(si1PCnt, 0, sizeof(si1PCnt));						// 位置数

	// 入力 - セット
#ifdef D_TEST
	sprintf(lc1Buf, ".\\Test\\T%d.txt", siTNo);
	szpFpI = fopen(lc1Buf, "r");
	sprintf(lc1Buf, ".\\Test\\A%d.txt", siTNo);
	szpFpA = fopen(lc1Buf, "r");
	siRes = 0;
#else
	szpFpI = stdin;
#endif

	// 実行メイン
	llRet = fMain();

	// 出力
	sprintf(lc1Buf, "%lld\n", llRet);
	fOut(lc1Buf);

	// 残データ有無
#ifdef D_TEST
	lc1Buf[0] = '\0';
	fgets(lc1Buf, sizeof(lc1Buf), szpFpA);
	if (strcmp(lc1Buf, "")) {
		siRes = -1;
	}
#endif

	// テストファイルクローズ
#ifdef D_TEST
	fclose(szpFpI);
	fclose(szpFpA);
#endif

	// テスト結果
#ifdef D_TEST
	if (siRes == 0) {
		printf("OK %d\n", siTNo);
	}
	else {
		printf("NG %d\n", siTNo);
	}
#endif

	return 0;
}

// プログラム開始
int
main()
{

#ifdef D_TEST
	int i;
	for (i = D_TEST_SNO; i <= D_TEST_ENO; i++) {
		siTNo = i;
		fOne();
	}
#else
	fOne();
#endif

	return 0;
}

