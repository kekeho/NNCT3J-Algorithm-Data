# お試し
授業で作成した多倍長演算ライブラリを使って課題を進める前に、試しにPythonでやってみた。

# できること
指定した範囲の間でルースアーロンペアを見つけられる。  
結果はターミナルに出力されるだけなくresult.txtに出力もされる。(常に自動的に上書きされるので注意。)

# 依存関係のインストール
Python3  
必要なライブラリ: sympy, multiprocessing
Python3がインストールされている環境で以下のコマンドを実行することでインストール可能。
```
pip3 install sympy
pip3 install multiprocessing
```

# 使い方
1~10までの間でアーロンペアを見つけたい場合、まずtest.pyのSTARTとSTOPにそれぞれ1, 10を書き込んで
```
python3 test.py
```