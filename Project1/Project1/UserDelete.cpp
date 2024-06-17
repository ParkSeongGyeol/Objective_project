#include "UserCreate.h"
#include "UserDelete.h"
#include "utils.h"
#include <iostream>
#include <fstream>



    // 사용자를 삭제하는 함수
    void deleteUser() {
        std::vector<User> users = loadUsers();
        std::string userID, userPW;
        std::cout << "탈퇴를 위한 회원님의 아이디를 입력해주세요 : ";
        std::cin >> userID;
        std::cout << "비밀번호를 입력해주세요 : ";
        std::cin >> userPW;

        auto it = std::remove_if(users.begin(), users.end(), [&](const User& user) {
            return user.userID == userID && user.userPW == userPW;
            });

        if (it == users.end()) {
            std::cerr << "유효하지 않은 아이디 또는 비밀번호입니다." << std::endl;
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
            std::cout << "성공적으로 회원탈퇴가 되셨습니다." << std::endl;
        }
        else {
            std::cerr << "데이터를 업데이트하는데 문제가 발생했습니다." << std::endl;
        }
    }
