#include <stdio.h>
int main(){
    int n, k;
    int sum, tmp;

    sum = 0;

    scanf("%d", &n);
    scanf("%d", &k);

    int  p[n];

    for(int i=0; i<n; i++){
        scanf("%d", &p[i]);
    }

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(p[i] > p[j]){
                tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }  
   

    for(int j=0; j<k; j++){
        sum = sum + p[j];
    }

    printf("%d\n", sum);
    

    return 0;

}