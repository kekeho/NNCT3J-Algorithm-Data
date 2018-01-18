#!/usr/bin/env python3
import sympy
import sys


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
    return (x, y)


def checkRuthAaronPair(start, stop):
    ruthAaronPair = []
    for i in range(start, stop):
        pair = makePair(i)
        if pair[0] == pair[1]:
            ruthAaronPair.append(pair)

    return ruthAaronPair


def main(start, stop):
    pair = checkRuthAaronPair(start, stop)
    for p in pair:
        print(p)


if __name__ == '__main__':
    main(int(sys.argv[1]), int(sys.argv[2]))
