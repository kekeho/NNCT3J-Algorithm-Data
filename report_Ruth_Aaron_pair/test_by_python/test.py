#!/usr/bin/env python3
import sympy
import sys
from multiprocessing import Pool
import multiprocessing as multi

START = 4294967296
STOP = 4294977295
ALL = STOP - START

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


def checkRuthAaronPair(i):
    indicator(ALL, i - START)
    pair = makePair(i)
    if pair[0] == pair[1]:
        return pair[2], pair[2] + 1


def main(start, stop):
    ruthAaronPair = []
    p = Pool(multi.cpu_count())
    ruthAaronPair = p.map(checkRuthAaronPair, range(start, stop))
    print('Done!')
    with open('result.txt', mode='w') as file:
        for p in ruthAaronPair:
            if p != None:
                print(p)
                file.write('{},{}\n'.format(p[0], p[1]))

def indicator(all, now):
    print('\rおおよその進捗: {now} / {all}'.format(now=now, all=all), end='')

if __name__ == '__main__':
    # try:
    #     main(int(sys.argv[1]), int(sys.argv[2]))
    # except IndexError as e:
    #     print("ERROR!: missing arguments")
    #     print("USAGE:\n\ttest.py <start> <end>")
    main(START, STOP)
