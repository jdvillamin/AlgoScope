/* Source: https://www.geeksforgeeks.org/dsa/print-n-to-1-without-loop/ */
#include <stdio.h>

void printNos(int n){
    
    // base case
    if (n == 0)
        return;
   
    printf("%d ", n);
    
    // recursive call
    printNos(n - 1);
}

int main(){
    int n = 3;
    
    printNos(n);
    
    return 0;
}
