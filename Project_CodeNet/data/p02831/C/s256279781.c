#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
//if(strcmp(s[i],"AC")==0)
//if(s[l]=='#')
/*小文字判定
if((moji>= 'a') && (moji<='z')){
    printf("a\n");
    return 0;
  }
  */

int W_Length(char *str){
	int length = 0;
	while(*str++ != '\0')
		length++;
	return length;
}

void swap(long long int *a, long long int *b){
  int temp;
  temp=*a;
  *a=*b;
  *b=temp;
}
//swap(&a, &b)

double deg(double theta){//deg to theta
return theta*(2*3.14159265359)/360;
}

long long int cmp( const void *p, const void *q ) {
    return *(long long int*)p - *(long long int*)q;
}//ちいさい順
//qsort(a,n,sizeof(long long int),cmp);


int cmp_s(const void * left, const void * right)
{
	char *left_char = (char *)left;
  char *right_char = (char *)right;
  return strcmp(left_char, right_char);
}
//qsort(s,n,sizeof(s[0]),cmp_s);
//char s[n][11]

long long int GCD(long long int a, long long int b){
  long long int L;
  while(1){
    L=a;
    if(b>a){
      L=b;
      b=a;
    }
    if(L%b==0){
      return b;
    }
    a=a%b;
  }
  
}

long long int LCM(long long int a, long long int b){
  return a*b/(GCD(a,b));
}

int main (void)
{
	long long int p[5005],b,c,n,i,k,a[5005]={0},max,j=1,get[5005]={0},temp1,k_temp;
scanf("%lld %lld",&b, &c);

  printf("%lld",LCM(b,c));
return 0;
}
