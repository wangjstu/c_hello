##如何运行

* 在命令行下执行

```
make ex1    //或者：CFLAGS="-Wall" make ex1
```

> 第一个命令中你告诉make，“我想创建名为ex1的文件”。于是Make执行下面的动作：
> 
> * 文件 ex1 存在吗？
> * 没有。好的，有没有其他文件以 ex1 开头？
> * 有，叫做 ex1.c 。我知道如何构建 .c 文件吗？
> * 是的，我会运行命令 cc ex1.c -o ex1 来构建它。
> * 我将使用 cc 从 ex1.c 文件来为你构建 ex1 。

 
* 运行

```
./ex1
```
