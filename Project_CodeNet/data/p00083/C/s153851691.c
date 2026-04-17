#include<stdio.h>
int main(void){
	int age,month,date;
	int flag = 0;
	while(scanf("%d",&age) != EOF){
		scanf("%d %d",&month,&date);
		if(age == 1868){
			if(month == 9){
				if(date < 8){
					flag = 1;
					printf("pre-meiji");
					printf("\n");
					flag = 0;
				}
				else{
					printf("meiji %d",age - 1868 + 1);
				}
			}
			else if(month < 9){
				flag = 1;
				printf("pre-meiji");
				printf("\n");
				flag = 0;
			}
			else{
				printf("meiji %d",age - 1868 + 1);
			}
		}
		else if(age > 1868 && age < 1911){
			printf("meiji %d",age - 1868 + 1);
		}
		else if(age == 1912){
			if(month == 7){
				if(date < 30){
					printf("meiji %d",age - 1868 + 1);
				}
				else{
					printf("taisho %d",age - 1912 + 1);
				}
			}
			else if(month < 7){
				printf("meiji %d",age -1868 + 1);
			}
			else{
				printf("taisho %d",age - 1912 + 1);
			}
		}
		else if(age > 1913 && age < 1925){
			printf("taisho %d",age - 1912 + 1);
		}
		else if( age == 1926){
			if(month == 12){
				if(date < 25){
					printf("taisho %d",age - 1912 + 1);
				}
				else{
					printf("showa %d",age - 1926 + 1);
				}
			}
			else if(month < 12){
				printf("taisho %d",age - 1912 + 1);
			}
			else{
				printf("showa %d",age - 1926 + 1);
			}
		}
		else if(age > 1927 && age < 1988){
			printf("showa %d",age - 1926 + 1);
		}
		else if(age == 1989){
			if(month == 1){
				if(date < 8){
					printf("showa %d",age - 1926 + 1);
				}
				else{
					printf("heisei %d",age - 1989 + 1);
				}
			}
			else if(month < 1){
				printf("showa %d",age - 1926 + 1);
			}
			else{
				printf("heisei %d",age - 1989 + 1);
			}
		}
		else{
			printf("heisei %d",age - 1989 + 1);
		}
		if(flag == 0){
		printf(" %d %d\n",month,date);
			flag = 0;
		}
	}
	return 0;
}