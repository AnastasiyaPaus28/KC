//Лабораторная №4, вариант 7, Паус Анастасия
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <windows.h>
#include <iostream>
using namespace std;

#pragma warning (disable: 4996)
SOCKET client;
int main() {
	setlocale(LC_ALL, "Russian");

	WSAData wsaData;
	WORD version = MAKEWORD(2, 2);
	if (WSAStartup(version, &wsaData) != 0) {
		cout << "Ошибка!" << WSAGetLastError() << endl;
		system("pause");
		return -1;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(110);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	client = socket(AF_INET, SOCK_STREAM, NULL);
	if (client == INVALID_SOCKET) {
		cout << "Error: " << WSAGetLastError() << endl;
		return -1;
	}

	int connection = 0;

	char msg[400];
	int sizeMsg = 0;

	
	connection = connect(client, (sockaddr*)& addr, sizeof(addr));
	if (connection == SOCKET_ERROR) {
		cout << "Ошибка: " << WSAGetLastError() << endl;
		return -1;
	}
	cout << "connected!\n";
	sizeMsg = recv(client, msg, sizeof(msg), NULL);
	msg[sizeMsg] = 0;
	cout << msg << endl;

	strcat(msg, "\r\n");
	int sizestr = 0;

	while (true)
	{
		int comand = 0;
		cout << "1.Вход.   2.Просмотр количества сообщений.   3.Удалить сообщение   4.Смена пользователя   5.Выход из программы\n";
		cin >> comand;
		switch (comand)
		{
		case 1:
			cout << "user: ";
			strcpy(msg, "user ");
			char name[255];
			cin >> name;
			strcat(msg, name);
			strcat(msg, "\r\n");
			send(client, msg, sizeof(msg), 0);
			cout << "password: ";
			strcpy(msg, "pass ");
			char pass[255];
			cin >> pass;
			strcat(msg, pass);
			strcat(msg, "\r\n");
			send(client, msg, sizeof(msg), 0);
			ZeroMemory(msg, sizeof(msg));
			recv(client, msg, sizeof(msg), 0);
			cout << msg << endl;
			break;
		case 2:
			ZeroMemory(msg, sizeof(msg));
			strcpy(msg, "list");
			strcat(msg, "\r\n");
			send(client, msg, sizeof(msg), 0);
			ZeroMemory(msg, sizeof(msg));
			recv(client, msg, sizeof(msg), 0);
			cout << msg << endl;
			break;
		case 3:
			ZeroMemory(msg, sizeof(msg));
			strcpy(msg, "dele ");
			char nomber[10];
			cin >> nomber;
			strcat(msg, nomber);
			strcat(msg, "\r\n");
			send(client, msg, sizeof(msg), 0);
			Sleep(1000);
			ZeroMemory(msg, sizeof(msg));
			recv(client, msg, sizeof(msg), 0);
			cout << msg << endl;
			Sleep(1000);
			break;
		case 4:
			strcpy(msg, "quit\r\n");
			send(client, msg, sizeof(msg), 0);
			ZeroMemory(msg, sizeof(msg));
			recv(client, msg, sizeof(msg), 0);
			cout << msg << endl;
			closesocket(client);
			break;
		case 5:
			closesocket(client);
			Sleep(400);
			return 0;
		default:
			cout << "Введена не верная команда\n";
			break;
		
		
		}
	}

	system("pause");
	return 0;
}