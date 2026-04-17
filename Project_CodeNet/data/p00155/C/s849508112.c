#include <stdio.h>          // printf(), scanf()
#include <math.h>           // sqrt()
#include <stdbool.h>

#define MAX_V 100

const int INF = 1000000000;
int V;
double cost[MAX_V][MAX_V];
double d[MAX_V];
int prev[MAX_V];

void
dijkstra(int s)
{
	bool used[MAX_V];

	for (int i = 0; i < V; ++i)
	{
		d[i] = INF;
		used[i] = false;
		prev[i] = -1;
	}

	d[s] = 0.0;
	while (true)
	{
		int v = -1;
		for (int u = 0; u < V; ++u)
		{
			if (!used[u] && (v == -1 || d[u] < d[v]))
				v = u;
		}

		if (v == -1)
			break;

		used[v] = true;
		for (int u = 0; u < V; ++u)
		{
			if (d[v] + cost[v][u] < d[u])
			{
				d[u] = d[v] + cost[v][u];
				prev[u] = v;
			}
		}
	}
}

void
solve(int s, int g)
{
	int path[MAX_V];

	dijkstra(s);
	if (d[g] == INF)
		printf("NA\n");
	else
	{
		int ix = 0;
		for (; g != -1; g = prev[g])
			path[ix++] = g;

		for (int i = ix - 1; i >= 0; --i)
			printf("%d%c", path[i] + 1, (i != 0) ? ' ' : '\n');
	}
}

int
main(int argc, char **argv)
{
	int x[MAX_V], y[MAX_V];

	while (true)
	{
		scanf("%d", &V);
		if (V == 0)
			break;

		for (int i = 0; i < V; ++i)
		{
			int b;
			int tx, ty;
			scanf("%d%d%d", &b, &tx, &ty);
			b--;
			x[b] = tx, y[b] = ty;
		}

		for (int i = 0; i < V; ++i)
		{
			for (int j = 0; j < V; ++j)
				cost[i][j] = (i == j) ? 0 : INF;
		}

		for (int i = 0; i < V; ++i)
		{
			for (int j = i + 1; j < V; ++j)
			{
				if (i != j)
				{
					int rx = x[i] - x[j], ry = y[i] - y[j];
					double r = sqrt(rx * rx + ry * ry);
					if (r <= 50.0)
					{
						cost[i][j] = r;
						cost[j][i] = r;
					}
				}
			}
		}

		int m;
		scanf("%d", &m);
		for (int i = 0; i < m; ++i)
		{
			int s, g;
			scanf("%d%d", &s, &g);
			s--, g--;
			solve(s, g);
		}
	}

	return 0;
}
