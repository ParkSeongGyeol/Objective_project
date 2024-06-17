#include "UserCreate.h"
#include "FindUserPW.h"
#include "utils.h"
#include <iostream>
#include <regex>



    // 비밀번호를 찾는 함수
    void findUserPW() {
        std::vector<User> users = loadUsers();
        std::string name, userID, phone, birthdate;

        std::cout << "이름을 입력하세요 : ";
        std::cin >> name;

        std::cout << "아이디를 입력 해주세요 : ";
        std::cin >> userID;
        if (!isValidIDorPW(userID)) {
            std::cerr << "올바른 형식의 아이디를 입력해주세요 (영어, 숫자, 기호 사용 가능)." << std::endl;
            return;
        }

        std::cout << "전화번호를 입력해주세요 : ";
        std::cin >> phone;
        if (!isValidPhone(phone)) {
            std::cerr << "올바른 형식의 전화번호를 입력해주세요 (11자리 숫자)." << std::endl;
            return;
        }

        std::cout << "생년월일을 입력해주세요 (YYYYMMDD): ";
        std::cin >> birthdate;
        if (!isValidBirthdate(birthdate)) {
            std::cerr << "올바른 형식의 생년월일을 입력해주세요 (8자리 숫자)." << std::endl;
            return;
        }

        auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
            return user.name == name && user.userID == userID &&
                user.phone == phone && user.birthdate == birthdate;
            });

        if (it != users.end()) {
            std::cout << "회원님의 비밀번호는 : " << it->userPW << " 입니다." << std::endl;
        }
        else {
            std::cerr << "회원을 찾을 수 없거나 회원정보와 일치하지 않습니다." << std::endl;
        }
    }
