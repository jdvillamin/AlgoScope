#include <stdio.h>

int main(){

int e,i,j,k,x,y,z,m,min ;


for(;;){
scanf("%d",&e);
if(e==0){
break;
}
min=e;
 
for(j=0;j<=e;j++){
for(k=0;k<=e;k++){

if(e-(j*j+k*k*k)>=0){
x=e-(j*j+k*k*k);
y=j;
z=k;
m=x+y+z;
}
//printf("%d\n",m);

if(m<=min){
min=m;
} 	
}
}
printf("%d\n",min);
}
return 0;
}