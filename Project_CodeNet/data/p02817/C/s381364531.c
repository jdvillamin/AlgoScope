/*template date:2019/12/27*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<limits.h>
typedef long long int ll;
typedef unsigned long long int ull;
int asc_cmp(const void* X,const void* Y){int x=*(int*)X,y=*(int*)Y;if(x<y)return -1;else if(x==y)return 0;else return 1;}
int desc_cmp(const void* X,const void* Y){int x=*(int*)X,y=*(int*)Y;if(x<y)return 1;else if(x==y)return 0;else return -1;}
int gcd(int x,int y){if(y==0)return x;return gcd(y,x%y);}
double to_deg(double r){return r*180.0/(atan(1.0)*4.0);}
typedef struct{
    int x;
    int y;
}pair_t;
int asc_cmp_t(const void* X,const void* Y){int x=(*(pair_t*)X).x,y=(*(pair_t*)Y).y;if(x<y)return -1;else if(x==y)return 0;else return 1;}
int desc_cmp_t(const void* X,const void* Y){int x=(*(pair_t*)X).x,y=(*(pair_t*)Y).y;if(x<y)return 1;else if(x==y)return 0;else return -1;}

int main(){
    char s[200],t[200];scanf("%s %s",s,t);
    printf("%s%s\n",t,s);
    return 0;
}