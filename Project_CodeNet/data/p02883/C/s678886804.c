long long n, k, i, a[200000], f[200000], top, bottom, med;

int cmp (const void *a, const void *b) {
    return *((long long*)a) - *((long long*)b);
}

int rcmp (const void *a, const void *b) {
    return - (*((long long*)a) - *((long long*)b));
}

int test (long long targetTime) {
    long long sum = 0, i, tmp;
    for (i = 0; i < n; i++) {
        tmp = a[i] - targetTime / f[i];
        if (tmp > 0) sum += tmp;
    }
    return sum > k;
}

int main (void) {
    scanf("%lld %lld", &n, &k);
    for (i = 0; i < n; i++) scanf("%lld", &a[i]);
    for (i = 0; i < n; i++) scanf("%lld", &f[i]);

    qsort(a, n, sizeof(long long), cmp);
    qsort(f, n, sizeof(long long), rcmp);

    /* binary search */
    for (i = 0; i < n; i++) if (a[i] * f[i] > top) top = a[i] * f[i];
    bottom = -1;

    while (top - bottom > 1) {
        med = (top + bottom) / 2;
        if (test(med)) {
            bottom = med;
        } else {
            top = med;
        }
    }

    printf("%d\n", top);
}
