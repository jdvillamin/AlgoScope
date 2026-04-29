/* Source: https://www.geeksforgeeks.org/dsa/program-to-print-multiplication-table-of-a-number/ */
#include <stdio.h>

void printTable(int n) { 
    for (int i = 1; i <= 10; ++i) 
        printf("%d * %d = %d\n", n, i, n * i);
}

int main() {
    int n = 5;  
    printTable(n);
    return 0;
}
