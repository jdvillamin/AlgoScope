#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int dx[4] = { 1, 0, -1, 0 };
const int dy[4] = { 0, 1, 0, -1 };

int main() {
	int H, W;
	cin >> H >> W;

	int CH, CW, DH, DW;
	cin >> CH >> CW >> DH >> DW;

	vector<string> field(H);
	for (int h = 0; h < H; ++h) {
		cin >> field[h];
	}

	int sx = CH - 1;
	int sy = CW - 1;

	int cnt = 0;

	queue<pair<int, int>> startP;
	startP.push(make_pair(sx, sy));

	vector<vector<int>> dist(H, vector<int>(W, -1));

	while (!startP.empty()) {
		pair<int, int> startPoint = startP.front();
		int sx = startPoint.first;
		int sy = startPoint.second;
		startP.pop();

		if (dist[sx][sy] != -1) {
			continue;
		}

		if (sx + 1 == DH && sy + 1 == DW) {
			cout << cnt << endl;
			return 0;
		}

		dist[sx][sy] = cnt;

		queue<pair<int, int>> que;
		que.push(make_pair(sx, sy));

		while (!que.empty()) {
			pair<int, int> current_pos = que.front();
			int x = current_pos.first;
			int y = current_pos.second;
			que.pop();

			for (int direction = 0; direction < 4; ++direction) {
				int next_x = x + dx[direction];
				int next_y = y + dy[direction];
				if (next_x < 0 || next_x >= H || next_y < 0 || next_y >= W) {
					continue;
				}
				if (field[next_x][next_y] == '#') {
					continue;
				}

				if (next_x + 1 == DH && next_y + 1 == DW) {
					cout << cnt << endl;
					return 0;
				}

				if (dist[next_x][next_y] == -1) {
					que.push(make_pair(next_x, next_y));
					dist[next_x][next_y] = cnt;
				}
			}
		}

		for (int h = 0; h < H; ++h) {
			for (int w = 0; w < W; ++w) {
				if (dist[h][w] == cnt) {
					for (int i = -2; i <= 2; ++i) {
						for (int j = -2; j <= 2; ++j) {
							int check_x = h + i;
							int check_y = w + j;

							if (check_x < 0 || check_x >= H || check_y < 0 || check_y >= W) {
								continue;
							}
							if (field[check_x][check_y] == '#') {
								continue;
							}
							if (dist[check_x][check_y] != -1) {
								continue;
							}

							startP.push(make_pair(check_x, check_y));
						}
					}
				}
			}
		}

		cnt++;
	}

	cout << "-1" << endl;
	return 0;
}
