import socket
import threading 
# make sure the ip and port that we need to listen 
server_ip="0.0.0.0"
server_port=9999
# init socket 
server=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind((server_ip,server_port))
'''
used socket.gethostname() so that the socket would be visible to the outside world. 
If we had used s.bind(('localhost', 80)) or s.bind(('127.0.0.1', 80)) we would still have a “server” socket, 
but one that was only visible within the same machine.
'''
server.listen(5)


print("[*]Listening to %s:%d" %(server_ip,server_port))

def handle_client(client):
    request=client.recv(1024)
    print ("the request is %s "%(request))
    client.send(b"the is web server!")
    client.close()
while True:
    client,addr=server.accept()# addr represent truple 
    print ("[*] accept from is %s:%d"%(addr[0],addr[1]))
    
    client_handler=threading.Thread(target=handle_client,args=(client,))
    client_handler.start()
'''
output:

[*]Listening to 0.0.0.0:9999
[*] accept from is 127.0.0.1:42464
the request is b'ABCDE' 
'''

