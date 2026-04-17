n= int(input())
a = list(map(int, input().split()))
m = a[0]
j = 0
k = 1
for i in range(1,n):
    if a[i] <= m:
        m = a[i]
        k += 1
        j = i
print(k)