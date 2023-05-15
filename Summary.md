
## 工具

make 仅仅是一个工具，也快成为时代的眼泪了！只需要知道从哪里找到[手册](https://www.gnu.org/software/make/manual/make.html)即可。

如果真的可能需要，可以参考下[Shell脚本——make命令和Makefile文件](https://blog.csdn.net/twc829/article/details/72729799)。

gcc，虽然不是时代眼泪，但也只需要知道[选项](https://gcc.gnu.org/onlinedocs/gcc/Option-Index.html)从哪找即可。



## 代码

C语言早期实现要求变量写在开头，C99取消了这一限定。此程序编写时C99应该还没出，所以可读性差一些。

getopt_long至少是C处理参数最好的方式了。我甚至见过用python写参数处理不如此份代码的。

代码前半段展现出了socket api，http协议，以及C string api，说实话，都GPT时代了，这种纯粹的api使用流，没有太多价值了。

利用fork特性，实现压测。 fork后父子进程间共享打开文件，而变量是写时复制。 通过管道进行父子进程通讯，传递测试结果（但并发写应该有问题吧）。

在压测核心代码部分，通过alarm signal设置停止标记。中断信号会唤醒socket，errno等于EINTR，于是把失败数-1。


如果从网络编程的角度看，此程序是极其简单的，没有涉及socket选项，也不存在多路复用。该程序只能算入门级。
