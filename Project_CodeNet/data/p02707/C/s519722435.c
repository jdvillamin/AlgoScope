#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n,a[500000]={},i,sum[500000]={};
    char token[10000000]={};
    fgets(token, sizeof(token), stdin);
    n=atoi(token);
    fgets(token, sizeof(token), stdin);
    a[0]=atoi(strtok(token, " "));
    for (i=1; i<n-1; i++) a[i]=atoi(strtok(NULL, " "));
    for (i=0; i<n-1; i++) sum[a[i]]++;
    for (i=1; i<=n; i++) printf("%d\n",sum[i]);
    return 0;
}

