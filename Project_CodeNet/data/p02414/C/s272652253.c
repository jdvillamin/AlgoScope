#include<stdio.h>

int main(void){
    int n, m, l, tmp;
    scanf("%d%d%d", &n, &m, &l);
    int a[n][m], b[m][l], c[n][l];
    for(int i=0; i<n; i++) for(int j=0; j<m; j++) scanf("%d", &a[i][j]);
    for(int i=0; i<m; i++) for(int j=0; j<l; j++) scanf("%d", &b[i][j]);
    for(int i=0; i<n; i++) for(int j=0; j<l; j++){
        tmp = 0;
        for(int k=0; k<m; k++) tmp += a[i][k] * b[k][l];
        printf("%d", tmp);
        if(j==l-1) printf("\n");
        else printf(" ");
    }
    return 0;
}

