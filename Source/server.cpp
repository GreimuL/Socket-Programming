#include<iostream>
#include<string>
#include<conio.h>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

int main() {
	cout << "THIS IS SERVER\n\n";

	WSADATA wsaData;	
	struct sockaddr_in sv_addr;
	struct sockaddr_in addr;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sk = socket(PF_INET, SOCK_STREAM, 0);

	sv_addr.sin_family = PF_INET;
	sv_addr.sin_port = htons(10000);
	sv_addr.sin_addr.s_addr = htonl(ADDR_ANY);

	if (bind(sk, (struct sockaddr*)&sv_addr, sizeof(sv_addr))==SOCKET_ERROR) {
		cout << "Connect Error (in bind)\n";
		return 0;
	}
	if (!listen(sk, 2)) {
		cout << "Waiting Connection...\n";
	}
	cout << "Waiting Connection...\n";

	int addrsize = sizeof(addr);

	SOCKET as = accept(sk, (struct sockaddr*) &addr,&addrsize);

	if (as == INVALID_SOCKET) {
		cout << "Connect Error (in accept)\n";
		return 0;
	}

	cout << "Connect Success!\n";
	cout << inet_ntoa(addr.sin_addr) << " " << ntohs(addr.sin_port)<<endl;

	char recvdata[30];
	recv(as, (char*)&recvdata, sizeof(recvdata), 0);
	cout <<"Receive data : "<< recvdata <<"\n";
	int senddata = 20171356;
	send(as, (char*)&senddata, 4, 0);
	cout << "I Send data \"" << senddata<<"\"" << endl;
	closesocket(sk);
	WSACleanup();

	return 0;
}