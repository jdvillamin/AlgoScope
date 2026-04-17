#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
  int i=1,j=1,x[100],ans=0,y[100];
  char s[100];

  while( scanf("%s", s) != EOF ){
    if ( s[0] == '+' ){
      if(i==1)ans=y[i-1]+y[i];
      else {
        y[j]=x[i-1]+x[i];
        i=1;
        j++;
      }
    } 
    else if ( s[0] == '-' ){
      if(i==1)ans=y[i-1]-y[i];
      else {
        y[j]=x[i-1]-x[i];
        i=1;
        j++;
      }
    } 
    else if ( s[0] == '*' ){
      if(i==1)ans=y[i-1]*y[i];
      else {
        y[j]=x[i-1]*x[i];
        i=1;
        j++; 
      }
    } 
    else {
      x[i] = atoi(s);
      i++;
    }
  }
  printf("%d\n",ans);