#define _WINSOCK_DEPRECATED_NO_WARNINGS // winsock c4996 처리

#include "UserManager.h"
#include "GameSelector.h"
#include <iostream>
#include <winsock2.h>
#include <thread>
using namespace std;

#pragma comment(lib,"ws2_32.lib") // ws2_32.lib 라이브러리를 링크

#define PORT 4444
#define PACKET_SIZE 1024 // 송수신 버퍼 사이즈 1024로 설정

SOCKET server_socket, client_socket;

void proc_recvs() {
    char buffer[PACKET_SIZE] = { 0 };

    while (!WSAGetLastError()) {
        ZeroMemory(&buffer, PACKET_SIZE); // 버퍼 초기화
        recv(client_socket, buffer, PACKET_SIZE, 0);
        cout << "받은 메세지: " << buffer << endl;
    }
}

void gameMenu() {
    cout << "===============================" << endl;
    cout << "=                             =" << endl;
    cout << "=        게임 실행 중..       =" << endl;
    cout << "=                             =" << endl;
    cout << "===============================" << endl;
    GameSelector gameSelector;
    gameSelector.run();
}

void chatMenu() {
    cout << "===============================" << endl;
    cout << "=                             =" << endl;
    cout << "=        채팅 실행중..        =" << endl;
    cout << "=                             =" << endl;
    cout << "===============================" << endl;
    
    WSADATA wsa; // Windows 소켓 구현에 대한 구조체 생성

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cout << "WSAStartup failed" << endl;
        return ;
    }

    // 클라이언트에서 접속할 서버 소켓 생성
    server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // 주소 패밀리, IP 주소 및 포트 번호에 대한 정보를 보유할 sockaddr 구조체 생성
    SOCKADDR_IN addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // 서버의 IP 설정. 서버가 클라이언트와 동일한 IP에서 실행되므로 여기서는 loopback 설정

    while (1) { // 서버 소켓에 대해 반복 연결 시도, 연결 성공 시 break
        if (!connect(server_socket, (SOCKADDR*)&addr, sizeof(addr))) break;
    }

    // server로부터 메세지를 수신하는 함수를 thread에 등록
    thread proc1(proc_recvs);

    char msg[PACKET_SIZE] = { 0 }; // 메세지 입력받을 버퍼 생성
    while (!WSAGetLastError()) {
        ZeroMemory(&msg, PACKET_SIZE); // 버퍼 초기화하고, 입력받은 메세지를 서버에게 send
        cin >> msg;
        send(server_socket, msg, strlen(msg), 0);
    }

    proc1.join(); // 실행중인 thread의 작업 완료될때까지 대기

    closesocket(server_socket); // client socket 닫기

    WSACleanup(); // 리소스 해제
    
}

int main() {
    UserManager userManager;
    static int num;

    while (true) {
        cout << "===============================" << endl;
        cout << "=                             =" << endl;
        cout << "=         1. 회원 가입        =" << endl;
        cout << "=                             =" << endl;
        cout << "=         2. 회원 변경        =" << endl;
        cout << "=                             =" << endl;
        cout << "=         3. 회원 탈퇴        =" << endl;
        cout << "=                             =" << endl;
        cout << "=         4. 아이디 찾기      =" << endl;
        cout << "=                             =" << endl;
        cout << "=         5. 비밀번호 찾기    =" << endl;
        cout << "=                             =" << endl;
        cout << "=         6. 로그인           =" << endl;
        cout << "=                             =" << endl;
        cout << "=         7. 나가기           =" << endl;
        cout << "=                             =" << endl;
        cout << "=     번호를 입력해주세요     =" << endl;
        cout << "===============================" << endl;

        // 입력 버퍼를 정리하고, 숫자가 아닌 입력이 들어오면 오류 처리
        if (!(cin >> num)) {
            cout << "숫자를 입력해주세요." << endl;
            cin.clear(); // 입력 상태 복구
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기
            continue; // 루프 재시작
        }

        {
            switch (num)
            {
            case 1:
                userManager.registerUser();
                break;
            case 2:
                userManager.updateUser();
                break;
            case 3:
                userManager.deleteUser();
                break;
            case 4:
                userManager.findUserID();
                break;
            case 5:
                userManager.findUserPW();
                break;
            case 6:
                if (userManager.loginUser()) {
                    while (true) {
                        cout << "===============================" << endl;
                        cout << "=                             =" << endl;
                        cout << "=         1. 게임             =" << endl;
                        cout << "=                             =" << endl;
                        cout << "=         2. 채팅             =" << endl;
                        cout << "=                             =" << endl;
                        cout << "=         3. 로그아웃         =" << endl;
                        cout << "=                             =" << endl;
                        cout << "=     번호를 입력해주세요     =" << endl;
                        cout << "===============================" << endl;

                        int choice;
                        cin >> choice;

                        if (choice == 1) {
                            gameMenu();
                            break;
                        }
                        if (choice == 2) {
                            chatMenu();
                            break;
                        }
                        if (choice == 3) {
                            cout << "로그아웃합니다..." << endl;
                            break;
                        }
                        else{
                            cerr << "잘못 입력하셨습니다. 숫자를 다시 입력해주세요." << endl;
                            continue;
                        }
                    }
                }
                break;
            case 7:
                return 0;

            default:
                std::cerr << "잘 못 입력하셨습니다 숫자를 다시 입력해주세요." << std::endl;
                continue;
            }
        }
    }
    closesocket(client_socket);
    closesocket(server_socket);

    WSACleanup();

    return 0;
}

