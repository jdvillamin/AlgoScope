#include <stdio.h>

#define MAX (1000)

int sqr_size;
int ans;

int main(void)
{
	char sqr[MAX][MAX];
	int i;
	int j;
	
	while (1){
		ans = 0;
		scanf("%d", &sqr_size);
		if (sqr_size == 0){
			break;
		}
		for (i = 0; i < sqr_size; i++){
			char str[MAX + 1];
			scanf("%s", str);
			for (j = 0; j < sqr_size; j++){
				sqr[j][i] = str[j];
			}
		}
		for (i = 0; i < sqr_size; i++){
			j = 0;
			while (j < sqr_size){
				int k, l, m;
				int size;
				
				if (sqr[j][i] == '*'){
					j++;
					continue;
				}
				
				k = 1;
				while ((i + k < sqr_size) && (sqr[j][i + k] == '.') && (j + k < sqr_size) && (sqr[j + k][i] == '.') ){
					k++;
				}
				size = k;
				if (size > ans){
					for (m = size - 1; m > ans; m--){
						for (k = 0; k < m; k++){
							for (l = 0; l < m; l++){
								if (sqr[j + l][i + k] != '.'){
									break;
								}
							}
						}
						if (k == m && l == m){
							ans = m;
							break;
						}
					}
				}
				j += size;
			}
		}
		
		printf("%d\n", ans);
	}
	return (0);
}