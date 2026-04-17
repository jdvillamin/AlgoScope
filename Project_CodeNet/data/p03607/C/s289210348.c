#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define REP(i,n) for(i=0;i<n;i++)

#define MOD 1000000007

//prototype declaration
int i_in();
long long ll_in();
double d_in();
char c_in();
void s_in(char *s);
void i_out(int i);
void ll_out(long long i);
void d_out(double i);
void c_out(char c);
void s_out(char *s);
int gcd(int a, int b);
int lcm(int a, int b);
long long ll_gcd(long long a, long long b);
long long ll_lcm(long long a, long long b);
void sort_asc(int *a);
void sort_desc(int *a);
int asc(const void *a, const void *b);
int desc(const void *a, const void *b);
void ll_sort_asc(long long *a);
void ll_sort_desc(long long *a);
int ll_asc(const void *a, const void *b);
int ll_desc(const void *a, const void *b);
double to_deg(double rad);
double distance(int xi, int yi, int xj, int yj);

//main function
int main() {
    int n = i_in(), i, tmp_count = 0, count = 0;
    long long a[n];
    long long tmp;
    REP(i,n) {
        a[i] = ll_in();
    }
    // ll_sort_asc(a);
    qsort(a, sizeof(a)/sizeof(long long), sizeof(long long), ll_asc);
    /*
    REP(i,n) {
        ll_out(a[i]);
    }
    // */
    REP(i,n) {
        if (tmp != a[i]) {
            tmp = a[i];
            count += (tmp_count % 2);
            tmp_count = 1;
        } else {
            tmp_count++;
        }
    }
    count += (tmp_count % 2);

    i_out(count);

    return 0;
}

//body function
int i_in() {
    int i;
    scanf("%d", &i);
    return i;
}

long long ll_in() {
    long long i;
    scanf("%lld", &i);
    return i;
}

double d_in() {
    double i;
    scanf("%lf", &i);
    return i;
}

char c_in() {
    char c;
    scanf("%c", &c);
    return c;
}

void s_in(char *s) {
    scanf("%s", s);
}

void i_out(int i) {
    printf("%d\n", i);
}

void ll_out(long long i) {
    printf("%lld\n", i);
}

void d_out(double i) {
    printf("%lf\n", i);
}

void c_out(char c) {
    printf("%c\n", c);
}

void s_out(char *s) {
    printf("%s\n", s);
}

/*
    int型の最大公約数
*/

int gcd(int a, int b) {
    int r;

    if (a < b) {
        r = a;
        a = b;
        b = r;
    }

    r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }

    return b;
}

/*
    int型の最小公倍数
*/

int lcm(int a, int b) {
    int r = ll_gcd(a, b);
    a /= r;
    return a * b;
}

/*
    long long型の最大公約数
*/

long long ll_gcd(long long a, long long b) {
    long long r;

    if (a < b) {
        r = a;
        a = b;
        b = r;
    }

    r = a % b;
    while (r != 0) {
        a = b;
        b = r;
        r = a % b;
    }

    return b;
}

/*
    long long型の最小公倍数
*/

long long ll_lcm(long long a, long long b) {
    long long r = ll_gcd(a, b);
    a /= r;
    return a * b;
}

/*
    int型の昇順ソート
*/

void sort_asc(int *a) {
    qsort(a, sizeof(a)/sizeof(int), sizeof(int), asc);
}

/*
    int型の降順ソート
*/

void sort_desc(int *a) {
    qsort(a, sizeof(a)/sizeof(int), sizeof(int), desc);
}

/*
    int型の昇順用比較関数
*/

int asc(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

/*
    int型の降順用比較関数
*/

int desc(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

/*
    long long型の昇順ソート
*/

void ll_sort_asc(long long *a) {
    qsort(a, sizeof(a)/sizeof(long long), sizeof(long long), ll_asc);
}

/*
    long long型の降順ソート
*/

void ll_sort_desc(long long *a) {
    qsort(a, sizeof(a)/sizeof(long long), sizeof(long long), ll_desc);
}

/*
    long long型の昇順用比較関数
*/

int ll_asc(const void *a, const void *b) {
    long long *A = (long long *)a;
    long long *B = (long long *)b;
    if (*A > *B) return 1;
    else if (*A < *B) return -1;
    else return 0;
}

/*
    long long型の降順用比較関数
*/

int ll_desc(const void *a, const void *b) {
    long long *A = (long long *)a;
    long long *B = (long long *)b;
    if (*A < *B) return 1;
    else if (*A > *B) return -1;
    else return 0;
}

/*
    弧度法を度数法に
*/

double to_deg(double rad) {
    return rad * 180.0 / (atan(1.0) * 4.0);
}

/*
    二点間の距離
*/

double distance(int xi, int yi, int xj, int yj) {
    return hypot(xj - xi, yj - yi);
}
