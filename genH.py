from random import randint as ri
from random import shuffle

def gen(name, n, m, d):
    with open(name,'w') as FILE:
        print(n, m, d, file=FILE)
        vec = [25]+[255]*d
        for i in range(n):
            vec[-1] = 255 - (i % 256)
            vec[-2] = 255 - (i // 256 % 256)
            vec[-3] = 255 - (i // 256 // 256 % 256)
            print(*vec,file=FILE)
        for i in range(m):
            vec[-1] = 255 - (i % 256)
            vec[-2] = 255 - (i // 256 % 256)
            vec[-3] = 255 - (i // 256 // 256 % 256)
            if ri(0,2)==1:
                vec[-4] = 254
            else:
                vec[-4] = 255
            print(*vec,file=FILE)

gen('hand2.in', 10**4, 10**4, 10**2)
gen('hand3.in', 10**3, 10**3, 10**3)
gen('hand4.in', 10, 10, 10**5)
