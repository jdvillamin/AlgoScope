#include <stdio.h>

int main(void){
    int n;
    int l[100];
    int count = 0;

    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &l[i]);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(l[j] > l[i]){
                int temp = l[j];
                l[j] = l[i];
                l[i] = temp;
            }
        }
    }

    for(int i = 0; i < n - 2; i++){
        for(int j = i + 1; j < n - 1; j++){
            for(int k = j + 1; k < n; k++){
                if(l[k] < (l[i] + l[j]) && l[i] != l[k] && l[k] != l[j] && l[i] != l[j]){
                    count++;
                }
            }
        }
    }

    printf("%d", count);

    return 0;
}