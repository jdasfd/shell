# Linux learning

##  对变量进行替换

```bash
A=aigo.goto.aigo.goto
echo ${A#*go}
echo ${A##*go}
echo ${A%go*}
echo ${A%%go*}
```

shell中对变量赋值时，记住不要在变量名中加空格

这个时候将上面的命令放入脚本中运行后可以得到如下结果

```bash
.goto.aigo.goto
to
aigo.goto.aigo.
ai
```

这些结果说明上述的命令可以对变量进行替换

#*go      指的是从左边开始匹配到的第一个go开始，包括go的左边全部去除

##*go   指的是从右边开始匹配到的第一个go开始，包括go的左边全部去除

%go*     指的是从右边开始匹配到的第一个.开始，包括.的右边全部去除

%%go*  指的是从右边开始匹配到的第一个go开始，包括go的右边全部去除

所以能够通过上述的命令对变量进行替换



#  文件描述符及重定向

##  文件描述符

Linux系统预留了三个文件描述符，意义分别是：

0-标准输入 (stdin)

1-标准输出 (stdout)

2-标准错误 (stderr)

假设在一个没有文件的路径之下，有且只有一个文件名称为1.txt，此时如果运行如下ls 1.txt这个命令，屏幕上会出现如下显示：

1.txt

这就是stdout的内容，标准输出至屏幕上

```bash
ls 1.txt
```

结果屏幕上会输出这个1.txt，这个就是标准输出的结果

```bash
ls 2.txt
```

此时屏幕上会出现如下显示：

ls: 无法访问2.txt: 没有那个文件或目录

上面的在屏幕上输出的结果就是stderr

##  重定向

两个重定向的符号分别为 > 和 >>，分别是直接覆盖写入，另一个是在原文件的后面追加输入

对于上面的举例，如果我们进行重定向会出现如下的情况

```bash
ls 1.txt 1>stdout.txt
cat stdout.txt
```

此时对stdout.txt进行cat读取后，屏幕上会出现"1.txt"，即将标准输出的结果1.txt重定向记录到了stdout.txt里面

```bash
ls 2.txt 2>stderr.txt
cat stderr.txt
```

此时读取后，屏幕上会显示"ls: 无法访问2.txt: 没有那个文件或目录"，即将标准错误的结果重定向记录到了stderr.txt

&符号是等同于的意思，如果想让标准输出和标准错误全部输入到同一个文件里，则可以使用：

2>&1 表示2的输出重定向等同于1，即将标准输出和标准错误到同一个地方

##  Linux特殊文件

/dev/null是一个特殊的设备文件，这个文件接收到任何数据都会被丢掉。因此，null这个设备通常被称为位桶(bit bucket)或黑洞

因此：

2>/dev/null的意思就是将标准错误stderr删掉



#  Compress or decompress file using gz

```bash
# Compress file
gzip filename
# Decompress file
gzip -d filename.gz
```



#  linux中大于号和小于号的作用

在之前的重定向中已经介绍了作为重定向符号

· >覆盖输出到文本

· >>追加到文本后

那么小于号的作用是什么呢？

小于号中能够使用的符号包括 <，<<，<<<



## · < 将后面文件作为前面命令的输入

比如此时如果我们使用一个命令

```bash
cat > test.txt
aaa
^C
```

那么此时会cat会默认捕捉标准输入($0)的内容进入test.txt中，如果此时属入aaa敲击回车后按Ctrl+C，则可以将aaa作为输入内容导入到test.txt中

此时如果输入如下的两个命令

```bash
cat test.txt
cat < test.txt
```

输出的结果一致，均会在屏幕出现aaa作为cat命令的输出。按我的理解，这里是直接将text.txt作为cat命令的输入传递给cat，那么cat就能执行读取test.txt的命令，显示aaa，所以这两个命令没有本质差别



## · << 带命令作用全文匹配某个字符串后结束

比如如果我们此时在命令行中输入如下的内容：

```bash
cat << eof
# screen will let you input something until you input eof
# for example, if you input something like the following
> hello
> world
> apple
> base_name
> eof
# then command cat will output on the screen:
#hello
#world
#apple
#base_name
# and if you want to input this into a file, you could run this
cat > test.txt << eof
# then all things will be redirected to test.txt, but not to stdout ($1)
```



##  · <<< 将后面的双引号内的内容传递给前面的命令

利用这个命令我们可以实现不同的功能

```bash
grep 'aa' <<< "ccccaa"
sed 's/g/dddd/' <<< "ghhhg"
sed 's/g$/dddd/' <<< "ghhhg"
bc <<< "${BASES} / ${GENOME}"
```



# 用Rscript给R脚本传递参数

```bash
Rscript <file>.r 1 2
```

将1和2传递给.r脚本，利用args传递

而在.r脚本中，需要的命令是

```R
args <- commandArgs(T)
# 收集参数给args变量，args[1] = 1, args[2] = 2
```

这样就可以根据不同的参数执行不同的命令

