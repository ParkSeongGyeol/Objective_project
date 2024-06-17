#include "UserCreate.h"
#include "Login.h"
#include "utils.h"
#include <iostream>
#include <regex>



    // ����ڸ� �α����ϴ� �Լ�
    bool loginUser() {
        std::vector<User> users = loadUsers();
        std::string userID;
        std::string userPW;

        std::cout << "���̵� �Է����ּ��� : ";
        std::cin >> userID;
        if (!isValidIDorPW(userID)) {
            std::cerr << "�ùٸ� ������ ���̵� �Է����ּ��� (����, ����, ��ȣ ��� ����)." << std::endl;
            return false;
        }

        std::cout << "��й�ȣ�� �Է����ּ��� : ";
        std::cin >> userPW;
        if (!isValidIDorPW(userPW)) {
            std::cerr << "�ùٸ� ������ ��й�ȣ�� �Է����ּ��� (����, ����, ��ȣ ��� ����)." << std::endl;
            return false;
        }

        auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
            return user.userID == userID && user.userPW == userPW;
            });

        if (it != users.end()) {
            std::cout << "���������� �α��� �Ǽ̽��ϴ�." << std::endl;
            return true;
        }
        else {
            std::cerr << "��ȿ���� ���� ���̵� �Ǵ� ��й�ȣ �Դϴ�." << std::endl;
            return false;
        }
    }
