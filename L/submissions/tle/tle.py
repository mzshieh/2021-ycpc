#!/usr/bin/python3


def solve(n):
    ans = []

    x = 1
    while x * x * x <= n:
        if n % (x * x + x) == 0:
            ans.append(x)
        x += 1

    if n == 1:
        return ans

    k = 1
    while True:
        m = n // k
        x = int((1 + 4 * m)**0.5) - 1 // 2
        if x**3 < n:
            break
        if n % k == 0 and x * (x + 1) == m:
            ans.append(x)
        k += 1

    return ans


def main():
    t = int(input())
    for cs in range(t):
        n = int(input())
        ans = solve(n)
        ans.sort()
        if len(ans) == 0:
            print(-1)
        else:
            print(*ans)


main()
