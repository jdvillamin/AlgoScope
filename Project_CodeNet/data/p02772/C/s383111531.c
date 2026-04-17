#include<stdio.h>
#include<math.h>
#include <stdlib.h>

int compare_int(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

main()
{
 /*   int a,b,c;
    scanf("%d%d%d",&a,&b,&c);

    if(a==b){
        if(a!=c){
            printf("Yes");
        }
        else{
            printf("No");
        }
    }
    else{
        if(b==c){
            printf("Yes");
        }
        else{
            printf("No");
        }
    }

*/

   // int data[] = {4, 2, 3, 6, 3, 2, 1, 3, 5, 7};
   // int i;

    //when you use sort
    /*qsort(data, 10, sizeof(int), compare_int);
    for (i = 0; i < 10; i++) {
        printf("%3d", data[i]);
    }
    printf("\n");
    */


    int N,i;
    scanf("%d",&N);
    int A[N];
    for(i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    for(i=0;i<N;i++){
        if(A[i]%2 == 0){
            if(A[i]%3 == 0){
                continue;
            }
            else if(A[i]%5 == 0){
                continue;
            }
            else{
                printf("DENIED");
                return 0;
            }
        }
    }
    printf("APPROVED");
}
