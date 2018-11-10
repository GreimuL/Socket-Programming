#include<iostream>
#include<string>
#include<WinSock2.h>
#include<conio.h>

#pragma comment(lib,"wsock32.lib")

using namespace std;

int main() {
	cout << "THIS IS CLIENT\n\n";
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET sk = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;

	serv_addr.sin_family = PF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(10000);

	if (connect(sk, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
		cout << "Connect Error";
		return 0;
	}

	cout << "Connect Success!\n";

	char msgdata[30];
	cout << "Send Msg : ";
	cin.getline(msgdata, 30);
	cout << "I send \"" << msgdata<<"\"" << endl;
	send(sk, (char*)&msgdata, sizeof(msgdata), 0);

	int recvdata;
	recv(sk, (char*)&recvdata, 4, 0);
	cout <<"Receive data : "<< recvdata << endl;
	closesocket(sk);
	WSACleanup();
	return 0;
}