#include<stdio.h>
int main(){
int price,fh,oh,fif,ten,five,one,sum;
while(1){
scanf("%d\n",&price);
sum=0;
if(price==0)break;
price = 1000 - price;
if (price>=500){
fh = price / 500; price -= 500;
}
if(price>=100){
oh = price / 100;
price -= 100;
}
if(price>=50){
fif =  price / 50;
price -= 50;
}
if(price>=10){
ten = price / 10;
price -= 10;
}
if(price>=5){
five = price / 5;
price -= 5;
}
if(price>=1){
one = price / 1;
}
sum = fh+oh+fif+ten+five+one;
printf("%d\n",sum);
}
return 0;
}