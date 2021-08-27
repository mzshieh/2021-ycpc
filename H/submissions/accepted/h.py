def solve(a, width):
    n = len(a)
    ans = 0
    l = 0
    for i in range(n):
        if l + a[i] > width:
            ans += 1
            l = 0
        l += a[i] + 1
    if l > 0:
        ans += 1
    return ans


n = int(input())
ans = 0
l = 0
a = []
for i in range(n):
    s = input()
    a.append(len(s))

l, r = min(a), 100000
while l != r:
    mid = (l + r) // 2
    if solve(a, mid) <= 24:
        r = mid
    else:
        l = mid + 1
print(r)
