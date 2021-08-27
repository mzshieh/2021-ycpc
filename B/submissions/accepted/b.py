n,c=input().split()
n = int(n)
c = int(c)
mod = 10**9 + 7
print(c * pow(c - 1, n - 1, mod) % mod)
