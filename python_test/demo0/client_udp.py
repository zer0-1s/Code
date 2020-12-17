import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
'''
UDP procotol will not connect to party which recvive the data.
Unlike TCP, it is unreliable and connectionless procotol.
'''
data=b'this is 80 port as all we known!'
# send data: send 127.0.0.1:80 some data regardless the receiver receive or not.
s.sendto(data, ('127.0.0.1',80))
# returns a bytes object read from an UDP socket and the address of the client socket as a tuple.
print(s.recvfrom(1024))
s.close()

'''
output:
(b'\n', ('127.0.0.1', 80))
we can listen to local 80 port to watch the echo,and we could get this.
➜  Desktop nc -lu  -p 80  
this is 80 port as all we known!

'''