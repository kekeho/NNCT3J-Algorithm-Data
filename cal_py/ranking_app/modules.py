#!/usr/bin/env python3
import time
import shutil
from data import db
from subprocess import getstatusoutput
data = db.data()

# personId: Student number like 15316, 15421, 14215...


def scoreCounter(SourceFilePath, personName, personId):
    # compile C source with GCC
    gccCmd = "gcc -o data/{id}.out {sourceFile}".format(
        id=personId, sourceFile=SourceFilePath)
    compileResult = getstatusoutput(gccCmd)

    # compile error
    if compileResult[0] != 0:
        print("GCC COMPILE ERROR:\n", compileResult[1])
        print("コンパイル時にエラーが出たのでランキングには反映されません😇")
        exit()

    # count start!
    startTime = time.time()
    runResult = getstatusoutput("./{id}.out".format(id=personId))
    endTime = time.time()
    if runResult[0] != 0:
        print("RUNTIME ERROR:\n", runResult[1])
        print("実行時にエラーが出たのでランキングには反映されません😇")
        exit()

    score = endTime - startTime

    # add score to database
    data.add(personId, personName, score)
    print("結果".center(shutil.get_terminal_size().columns, '='))
    print("Time: {second}s, 第{rank}位\n".format(second=score, rank=114514).center(shutil.get_terminal_size().columns))
    print(runResult[1])
