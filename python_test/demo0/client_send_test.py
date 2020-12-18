import socket

target_host="127.0.0.1"
target_port=9999

# set an socket object
client =socket .socket(socket.AF_INET,socket.SOCK_STREAM)
# link to client
client.connect((target_host,target_port))
# sent some data to target ip
client.send(b"ABCDE")
# recvive some data
response=client.recv(4096)

print (response)

'''
➜  Desktop python3 m.py
b'the is web server!'
'''