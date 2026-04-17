#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define PIE atan(1.0)*4

typedef struct nd{
	int id;
	//
	int x, y;
	int r;
	int v;
	//
	double polar_r;
	double polar_t;
	//
	int state;	// 0:接近中，1:撃破, 2:到達
	struct nd *next;
	struct nd *prev;
	bool dummy;
} node;

void initList(node **top, int num) {
	int i;
	// 極座標変換
	for (i = 0; i < num; i++) {
		top[i]->polar_r = sqrt((double)(top[i]->x*top[i]->x + top[i]->y*top[i]->y));
		top[i]->polar_t = acos((double)top[i]->x / top[i]->polar_r);
		if (top[i]->y < 0)
			top[i]->polar_t = 2*PIE-top[i]->polar_t;
		top[i]->prev = i!=0 ? top[i - 1] : NULL;
		top[i]->next = i!=num-1 ? top[i + 1] : NULL;
		top[i]->dummy = false;
	}
}

node *removeNode(node *target) {
	node *next = target->next;
	target->next->prev = target->prev;
	target->prev->next = target->next;
	free(target);
	return next;
}

void removeNodes(node *begin) {
	node *temp = begin->next;
	while (temp->next != NULL) {
		if (temp->state != 0)
			temp = removeNode(temp);
		else
			temp = temp->next;
	}
}

int main(int argc, char* argv[]) {

	int invaridR, ufoNum;

	int i;
	node *temp;

	while (true) {
		// データ読み込み
		scanf("%d %d", &invaridR, &ufoNum);
		if (invaridR == 0 && ufoNum == 0) break;
		node **ufos = (node**)malloc(sizeof(node*)*ufoNum);
		for (i = 0; i < ufoNum; i++) {
			ufos[i] = (node*)malloc(sizeof(node));
			ufos[i]->id = i;
			scanf("%d %d %d %d", &(ufos[i]->x), &(ufos[i]->y), &(ufos[i]->r), &(ufos[i]->v));
			ufos[i]->next = ufos[i]->prev = NULL;
			ufos[i]->state = 0;
		}
		initList(ufos, ufoNum);
		node *begin = (node*)malloc(sizeof(node));
		begin->dummy = true;
		begin->id = -1;
		begin->prev = NULL;
		begin->next = ufos[0];
		ufos[0]->prev = begin;
		node *end = (node*)malloc(sizeof(node));
		end->dummy = true;
		end->id = -2;
		end->next = NULL;
		end->prev = ufos[ufoNum - 1];
		ufos[ufoNum - 1]->next = end;

		// 計算
		int t = 0;
		int count = 0;
		while (begin->next != end) {
			// 位置＆時刻更新
			t++;
			for (i = 0; i < ufoNum; i++) {
				ufos[i]->polar_r -= ufos[i]->v;
			}
			// 照射方向決定
			double minR = 1500;
			double fireT = 0;
			for (temp = begin->next; temp != end; temp = temp->next) {
				if (temp->polar_r < minR && temp->polar_r>invaridR) {
					minR = temp->polar_r;
					fireT = temp->polar_t;
				}
			}
			// 照射
			for (temp = begin->next; temp != end; temp = temp->next) {
				double dt = fireT - temp->polar_t;
				if (dt > 2 * PIE) dt -= 2 * PIE;
				if (dt < 0) dt += 2 * PIE;
				if (temp->polar_r < invaridR) {
					// 到達
					temp->state = 2;
					count++;
				}
				else if (fabs(temp->polar_r*sin(dt)) < temp->r){
					// 撃破
					temp->state = 1;
				}
			}
			// 不要ufo削除
			removeNodes(begin);
		}

		fprintf(stdout, "%d\n", count);
	}

	return 0;
}