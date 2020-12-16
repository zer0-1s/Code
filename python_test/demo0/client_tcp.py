import socket

target_host="www.baidu.com"
target_port=80

# set an socket object
'''
AF_INET represent standard IPV4 address or hostname.
SOCK_STREAM represent TCP client.
TCP (SOCK_STREAM) is a connection-based protocol. The connection is established and the two parties have a conversation until the connection is terminated by one of the parties or by a network error.
'''
client =socket .socket(socket.AF_INET,socket.SOCK_STREAM)
# link to client
client.connect((target_host,target_port))
# sent some data to target ip
client.send(b"GET / HTTP/1.1\r\nHost:baidu.com\r\n\r\n")
# recvive some data
response=client.recv(4096)

print (response)