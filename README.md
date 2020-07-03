# /dev/null_segv
(Format:UTF-8)  
A module to send SIGSEGV when read or write

## 概要
**これはジョークソフトです。常用や他人と共有しているPCでは実行しないでください。**  
読み書きしたらSEGVする/dev/null_segvを生やすための怪しいソフトです。  

## ビルド
### 依存関係
* build-essential
* kernel-headers

### ビルド

```
$ make
$ sudo make load
$ sudo make unload # 電源を切る前に行ってください
```
