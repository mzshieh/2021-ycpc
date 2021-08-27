n = int(input())
ans = 0
l = 0
for i in range(n):
    s = input()
    if l + len(s) > 80:
        ans += 1
        l = 0
    l += len(s) + 1
if l > 0:
    ans += 1
print(ans)
