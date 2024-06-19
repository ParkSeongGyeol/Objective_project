#define _WINSOCK_DEPRECATED_NO_WARNINGS // winsock c4996 ó��

#include "UserManager.h"
#include "GameSelector.h"
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

void gameMenu() {
    cout << "===============================" << endl;
    cout << "=                             =" << endl;
    cout << "=        ���� ���� ��..       =" << endl;
    cout << "=                             =" << endl;
    cout << "===============================" << endl;
    GameSelector gameSelector;
    gameSelector.run();
}

void chatMenu() {
    cout << "===============================" << endl;
    cout << "=                             =" << endl;
    cout << "=        ä�� ������..        =" << endl;
    cout << "=                             =" << endl;
    cout << "===============================" << endl;
    
    WSADATA wsa; // Windows ���� ������ ���� ����ü ����

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cout << "WSAStartup failed" << endl;
        return ;
    }

    // Ŭ���̾�Ʈ���� ������ ���� ���� ����
    server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // �ּ� �йи�, IP �ּ� �� ��Ʈ ��ȣ�� ���� ������ ������ sockaddr ����ü ����
    SOCKADDR_IN addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // ������ IP ����. ������ Ŭ���̾�Ʈ�� ������ IP���� ����ǹǷ� ���⼭�� loopback ����

    while (1) { // ���� ���Ͽ� ���� �ݺ� ���� �õ�, ���� ���� �� break
        if (!connect(server_socket, (SOCKADDR*)&addr, sizeof(addr))) break;
    }

    // server�κ��� �޼����� �����ϴ� �Լ��� thread�� ���
    thread proc1(proc_recvs);

    char msg[PACKET_SIZE] = { 0 }; // �޼��� �Է¹��� ���� ����
    while (!WSAGetLastError()) {
        ZeroMemory(&msg, PACKET_SIZE); // ���� �ʱ�ȭ�ϰ�, �Է¹��� �޼����� �������� send
        cin >> msg;
        send(server_socket, msg, strlen(msg), 0);
    }

    proc1.join(); // �������� thread�� �۾� �Ϸ�ɶ����� ���

    closesocket(server_socket); // client socket �ݱ�

    WSACleanup(); // ���ҽ� ����
    
}

int main() {
    UserManager userManager;
    static int num;

    while (true) {
        cout << "===============================" << endl;
        cout << "=                             =" << endl;
        cout << "=         1. ȸ�� ����        =" << endl;
        cout << "=                             =" << endl;
        cout << "=         2. ȸ�� ����        =" << endl;
        cout << "=                             =" << endl;
        cout << "=         3. ȸ�� Ż��        =" << endl;
        cout << "=                             =" << endl;
        cout << "=         4. ���̵� ã��      =" << endl;
        cout << "=                             =" << endl;
        cout << "=         5. ��й�ȣ ã��    =" << endl;
        cout << "=                             =" << endl;
        cout << "=         6. �α���           =" << endl;
        cout << "=                             =" << endl;
        cout << "=         7. ������           =" << endl;
        cout << "=                             =" << endl;
        cout << "=     ��ȣ�� �Է����ּ���     =" << endl;
        cout << "===============================" << endl;

        // �Է� ���۸� �����ϰ�, ���ڰ� �ƴ� �Է��� ������ ���� ó��
        if (!(cin >> num)) {
            cout << "���ڸ� �Է����ּ���." << endl;
            cin.clear(); // �Է� ���� ����
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ����
            continue; // ���� �����
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
                        cout << "=         1. ����             =" << endl;
                        cout << "=                             =" << endl;
                        cout << "=         2. ä��             =" << endl;
                        cout << "=                             =" << endl;
                        cout << "=         3. �α׾ƿ�         =" << endl;
                        cout << "=                             =" << endl;
                        cout << "=     ��ȣ�� �Է����ּ���     =" << endl;
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
                            cout << "�α׾ƿ��մϴ�..." << endl;
                            break;
                        }
                        else{
                            cerr << "�߸� �Է��ϼ̽��ϴ�. ���ڸ� �ٽ� �Է����ּ���." << endl;
                            continue;
                        }
                    }
                }
                break;
            case 7:
                return 0;

            default:
                std::cerr << "�� �� �Է��ϼ̽��ϴ� ���ڸ� �ٽ� �Է����ּ���." << std::endl;
                continue;
            }
        }
    }
    closesocket(client_socket);
    closesocket(server_socket);

    WSACleanup();

    return 0;
}

