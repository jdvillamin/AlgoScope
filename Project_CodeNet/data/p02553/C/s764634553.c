#include <stdio.h>
#include <stdlib.h>

#define rep(i, n) for (int i = 0; i < n; i = i + 1)
#define array(N, t) (t*)calloc(N, sizeof(t))
#define ll long long
#define INF ((1LL << 62) - (1LL << 31))
#define max(p, q)((p) > (q) ? (p) : (q))
#define min(p, q)((p) < (q) ? (p) : (q))
#define swap(type, a, b) { type temp = a; a = b; b = temp; }

int main() {
  ll a, b, c, d;
  scanf("%lld%lld%lld%lld", &a, &b, &c, &d);

  // printf("max(c, d): %d\n", max(c, d));

  ll ans = 0;

  ll x = max(a, b);
  ll y = max(c, d);
  if (x > 0) {
    if (y > 0) {
    } else {
      x = min(a, b);
    }
  } else {
    if (y > 0) {
      y = min(c, d);
    } else {
      x = min(a, b);
      y = min(c, d);
    }
  }

  ans = x * y;

  printf("%lld\n", ans);

  return 0;
}
