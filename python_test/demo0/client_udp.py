import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

data=b'this is 80 port as all we known!'
# send data:
s.sendto(data, ('127.0.0.1',80))
# recvive data:
print(s.recvfrom(1024))
s.close()

'''
we can listen to local 80 port to watch the echo,and we could gety this.
➜  Desktop nc -lu  -p 80  
this is 80 port as all we known!

'''