#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

void CheckError(string msg)
{
	cout << "���� �߻� " << endl;
	system("pause");
	exit(1);
}

int main()
{
	cout << "hi" << endl;
	WSADATA wsaData; //���� �ʱ�ȭ ����ü 
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddress, clientAddress;

	int serverPort = 9876;
	char received[256];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		CheckError("WSAStartUp");
	}

	serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (serverSocket == INVALID_SOCKET)
		CheckError("socket()");

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(serverPort);

	if (bind(serverSocket, (SOCKADDR *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
	{
		CheckError("bind");
	}

	cout << "���� ���� bind()" << endl;

	if (listen(serverSocket, 5) == SOCKET_ERROR)
	{
		CheckError("Listen");
	}

	cout << "���� ���� Listen";

	int sizeclientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR *)&clientAddress, &sizeclientAddress);
	cout << "���� ���� accept" << endl;

	if (clientSocket == INVALID_SOCKET)
		CheckError("accept");

	while (1)
	{
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;
		cout << "Ŭ���̾�Ʈ �޽��� : " << received << endl;
		cout << "�޽��� ���� : " << received << endl;

		if (strcmp(received, "exit") == 0)
		{
			send(clientSocket, received, sizeof(received) - 1, 0);
			cout << "���� ����" << endl;
			break;
		}

		send(clientSocket, received, sizeof(received) - 1, 0);

	}

	closesocket(clientSocket);
	closesocket(serverSocket);

	WSACleanup();
	system("pause");

	return 0;
}