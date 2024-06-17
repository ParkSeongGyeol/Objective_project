#include "UserCreate.h"
#include "Login.h"
#include "utils.h"
#include <iostream>
#include <regex>



    // 사용자를 로그인하는 함수
    bool loginUser() {
        std::vector<User> users = loadUsers();
        std::string userID;
        std::string userPW;

        std::cout << "아이디를 입력해주세요 : ";
        std::cin >> userID;
        if (!isValidIDorPW(userID)) {
            std::cerr << "올바른 형식의 아이디를 입력해주세요 (영어, 숫자, 기호 사용 가능)." << std::endl;
            return false;
        }

        std::cout << "비밀번호를 입력해주세요 : ";
        std::cin >> userPW;
        if (!isValidIDorPW(userPW)) {
            std::cerr << "올바른 형식의 비밀번호를 입력해주세요 (영어, 숫자, 기호 사용 가능)." << std::endl;
            return false;
        }

        auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
            return user.userID == userID && user.userPW == userPW;
            });

        if (it != users.end()) {
            std::cout << "성공적으로 로그인 되셨습니다." << std::endl;
            return true;
        }
        else {
            std::cerr << "유효하지 않은 아이디 또는 비밀번호 입니다." << std::endl;
            return false;
        }
    }
