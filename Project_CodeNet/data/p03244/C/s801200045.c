#include <stdio.h>
int main(void){
	
int n;
int num[10001]={};
int a=0,b=0;
int i;


scanf("%d",&n);

for(i=0;i<n;i++)
scanf("%d",&num[i]);

for(i=0;i<n-2;i++){
if(num[i]!=num[i+2])
a++;
if(num[i]==num[i+1])
b++;
}
if(num[n-2]==num[n-1]&&b==n-2)
printf("%d\n",n/2);
else
printf("%d\n",a);


return 0;
}