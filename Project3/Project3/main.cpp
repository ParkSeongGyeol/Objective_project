#include "UserManager.h"
#include "GameSelector.h"
#include <iostream>
using namespace std;

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
    // 채팅 관련 코드 추가
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

                        switch (choice) {
                        case 1:
                            gameMenu();
                            break;
                        case 2:
                            chatMenu();
                            break;
                        case 3:
                            cout << "로그아웃합니다..." << endl;
                            break;
                        default:
                            cerr << "잘못 입력하셨습니다. 숫자를 다시 입력해주세요." << endl;
                            continue;
                        }

                        if (choice == 3) {
                            break; // 로그아웃을 선택하면 루프 종료
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
    return 0;
}

