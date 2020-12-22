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
