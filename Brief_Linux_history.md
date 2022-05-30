# Brief Linux history

在学习Linux的过程中，发现Linux版本众多并且有一些小的区别，同时有大量的概念并不清楚，因此对其发展历程有了点兴趣。

由于阅读面有限，加之能力不足，只想借该记录对碎片式的信息进行大概的整理。毕竟不是主要任务 -.-!

不定期更新，看到啥有趣的都会记录在这里。

---

Linux最早是芬兰（Finnish）学生Linus Torvalds在1991年创造的一个free operating system kernel。而由此创造的Linux kernel一直不断地增长。

自1991年最初公布以来，Linux的源代码（source code）从寥寥几个C files成长为一个拥有超过23.3 million行数的一个庞大的系统，并且拥有GNU通用公共许可证（GNU General Public License, GPL)。

kernel - 指的是操作系统的核心（the core of the operating system itself），而不是运行在这个系统上的应用（applications），比如编译器（compiler），shells等。

在今时今日，Linux这个单词用以指代具有Linux kernel的一个软件环境（software environment），包含了其他大量的应用和软件组件。

所以在更大的意义上，许多人更喜欢使用GNU/Linux这个术语，指代那些发挥了关键作用的工具（tools from GNU project）。

Linux不是 “a version of Unix”，但Linux提供了标准UNIX系统的所有通用编程接口（the common programming interfaces）。

Linux是，但不仅仅是免费的。它是一款很好的软件。Linux的优势其实可以追溯到软件自由概念（the concept of software freedom)的诞生，这是驱动Linux不断创新，不断发展的根源。

下文引自Linux in a Nutshell：

时至今日，许多程序员仍旧在追忆（fondly remember）AT&T免费提供UNIX源码和UC Berkeley以所有可能的方式分发它们自己版本的那个年代。
时过境迁，对于那些老的黑客们（older hackers），Linux的出现带回了往日的精神 - 共同创造（working together）一个好的社区，尤其是如今互联网普及的大背景下。许多人可能没经历过第一轮系统开放，或早已因专有系统的限制而心灰意冷地放弃了自己曾经的探索。
但Linux来了，这正是体验自由分发的源代码和无限适应接口中蕴藏着的美妙的时刻（discovery the wonders）。

Interface: In computing, an interface is a shared boundary across which two or more separate components of a computer system exchange information.
The exchange can be between software, computer hardware, peripheral devices, humans and combinations of these.

由于除了kernel之外，涉及功能性计算环境需要大量的工具，因此从头搭建一个Linux安装流程是非常复杂的。

Linux命令与标准的Unix命令不同。Linux的大多数命令是由自由软件基金会（Free Software Foundation, FSF）运行着的GNU project提供。

GNU means "GNU's Not Unix" - the first word of the phrase is expanded with infinite recursion.

Linux kernel是一个免费和开源的、单片、模块化、多任务、类Unix的操作系统内核。最初在1991年由Linus Torvalds在1991年在i386-based PC上编写，并很快被GNU操作系统作为其系统的内核。GNU则是作为UNIX的免费替代版本而被编写出来。

在上世纪90年代（1990s），这样一个kernel被大量的操作系统发行版（operating system distributions）所采用的，而这些发行版通常也被称为Linux。但是，对这类系统的命名一直存在着争议，包括[ichard Stallman](https://en.wikipedia.org/wiki/Richard_Stallman)本人都辩称将这些操作系统成为Linux是错误的。他认为这些操作系统实际上大部分是GNU，，Linux内核则是在1983年启动GNU project九年后的1992年晚些时候才添加为一个组件，于是这些系统被命名为GNU/Linux作为替代的称呼。

大多数Linux kernel的代码是由标准C语言的GNU扩展-GCC编写的，并使用特定的体系结构的指令（ISA）。这样就产生了大量高度优化的可执行文件（vmlinux），在内存利用率和任务执行时间方面有所提高。

(当然，因为GCC的问题，之前安装文件也遇到了各种困难，T_T)。

**[Kernel](https://en.wikipedia.org/wiki/Kernel_(operating_system))**:

kernel是一种位于计算机操作系统核心的计算机程序。它是操作系统代码的一部分，始终驻留在内存中，便于硬件和软件组件之间的交互。

一个完整的内核通过设备驱动控制所有硬件资源（如I/O，内存，加密），仲裁不同程序在占用资源中的冲突，并优化公共资源的利用，包括CPU和缓存的使用，管理文件系统和网络套接字（network sockets）。

![kernel](https://upload.wikimedia.org/wikipedia/commons/8/8f/Kernel_Layout.svg)

## Reference
- [History_of_Linux](https://en.wikipedia.org/wiki/History_of_Linux)
- Linux in a Nutshell, Sixth Edition by Ellen Siever, Stephen Figgins, Robert Love, and Arnold Robbins, 2009. ISBN: 978-0-596-15448-6
- [Interface](https://en.wikipedia.org/wiki/Interface_(computing))
- [Linux_kernel](https://en.wikipedia.org/wiki/Linux_kernel)
