#include "UserCreate.h"
#include "UserDelete.h"
#include "UserChange.h"
#include "FindUserId.h"
#include "FindUserPW.h"
#include "Login.h"
#include <iostream>
using namespace std;

void gameMenu() {
    cout << "===============================" << endl;
    cout << "=                             =" << endl;
    cout << "=         ���� �޴�           =" << endl;
    cout << "=                             =" << endl;
    cout << "===============================" << endl;
    cout << "������ �����մϴ�..." << endl;
    // ���� ���� �ڵ� �߰�
}

void chatMenu() {
    cout << "===============================" << endl;
    cout << "=                             =" << endl;
    cout << "=         ä�� �޴�           =" << endl;
    cout << "=                             =" << endl;
    cout << "===============================" << endl;
    cout << "ä���� �����մϴ�..." << endl;
    // ä�� ���� �ڵ� �߰�
}

int main() {
    
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
                registerUser();
                break;
            case 2:
                updateUser();
                break;
            case 3:
                deleteUser();
                break;
            case 4:
                findUserID();
                break;
            case 5:
                findUserPW();
                break;
            case 6:
                if (loginUser()) {
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

                        switch (choice) {
                        case 1:
                            gameMenu();
                            break;
                        case 2:
                            chatMenu();
                            break;
                        case 3:
                            cout << "�α׾ƿ��մϴ�..." << endl;
                            break;
                        default:
                            cerr << "�߸� �Է��ϼ̽��ϴ�. ���ڸ� �ٽ� �Է����ּ���." << endl;
                            continue;
                        }

                        if (choice == 3) {
                            break; // �α׾ƿ��� �����ϸ� ���� ����
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
    return 0;
}
