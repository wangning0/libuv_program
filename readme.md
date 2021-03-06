# libuv programming

> 构建详情请看[issue](https://github.com/wangning0/Autumn_Ning_Blog/issues/39)

## therads

### libuv work queue

`uv_queue_work()`是一个便利的函数，它使得一个应用程序能够在不同的线程运行任务，当任务完成后，回调函数将会被触发

看起来好像很简单，但是它真正吸引人的地方在于它能够使得任何第三方的库都能以event-loop的方式知性。当使用event-loop的时候，最重要的是不能让loop线程阻塞，或是执行高cpu占用的程序，因为这样会使得loop慢下来，loop-event高效的特性也不能很好地发挥

然而，很多带有阻塞的特性的程序使用开辟新线程来响应新请求（最经典的一个客户，一个线程模型).使用event-loop可以提供另一种实现的方式，libuv提供了一个很好的抽象，使得你能够更好的使用它

从libuv 0.9.4版后，添加了函数`uv_cancel()`。它可以用来取消工作队列中的任务。只有还未开始的任务可以被取消，如果任务已经开始执行或者已经执行完毕，`uv_cancel`()调用会失败。

当用户想要终止程序的时候，`uv_cancel`()可以用来清理任务队列中的等待执行的任务


### inter-thread communication

很多时候 我们希望正在运行的线程之间能够相互发送消息。例如你在运行一个持续时间长的任务（可能使用`uv_queue_work`)，但是你需要在主线程中监视它的进度情况。

因为异步的线程通信是基于event-loop，所以尽管所有的线程都可以是发送方，但是只有在event-loop上的线程可以是接收方。


## Processes

libuv提供了相当多的子进程管理函数，并且是跨平台的，还允许使用stream，或者说pipe完成进程间的通信

在UNIX中又一个共识，就是进程只做一件事，并把它做好，因此，进程通常创建子进程来完成不同的任务，一个多进程的，通过消息通信的模型，总比多线程的，共享内存的模型要容易理解的多

当前一个比较常见的反对事件驱动编程的原因在于，其不能很好地利用现代多核计算机的优势。一个多线程的程序，内核可以将线程调度到不同的CPU核心中执行，提高性能。但是一个event-loop的程序只有一个线程，实际上，工作区可以被分配到多进程上，每一个进程执行一个event-loop，然后每个进程被分配到不同的cpu核心中执行

### Spawning child processes

