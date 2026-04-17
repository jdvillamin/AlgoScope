#include <stdio.h>

int main(int argc, const char * argv[])
{
	int n, x;
	int i, j, k;
	int result;
	
	while (1) {
		scanf("%d %d", &n, &x);
		if(n == 0 && x == 0) break;
		
		result = 0;
		for(i=1; i<=n; i++){
			for(j=i+1; j<=n; j++){
				for(k=j+1; k<=n; k++){
					if(i+j+k == x){
						result ++;
					}
				}
			}
		}
		printf("%d\n", result);
	}
	
	
	return 0;
}