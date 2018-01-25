#!/usr/bin/env python3
import sympy #代数計算ライブラリ
from multiprocessing import Pool #並列計算ライブラリ
import multiprocessing as multi #CPUのスレッド数を特定するためのライブラリ
import time

#計算範囲指定
START =  4294967295+1
STOP = 4295967296

#(ルースアーロンか判定していない)ペアの生成
#numとnum+1でペアの生成
def makePair(num):
    # num=2016 -> pair1={2: 5, 3: 2, 7: 1} (2^5 + 3^2 + 7^1)
    #素因数のリストを生成
    pair1_dict = sympy.factorint(num) #num
    pair2_dict = sympy.factorint(num + 1) #num+1

    x = 0 #numの素因数の和
    y = 0 #num+1の素因数の和
    
    #加算処理
    for k, v in pair1_dict.items():
        for i in range(v):
            x += k

    for k, v in pair2_dict.items():
        for i in range(v):
            y += k
    return (x, y, num) #n


#ルースアーロンペアかどうかのチェック
def checkRuthAaronPair(num):
    pair = makePair(num) #numとnum+1でペアの生成
    #ルースアーロンペアかのチェック
    if pair[0] == pair[1]:
        return pair[2], pair[2] + 1


def main(start, stop):
    timer_start = time.time() #タイマースタート
    ruthAaronPair = []
    p = Pool(multi.cpu_count()) #スレッド数の指定
    ruthAaronPair = p.map(checkRuthAaronPair, range(start, stop)) #並列処理
    timer_result = time.time() - timer_start #タイマーストップ
    print('Done! {} second'.format(timer_result))
    #結果をファイルとコンソールに出力
    with open('result.txt', mode='w') as file:
        for p in ruthAaronPair:
            if p != None:
                print(p)
                file.write('{},{}\n'.format(p[0], p[1]))

if __name__ == '__main__':
    main(START, STOP) #実行
