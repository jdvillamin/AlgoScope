#include<stdio.h>

int search(int A[], int n,int key){
 int i = 0, int c = 0;
 A[n] = key;
 while ( A[i] != key )
       i++;
 
 if( A[i] != n ) 
    c = 1;

 return c;
}

int main(){

 int , c = 0, i, n, A[1000+1], q, key, sum = 0;

 scanf("%d\n", &n);
 for( i = 0; i < n; i++){
   scanf("%d", &key);
   search(A, n, key);
   if(c=1)
     sum++;
 }
 printf("%d\n", sum);

 return 0;
}