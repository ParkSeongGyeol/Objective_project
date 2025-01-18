#define _WINSOCK_DEPRECATED_NO_WARNINGS // winsock c4996 처리

#include <iostream>
#include <winsock2.h>
#include <thread>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // ws2_32.lib 라이브러리를 링크
#define PACKET_SIZE 1024 // 송수신 버퍼 사이즈 1024로 설정
SOCKET server_socket;

void proc_recv() {
	char buffer[PACKET_SIZE] = {}; //char 생성
	while (!WSAGetLastError()) {
		ZeroMemory(&buffer, PACKET_SIZE); //buffer 비우기
		recv(server_socket, buffer, PACKET_SIZE, 0); //데이터받아오기
		cout << "받은 메세지: " << buffer << endl;
	}
}

int main() {
	WSADATA wsa; // Windows 소켓 구현에 대한 구조체 생성

	// WSAStartup을 통해 wsadata 초기화
	// MAKEWORD(2,2) 매개 변수는 시스템에서 Winsock 버전 2.2를 요청
	// WSAStartup은 성공시 0, 실패시 SOCKET_ERROR를 리턴하므로
	// 리턴값이 0인지 검사하여 에러 여부 확인
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		std::cout << "WSAStartup failed" << endl;
		return 1;
	}

	// 클라이언트에서 접속할 서버 소켓 생성
	server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 주소 패밀리, IP 주소 및 포트 번호에 대한 정보를 보유할 sockaddr 구조체 생성
	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4444);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// 서버의 IP 설정. 서버가 클라이언트와 동일한 IP에서 실행되므로 여기서는 loopback 설정

	while (1) { // 서버 소켓에 대해 반복 연결 시도, 연결 성공 시 break
		if (!connect(server_socket, (SOCKADDR*)&addr, sizeof(addr))) break;
	}

	// server로부터 메세지를 수신하는 함수를 thread에 등록
	thread proc1(proc_recv);

	char msg[PACKET_SIZE] = { 0 }; // 메세지 입력받을 버퍼 생성
	while (!WSAGetLastError()) {
		ZeroMemory(&msg, PACKET_SIZE); // 버퍼 초기화하고, 입력받은 메세지를 서버에게 send
		cin >> msg;
		send(server_socket, msg, strlen(msg), 0);
	}

	proc1.join(); // 실행중인 thread의 작업 완료될때까지 대기

	closesocket(server_socket); // client socket 닫기

	WSACleanup(); // 리소스 해제
	return 0;
}