#include <stdio.h>

int main(void)
{
	int flag=1, buf, i=1;
	while(flag == 1){
		scanf("%d", &buf);

		if(buf != 0){
			printf("Case %d: %d\n", i, buf);
			i++;
		}else{
			flag = 0;
		}
	}

	return 0;
}