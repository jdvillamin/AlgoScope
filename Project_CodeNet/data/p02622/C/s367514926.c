#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define BUFSIZE 1000000

int x,n,m;

char p[BUFSIZE];

int cnt = 0 ;

/*
int compare_int(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}
*/
int a;
char s[BUFSIZE];
char t[BUFSIZE];
int main(void){
  scanf("%s",s);
  scanf("%s",t);
  for(int i = 0 ;i < strlen(s);i++){
    if(s[i] != t[i]) cnt++;
  }

/*
  for(int i = 0;i < ;i++){
    scanf("%",);

  }
/*  qsort(a, n, sizeof(int), compare_int);
*/
/*
for(int i = 0;i < ;i++){


}
*/
printf("%d",cnt);
return 0;

}
