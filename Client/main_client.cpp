#include <iostream>
#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
using namespace std;

void CheckError(string msg)
{
	cout << "오류 발생 " << endl;
	system("pause");
	exit(1);
}

int main()
{
	WSADATA wsaData; //윈속 초기화 구조체 
	SOCKET  clientSocket;
	SOCKADDR_IN serverAddress;

	int serverPort = 9876;
	char received[256];
	string sent;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		CheckError("WSAStartUp");
	}

	// 소켓을 생성하자 
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (clientSocket == INVALID_SOCKET)
		CheckError("socket()");

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_port = htons(serverPort);

	//connect 작업 

	if (connect(clientSocket, (SOCKADDR *)&serverAddress, sizeof(serverAddress))
		== SOCKET_ERROR)
		CheckError("connect()");

	cout << "현재 상태 connect()";


	while (1)
	{
		cout << "메시지 전송 : ";
		getline(cin, sent);

		if (sent == "") continue;
		send(clientSocket, sent.c_str(), sent.length(), 0);
		int length = recv(clientSocket, received, sizeof(received) - 1, 0);

		if (strcmp(received, "exit") == 0)
		{
			cout << "서버 종료" << endl;
			break;
		}

		cout << "서버 메시지 : " << received << endl;
	}

	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}