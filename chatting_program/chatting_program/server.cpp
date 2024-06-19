#define _WINSOCK_DEPRECATED_NO_WARNINGS // winsock c4996 ó��

#include <iostream>
#include <winsock2.h>
#include <thread>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // ws2_32.lib ���̺귯���� ��ũ

#define PORT 4444
#define PACKET_SIZE 1024 // �ۼ��� ���� ������ 1024�� ����

SOCKET server_socket, client_socket;


void proc_recvs() {
	char buffer[PACKET_SIZE] = { 0 };

	while (!WSAGetLastError()) {
		ZeroMemory(&buffer, PACKET_SIZE); // ���� �ʱ�ȭ
		recv(client_socket, buffer, PACKET_SIZE, 0);
		cout << "���� �޼���: " << buffer << endl;
	}
}

int main() {
	WSADATA wsa; // Windows ���� ������ ���� ����ü ����

	// WSAStartup�� ���� wsadata �ʱ�ȭ
	// MAKEWORD(2,2) �Ű� ������ �ý��ۿ��� Winsock ���� 2.2�� ��û
	// WSAStartup�� ������ 0, ���н� SOCKET_ERROR�� �����ϹǷ�
	// ���ϰ��� 0���� �˻��Ͽ� ���� ���� Ȯ��
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		std::cout << "WSAStartup failed" << endl;
		return 1;
	}

	// ������ Ŭ���̾�Ʈ ������ ���� ����� �� �ֵ��� ���� ����
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// �ּ� �йи�, IP �ּ� �� ��Ʈ ��ȣ�� ���� ������ ������ sockaddr ����ü ����
	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET; // IPv4 ����� TCP, UDP �������� ���
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// bind �Լ��� ���� ������ ���� �� sockaddr ������ �Ű� ������ ����
	bind(server_socket, (SOCKADDR*)&addr, sizeof(addr));
	listen(server_socket, SOMAXCONN); // ���Ͽ��� ���� ���
	// SOMAXCONN�� Winsock �����ڿ��� ť�� �ִ� �ִ� ���� ���� ���� ���� ������ ����ϵ��� �����ϴ� Ư�� ���

	SOCKADDR_IN client = {};
	int client_size = sizeof(client);

	// Ŭ���̾�Ʈ���� ������ �����ϱ� ���� ClientSocket�̶�� �ӽ� ���� ��ü ����
	client_socket = accept(server_socket, (SOCKADDR*)&client, &client_size);

	if (!WSAGetLastError()) {
		std::cout << "���� �Ϸ�" << endl;
		std::cout << "Client IP: " << inet_ntoa(client.sin_addr) << endl;
		std::cout << "Port: " << ntohs(client.sin_port) << endl;
	}

	// client�κ��� �޼����� �����ϴ� �Լ��� thread�� ���
	thread proc2(proc_recvs);

	char msg[PACKET_SIZE] = { 0 };
	while (!WSAGetLastError()) {
		ZeroMemory(&msg, PACKET_SIZE);
		cin >> msg;
		send(client_socket, msg, strlen(msg), 0);
	}
	proc2.join();

	closesocket(client_socket);
	closesocket(server_socket);

	WSACleanup();

	return 0;
}

