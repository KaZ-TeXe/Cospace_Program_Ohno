# dll generatorの使い方 (How to use dll generator)

dll generatorは、Cospace用のdllファイルを自動で作成するツールである。
`dll generator` makes `dll` file for rescue simulation from c++ language.


原理は、`code`というフォルダーに入っている拡張子が`.cpp`のファイルを検索し、それらすべてをまとめてコンパイルする。
`dll generator` search all `.cpp` files in `code(c++)` folder and compile these files to one dll file.
そのため、Cospaceに関係ない`.cpp`のファイルはcodeのフォルダーの中に入れてはならない。
So, you must not put any `.cpp` file which is unrelated to rescue simulation.

## Pythonをインストールしている場合(If you have python)

dll_generator.pyをコピーして、以下のようなフォルダー構造にしなければならない。
You must have folders like the graph.

> folder/<br>
> 　├ code/<br>
> 　│　└ main.cpp<br>
> 　│　└ tools.cpp<br>
> 　│　└ tools.hpp<br>
> 　└ dll_generator.py

`python dll_generator.py`とコマンドプロンプトで実行する。
And run 'python dll_generator.py` in command prompt.

## Pythonをインストールしていない場合(If you don't have python)

`cplus.exe`をコピーして、以下のようなフォルダー構造にしなければならない。
you must have folders like the graph.

> 適当なフォルダー/<br>
> 　├ code/<br>
> 　│　└ main.cpp<br>
> 　│　└ tools.cpp<br>
> 　│　└ tools.hpp<br>
> 　└ cplus.exe

その後、`cplus.exe`を実行すればよい。
Run `cplus.exe` in the command prompt.


## コマンドラインオプション一覧

- --help
  - コマンドオプション一覧を表示する
  - show all options
- --debug
  - debugモードで実行する
  - run in debug mode
- --outhere
  - Ninja.dllを、dll_generator(c++)がある場所に生成する
  - generate Ninja.dll as same folder
- --outcospace
  - Ninja.dllを、`/Microsoft Robotics Dev Studio 4/CS/User/Rescue/CsBot/`の中に生成する
  - generate Ninja.dll in `/Microsoft Robotics Dev Studio 4/CS/User/Rescue/CsBot/`
- --no-lite-warming
  - 重要度の低い警告を無視する
  - Ignore warmings

## 最終更新日時

* ReadMe.md : 2019-06-10 18:50:56
* ReadMe.pdf : 2019-06-10 18:51:03
* dll_generator.py : 2019-04-13 10:10:24
* dll_generator.exe : 2019-04-13 10:10:29
