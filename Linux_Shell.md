# Linux Shell Learning

Recording shell commands study processes (in simplified Chinese).

记录在shell中遇到的问题以及学习的笔记。

## 基本的I/O重定向

标准输入/输出(standard I/O)可能是软件设计原则中最重要的概念了。这个概念就是：程序应该有数据的来源端、数据的目的端（数据要去的地方）以及报告问题的地方，分别是标准输入（standard input）、标准输出（standard output）和标准错误输出（standard error）。程序不必知道也不关心它的输入与输出是什么设备。许多UNIX程序都遵循这一原则。

默认情况下：这些程序会读取标准入，写入标准出，并将错误传入标准误。这类程序通常叫过滤器（filter）。

### 重定向输出`>`

- 以`>`改变标准输出

对于上面的举例，如果我们进行重定向会出现如下的情况

```bash
echo "1" > test.txt

cat test.txt
#1
```

`>`会直接覆盖写入重定向的文件，如果没有文件，则会创建一个新文件并输入。

- 以`>>`改变标准输出

与`>`的区别在于在原文件的后面追加输入，如果没有文件，则会创建一个新文件并追加输入。

比如**继续用上面的例子**:

```bash
echo "2" >> test.txt

cat test.txt
#1
#2

echo "3" > test.txt
#3
# overwrite again
```

### 重定向输入`<`

- 以`<`改变标准输入

`<` 将后面文件作为前面命令的输入

```bash
program < file
```

可以将program的标准输入修改为由file传入:

```bash
tr -d '\n' < dos-file.txt
# delete all newline character '\n' in dos-file.txt
```

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

但有时如果一个命令只能通过文件来接受而非标准入（即管道符此时不能完成重定向），则可以用这种重定向来将另一个命令的输入伪装成文件。

如[faops](https://github.com/wang-q/faops)中使用到的例子：

```bash
faops order test/ufasta.fa \
    <(cat test/ufasta.fa | grep '>' | sed 's/>//' | sort) \
    out.fa
```

由于`faops`需要从标准输入接受文件，所以可以利用`<`将后面命令运行的结果伪装成一个文件传入前一个命令。

- `<<` 将开始tag和结束tag之间的内容作为输入

比如如果我们此时在命令行中输入如下的内容：

```bash
cat << eof
hello
world
apple
base_name
eof 
# screen will let you input something until you input another eof
# then command cat will output on the screen:
#hello
#world
#apple
#base_name

# and if you want to input this into a file, you could run this
cat > test.txt << eof
...
eof
# then all things will be redirected to test.txt, but not to stdout
```

- `<<<` 将后面的双引号内的内容传递给前面的命令

利用这个命令我们可以实现不同的功能

```bash
grep 'aa' <<< "ccccaa"
#ccccaa ([aa] is red on my screen in Ubuntu)
sed 's/g/dddd/' <<< "ghhhg"
#ddddhhhg
sed 's/g$/dddd/' <<< "ghhhg"
#ghhhdddd
bc <<< "3+6"
#9
bc <<< "${BASES} / ${GENOME}"
# this command actually calculate the result of ${BASES} divided by ${GENOME} 
```

### 其他重定向

- `&`

`&`符号是等同于的意思，如果想让标准输出和标准错误全部输入到同一个文件里，则可以使用：

`2>&1` 表示2的输出重定向等同于1，即将标准输出和标准错误到同一个地方

`n>&m` 表示将输出文件m和n合并

`n<&m` 表示将输入文件m和n合并

- `|`

`|`管道（pipeline）符号也是一个重要的重定向符号，会将上个程序的标准出变成下个程序的标准入。

```bash
tr -d '\n' < file1.txt | sort > file2.txt
```

先删除`file1.txt`的回车符，在完成数据的排序后，将结果输出到`file2.txt`。

### Linux特殊文件

/dev/null是一个特殊的设备文件，这个文件接收到任何数据都会被丢掉。因此，null这个设备通常被称为位桶(bit bucket)或黑洞

因此：

`2>/dev/null`的意思就是将标准错误stderr删掉

## 文件描述符与特殊变量

### 文件描述符

Linux系统预留了三个文件描述符，意义分别是：

0-标准输入 (stdin)

1-标准输出 (stdout)

2-标准错误 (stderr)

假设在一个没有文件的路径之下，有且只有一个文件名称为`1.txt`，此时如果运行如下`ls 1.txt`这个命令

```bash
ls 1.txt
#1.txt
```

此命令的结果会在屏幕上出现`1.txt`。这就是stdout的内容，并显示至屏幕上。

```bash
ls 2.txt
#ls: cannot access '2.txt': No such file or directory
```

由于上面的命令没有成功运行，在屏幕上输出的结果`ls: cannot access '2.txt': No such file or directory`就是stderr，并显示至屏幕上。

当以`>`改变标准输出时:

```bash
ls 1.txt 1>stdout.txt
cat stdout.txt
#1.txt
```

此时对stdout.txt进行cat读取后，屏幕上会出现"1.txt"，即将标准输出的结果1.txt重定向记录到了stdout.txt里面。

`1`就代表文件描述符stdout，其效果等同于`ls 1.txt > stdout.txt`

```bash
ls 2.txt 2>stderr.txt
cat stderr.txt
#ls: cannot access '2.txt': No such file or directory
```

此时读取后，屏幕上会显示"ls: 无法访问2.txt: 没有那个文件或目录"，即将标准错误的结果重定向记录到了stderr.txt。

这些就是文件描述符的作用。

当以`>>`改变标准输出时，与上述例子同样的：

```bash
ls 1.txt 1>>stdout.txt
cat stdout.txt
#1.txt
#1.txt
```

上面是预留的文件描述符的作用。

### Shell中的特殊变量

主要的特殊变量包括：`$#`, `$@`, `$0`, `$1`, `$2`等。（其他特殊变量遇到时再进行更新）

变量说明：

`$$`: Shell本身的PID (ProcessID)

`$!`: Shell最后运行的后台Process的PID

`$?`: 最后运行的命令的返回值

`$-`: 使用Set命令设定的Flag一览

`$*`: 所有参数列表。如果是`"$*"`的情况，以"$1 $2 ... $n"的形式输出所有参数

`$@`: 所有参数列表。如果是`"$@"`的情况，以"$1" "$2" ... "$n"的形式输出所有参数

`$#`: 添加到Shell的参数个数

`$0`: Shell本身的文件名

`$1 - $n`: 添加到Shell的各个参数值。`$1`是第1个参数、`$2`是第二个参数...

### 访问Shell脚本的参数

所谓的位置参数（positional parameters）指的是Shell脚本的命令行参数（command-line arguments）。在Shell函数中，它们同时也可以是函数的参数。基于历史的原因，当它超过9，就应该用大括号把数字框起来：

```bash
echo first arg is $1
echo tenth arg is ${10}
```

## 对变量进行替换

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

`#*go`      指的是从左边开始匹配到的第一个go开始，包括go的左边全部去除

`##*go`   指的是从右边开始匹配到的第一个go开始，包括go的左边全部去除

`%go*`     指的是从右边开始匹配到的第一个.开始，包括.的右边全部去除

`%%go*`  指的是从右边开始匹配到的第一个go开始，包括go的右边全部去除

所以能够通过上述的命令对变量进行替换

## 变量命名的注意事项

在对变量进行命名的时候，要注意在shell脚本中，变量需要以字母进行开头，而不允许数字开头的形式

```bash
$ 1mis=1
1mis=1: command not found

$ mis1=1
$ echo $mis1
1
```

## Shell中相关文件的压缩及解压

处理压缩文件时会碰到`.gz`和`.tar.gz`

tar指的是打包，如果仅仅是打包，`<file> --> <file>.tar`

打包后再压缩，则为`<file>/<file>.tar --> <file>.gz/<file>.tar.gz`

`.gz` file（不涉及打包）:

```bash
# Compress file
gzip filename
# Decompress file
gzip -d filename.gz
```

`.tar.gz` file（涉及打包）:

```bash
# Compress file
tar -cvzf <file>.tar.gz source_file
# source_file: 源文件

# Decompress file
tar -xzvf <file>.tar.gz [-C path]

# -c, --create: 创建归档文件，即打包
# -x, --extract: 解压
# -z, --gzip, --gunzip, --ungzip: 通过gzip来归档后压缩
# -v, --verbose: 可视化，在stdout中显示处理过程
# -f, --file: 被操作的文件名
# -C, --directory=DIR: 指定解压路径，无该参数时解压至当前路径
```

## 用Rscript给R脚本传递参数

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

也可以在R的脚本中加入下列命令，optparse可以做到类似Perl或Python的数据传入方式，这样就可以用变量来代替args

```R
library("optparse")

option_list = list(
    make_option(c("-f","--file"), type = "character", default = NULL,
    help = "tsv file name", metavar = "character"),
    make_option(c("-o","--out"), type = "character", default = "output.pdf",
    help = "output pdf script in category name [default = %default]", metavar = "character"),
    make_option(c("-a","--outall"), type = "character", default = "outputall.pdf",
    help = "output pdf script name [default = %default]", metavar = "cahracter"),
    make_option(c("-t","--title"), type = "character", default = NULL,
    help = "output script RNA for maintitle", metavar = "character")
);

opt_parser = OptionParser(option_list=option_list);
opt = parse_args(opt_parser);

# opt$file, opt$out... variable could be used in the command
```

```bash
Rscript <file.r> [options -f <file> -o <output> ...]
```

## Common linux shell tool usage

### grep

`-q : Quiet: do not write anything to standard output. Exit immediately with zero status if any match is found, even if an error was detected.`
安静模式，不打印任何标准输出，当有匹配的内容时立即返回状态值0.

```bash
cat a.txt
nihao
nihaooo
hello

if grep -q hello a.txt; then
echo "yes";
else
echo "no";
fi
Output:
yes

if grep -q word a.txt; then
echo "yes";
else
echo "no";
fi
Output:
no
```

帮助判断是否含有字符串，同时不产生`grep`的结果.

### curl

`-L`：跟随网站的跳转
`-O`: 写入到文件，文件名和远程文件一样

### datamash
