#include "UserCreate.h"
#include "FindUserID.h"
#include "utils.h"
#include <iostream>
#include <regex>

    // 아이디를 찾는 함수
    void findUserID() {

        std::vector<User> users = loadUsers();
        std::string name, birthdate, phone;

        std::cout << "이름을 입력해주세요 : ";
        std::cin >> name;

        std::cout << "생년월일을 입력해주세요 (YYYYMMDD): ";
        std::cin >> birthdate;
        if (!isValidBirthdate(birthdate)) {
            std::cerr << "올바른 형식의 생년월일을 입력해주세요 (8자리 숫자)." << std::endl;
            return;
        }

        std::cout << "전화번호를 입력해주세요 : ";
        std::cin >> phone;
        if (!isValidPhone(phone)) {
            std::cerr << "올바른 형식의 전화번호를 입력해주세요 (11자리 숫자)." << std::endl;
            return;
        }

        auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
            return user.name == name && user.birthdate == birthdate && user.phone == phone;
            });

        if (it != users.end()) {
            std::cout << "회원님의 아이디는 : " << it->userID << " 입니다." << std::endl;
        }
        else {
            std::cerr << "회원을 찾을 수 없습니다." << std::endl;
        }
    }