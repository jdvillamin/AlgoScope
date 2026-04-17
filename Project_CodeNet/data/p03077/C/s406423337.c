#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> // uint64_t

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) > (b) ? (b) : (a))

int64_t get_int(void) {
  int64_t num;
  scanf("%lld", &num);
  return num;
}

// <arr[0]> <arr[1]> .. <arr[size-1]>
int fget_array(int64_t *arr, int size) {
    int i;
    for(i = 0; i < size; i++) {
        scanf("%lld", &arr[i]);
    }
    return 0;
}

#define ROADS 5

int main(void) {
    int64_t num = get_int();
    static int64_t arr[ROADS+1];
    fget_array(arr, ROADS);

    int i;
    int64_t rem = num;
    int64_t time = 0;
    for(i = 1; i <= 5; i++) {
        int delay = i;
        int64_t elapse = (rem-1)/arr[i-1] + 1;
        time += elapse;
        int64_t out = (time-delay)*arr[i];
        rem = max(rem-out, 0);
    }

    printf("%lld\n", time);
    return 0;
}