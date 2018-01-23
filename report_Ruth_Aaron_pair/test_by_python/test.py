#!/usr/bin/env python3
import sympy
import sys
from numba import jit, int64


@jit(int64(int64))
def makePair(num):
    # num=2016 -> pair1={2: 5, 3: 2, 7: 1} (2^5 + 3^2 + 7^1)
    pair1_dict = sympy.factorint(num)
    pair2_dict = sympy.factorint(num + 1)

    x = 0
    y = 0
    for k, v in pair1_dict.items():
        for i in range(v):
            x += k

    for k, v in pair2_dict.items():
        for i in range(v):
            y += k
    return (x, y, num)


@jit(int64(int64, int64))
def checkRuthAaronPair(start, stop):
    ruthAaronPair = []
    for i in range(start, stop):
        pair = makePair(i)
        if pair[0] == pair[1]:
            ruthAaronPair.append((pair[2], pair[2] + 1))

    return ruthAaronPair


def main(start, stop):
    pair = checkRuthAaronPair(start, stop)
    with open('result.txt', mode='w') as file:
        for p in pair:
            print(p)
            file.write('{},{}\n'.format(p[0], p[1]))


if __name__ == '__main__':
    START = 4294967296
    STOP = 4294977295
    # try:
    #     main(int(sys.argv[1]), int(sys.argv[2]))
    # except IndexError as e:
    #     print("ERROR!: missing arguments")
    #     print("USAGE:\n\ttest.py <start> <end>")
    main(START, STOP)
