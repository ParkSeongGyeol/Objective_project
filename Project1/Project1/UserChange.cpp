#include "UserCreate.h"
#include "UserChange.h"
#include <iostream>
#include <fstream>
#include <regex> // 정규 표현식 사용을 위한 헤더 추가
using namespace std;

bool isValidIDorPW(const std::string& str) {
    // 정규 표현식으로 영어, 숫자, 기호만 포함하는지 검사
    const std::regex pattern(R"([A-Za-z0-9._%+-]+)");
    return std::regex_match(str, pattern);
}

// 정규 표현식을 사용하여 입력 형식을 검사하는 함수들
bool isValidEmail(const std::string& email) {
    // 이메일 형식 검사 정규 표현식
    const std::regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
    return std::regex_match(email, pattern);
}

bool isValidPhone(const std::string& phone) {
    // 전화번호 형식 검사 정규 표현식
    const std::regex pattern(R"(\d{11})");
    return std::regex_match(phone, pattern);
}

bool isValidBirthdate(const std::string& birthdate) {
    // 생년월일 형식 검사 정규 표현식
    const std::regex pattern(R"(\d{8})");
    return std::regex_match(birthdate, pattern);
}

bool isValidGender(const std::string& gender) {
    // 성별 형식 검사
    return gender == "남자" || gender == "여자";
}

// 사용자를 업데이트하는 함수
void updateUser() {
    std::vector<User> users = loadUsers();
    std::string userID, userPW;
    std::cout << "아이디를 입력해주세요 : ";
    std::cin >> userID;
    std::cout << "비밀번호를 입력해주세요 : ";
    std::cin >> userPW;

    auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
        return user.userID == userID && user.userPW == userPW;
        });

    if (it == users.end()) {
        std::cerr << "유효하지 않은 아이디 또는 비밀번호 입니다." << std::endl;
        return;
    }

    User& userToUpdate = *it;
    int choice;

    while (true) {
        std::cout << "무엇을 변경하시겠습니까?:\n";
        std::cout << "1. 이메일\n";
        std::cout << "2. 비밀번호\n";
        std::cout << "3. 이름\n";
        std::cout << "4. 생년월일\n";
        std::cout << "5. 전화번호\n";
        std::cout << "6. 성별\n";
        std::cout << "7. 메인 메뉴로 돌아가기\n";
        std::cout << "번호를 선택 해주세요.: ";
        std::cin >> choice;

        if (choice == 7) {
            break;
        }

        switch (choice) {
        case 1: {
            std::cout << "변경할 이메일을 입력해주세요 : ";
            std::string newEmail;
            std::cin >> newEmail;
            if (!isValidEmail(newEmail)) {
                std::cerr << "올바른 이메일 형식이 아닙니다. 다시 입력해주세요." << std::endl;
            }
            else {
                userToUpdate.email = newEmail;
                std::cout << "이메일이 성공적으로 변경되었습니다." << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "변경할 비밀번호를 입력해주세요 : ";
            std::string newPassword;
            std::cin >> newPassword;
            if (!isValidIDorPW(newPassword)) {
                std::cerr << "올바른 형식의 비밀번호를 입력해주세요 (영어, 숫자, 기호 사용 가능)." << std::endl;
            }
            else {
                userToUpdate.userPW = newPassword;
                std::cout << "비밀번호가 성공적으로 변경되었습니다." << std::endl;
            }
            break;
        }
        case 3:
            std::cout << "변경할 이름을 입력해주세요 : ";
            std::cin >> userToUpdate.name;
            std::cout << "이름이 성공적으로 변경되었습니다." << std::endl;
            break;
        case 4: {
            std::cout << "변경할 생년월일을 입력해주세요 (YYYYMMDD): ";
            std::string newBirthdate;
            std::cin >> newBirthdate;
            if (!isValidBirthdate(newBirthdate)) {
                std::cerr << "올바른 생년월일 형식이 아닙니다. 다시 입력해주세요." << std::endl;
            }
            else {
                userToUpdate.birthdate = newBirthdate;
                std::cout << "생년월일이 성공적으로 변경되었습니다." << std::endl;
            }
            break;
        }
        case 5: {
            std::cout << "변경할 전화번호를 입력해주세요 : ";
            std::string newPhone;
            std::cin >> newPhone;
            if (!isValidPhone(newPhone)) {
                std::cerr << "올바른 전화번호 형식이 아닙니다. 다시 입력해주세요." << std::endl;
            }
            else {
                userToUpdate.phone = newPhone;
                std::cout << "전화번호가 성공적으로 변경되었습니다." << std::endl;
            }
            break;
        }
        case 6: {
            std::cout << "변경할 성별을 입력해주세요 : ";
            std::string newGender;
            std::cin >> newGender;
            if (!isValidGender(newGender)) {
                std::cerr << "올바른 성별 형식이 아닙니다. '남자' 또는 '여자'로 입력해주세요." << std::endl;
            }
            else {
                userToUpdate.gender = newGender;
                std::cout << "성별이 성공적으로 변경되었습니다." << std::endl;
            }
            break;
        }
        default:
            std::cerr << "올바르지 않은 숫자 입니다. 다시 시도해주십시오." << std::endl;
            continue;
        }
    }

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
    }
    else {
        std::cerr << "유저의 데이터를 업데이트하는데 문제가 있습니다." << std::endl;
    }
}
