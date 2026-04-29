/* Source: https://www.geeksforgeeks.org/dsa/print-1-to-n-without-using-loops/ */
#include <stdio.h>

void printNos(int n){
    
    // base condition
    if (n == 0)
        return;
        
    // recursive call
    printNos(n - 1);
    printf("%d ", n);
}

int main(){
    int n = 3;
    printNos(n);
    return 0;
}
