#define _WINSOCK_DEPRECATED_NO_WARNINGS // winsock c4996 ó��

#include <iostream>
#include <winsock2.h>
#include <thread>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // ws2_32.lib ���̺귯���� ��ũ
#define PACKET_SIZE 1024 // �ۼ��� ���� ������ 1024�� ����
SOCKET server_socket;

void proc_recv() {
	char buffer[PACKET_SIZE] = {}; //char ����
	while (!WSAGetLastError()) {
		ZeroMemory(&buffer, PACKET_SIZE); //buffer ����
		recv(server_socket, buffer, PACKET_SIZE, 0); //�����͹޾ƿ���
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

	// Ŭ���̾�Ʈ���� ������ ���� ���� ����
	server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// �ּ� �йи�, IP �ּ� �� ��Ʈ ��ȣ�� ���� ������ ������ sockaddr ����ü ����
	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4444);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// ������ IP ����. ������ Ŭ���̾�Ʈ�� ������ IP���� ����ǹǷ� ���⼭�� loopback ����

	while (1) { // ���� ���Ͽ� ���� �ݺ� ���� �õ�, ���� ���� �� break
		if (!connect(server_socket, (SOCKADDR*)&addr, sizeof(addr))) break;
	}

	// server�κ��� �޼����� �����ϴ� �Լ��� thread�� ���
	thread proc1(proc_recv);

	char msg[PACKET_SIZE] = { 0 }; // �޼��� �Է¹��� ���� ����
	while (!WSAGetLastError()) {
		ZeroMemory(&msg, PACKET_SIZE); // ���� �ʱ�ȭ�ϰ�, �Է¹��� �޼����� �������� send
		cin >> msg;
		send(server_socket, msg, strlen(msg), 0);
	}

	proc1.join(); // �������� thread�� �۾� �Ϸ�ɶ����� ���

	closesocket(server_socket); // client socket �ݱ�

	WSACleanup(); // ���ҽ� ����
	return 0;
}