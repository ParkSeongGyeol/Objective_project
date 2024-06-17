#include "UserCreate.h"
#include "UserDelete.h"
#include "utils.h"
#include <iostream>
#include <fstream>



    // ����ڸ� �����ϴ� �Լ�
    void deleteUser() {
        std::vector<User> users = loadUsers();
        std::string userID, userPW;
        std::cout << "Ż�� ���� ȸ������ ���̵� �Է����ּ��� : ";
        std::cin >> userID;
        std::cout << "��й�ȣ�� �Է����ּ��� : ";
        std::cin >> userPW;

        auto it = std::remove_if(users.begin(), users.end(), [&](const User& user) {
            return user.userID == userID && user.userPW == userPW;
            });

        if (it == users.end()) {
            std::cerr << "��ȿ���� ���� ���̵� �Ǵ� ��й�ȣ�Դϴ�." << std::endl;
            return;
        }

        users.erase(it, users.end());

        std::ofstream file("users.txt", std::ios::trunc);
        if (file.is_open()) {
            for (const auto& user : users) {
                file << user.userID << "\t"
                    << user.userPW << "\t"
                    << user.email << "\t"
                    << user.name << "\t"
                    << user.birthdate << "\t"
                    << user.phone << "\t"
                    << user.gender << "\n";
            }
            file.close();
            std::cout << "���������� ȸ��Ż�� �Ǽ̽��ϴ�." << std::endl;
        }
        else {
            std::cerr << "�����͸� ������Ʈ�ϴµ� ������ �߻��߽��ϴ�." << std::endl;
        }
    }
