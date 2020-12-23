<p>
insmod:模块载入内核</br>
rmmod:模块从内核中卸去</br>
</p>

<code>
#before this you need to make
ctf@ubuntu:~/Desktop/helloworld$ sudo insmod ./hello.ko && sudo rmmod hello
[sudo] password for ctf: 
ctf@ubuntu:~/Desktop/helloworld$ dmesg -t | tail -2
Hello world
Goodbye
ctf@ubuntu:~/Desktop/helloworld$ dmesg -t | tail -2 > log.txt
ctf@ubuntu:~/Desktop/helloworld$ cat log.txt
Hello world
Goodbye
ctf@ubuntu:~/D
</code>

```
printf() -> printk()，但需要注意的是 printk() 不一定会把内容显示到终端上，但一定在内核缓冲区里，可以通过 dmesg 查看效果
```

