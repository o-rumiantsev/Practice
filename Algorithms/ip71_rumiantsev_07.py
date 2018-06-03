import sys
from time import time

if len(sys.argv) < 2:
    print 'Please, enter input filename'
    exit(1)

filename = sys.argv[1]
file = open(filename)

input = [line.strip().split() for line in file]
file.close()

data = map(lambda x: map(lambda y: int(y), x), input)

W = data[0][0]
n = 500
del data[0]

cache = {}
def knapsackTD(l, w):
    global cache, data, W

    key = str([l, w])
    if key in cache:
        return cache[key]


    if l == 0 or W == 0: return 0

    vi = data[l - 1][0]
    wi = data[l - 1][1]

    if wi > w:
        res = knapsackTD(l - 1, w)
        cache[key] = res
        return res
    else:
        res = max([knapsackTD(l - 1, w), knapsackTD(l - 1, w - wi) + vi])
        cache[key] = res
        return res


opt = knapsackTD(len(data), W)

output = open('ip71_rumiantsev_07_output.txt', 'w')
output.write(str(opt))
