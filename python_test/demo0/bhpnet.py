import sys
import getopt
import socket
import threading
import subprocess


#define global $var
listen            =False
command           =False
upload            =False
target            =""
upload_destination =""
execute           =""
ip                =0

def usage():
    print ("[*]BHP NET TOOL")
    #print ()

    print ()
    print ("Usage: bhpnet.py -t target -p port ")
    print ("-l --listen               -listen on [host]:[port] for incoming connections")      
    print ("-e --execute file_to_run  -execute the given file upon recvieving a connection")
    print ("-c --command              -initiaize a command shell")
    print ("-u --upload=destination   -upon recvieving a connection upload a file and write to [destination] ")
    print ()
    print ()
    print ("Here is an example:")
    print ()
    print ("bhpnet.py -t 192.163.153.1 -p 80 -l -c")
    print ("bhpnet.py -t 192.163.153.1 -p 80 -l -e \"cat /etc/passwd\"")
    print ("bhpnet.py -t 192.163.153.1 -p 80 -l -u =c:\\target.exe")
    print ("echo 'ABCDEFG' |./bhpnet.py -t 192.163.153.1 -p 80")
    sys.exit(0)
    
usage()
    
    