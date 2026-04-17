#include <stdio.h>

int main (void){
    int n, i, dif = -999999999, minp = 9999999;
    
    scanf("%d", &n);
    
    int r[n];
    
    for(i = 0; i < n; i++){
        scanf("%d", &r[i]);
        if(minp > r[i-1] && i >= 1){ minp = r[i-1]; } 
        
        if(dif < r[i] - minp) dif = r[i] - minp;
    }
    
    printf("%d\n", dif);
    return 0;
    
}