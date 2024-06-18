#include "UserManager.h"
#include "utils.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <regex>
using namespace std;


std::vector<User> UserManager::loadUsers() {
    std::vector<User> users;
    std::ifstream file("users.txt");
    if (file.is_open()) {
        User user;
        while (file >> user.userID >> user.userPW >> user.email >> user.name >> user.birthdate >> user.phone >> user.gender) {
            users.push_back(user);
        }
        file.close();
    }
    return users;
}


    // 아이디와 이메일 전화번호 중복을 검사하는 함수
bool UserManager::isUserExists(const vector<User>& users, const string& field, const string& value) {
    for (const auto& user : users) {
        if ((field == "userID" && user.userID == value) ||
            (field == "email" && user.email == value) ||
            (field == "phone" && user.phone == value)) {
            return true;
        }
    }
    return false;
}

    // 아이디, 비밀번호, 이메일, 전화번호, 생년월일, 성별 형식을 검사하는 함수
bool UserManager::isValidIDorID(const std::string& idOrID) {

    // 정규 표현식으로 영어, 숫자, 기호만 포함하는지 검사

    const std::regex pattern(R"([A-Za-z0-9._%+-]+)");
    return std::regex_match(idOrID, pattern);
}

bool UserManager::isValidIDorPW(const std::string& idOrPW) {
    // 영어 알파벳(대문자와 소문자)과 특수문자만 포함
    const std::regex pattern(R"(^[A-Za-z0-9!@#$%^&*()_+|~\-=?{}[\]:;"'<>,./]*$)");
    return std::regex_match(idOrPW, pattern);
}
    
bool UserManager::isValidEmail(const std::string& email) {

    // 이메일 형식 맞는지 검사

    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
    return std::regex_match(email, pattern);
}

bool UserManager::isValidPhone(const std::string& phone) {

    // 전화번호 형식 맞는지 검사

    const std::regex pattern(R"(\d{11})");
    return std::regex_match(phone, pattern);
}

bool UserManager::isValidBirthdate(const std::string& birthdate) {

    // 생년월일 형식 맞는지 검사

    const std::regex pattern(R"(\d{8})");
    return std::regex_match(birthdate, pattern);
}

bool UserManager::isValidGender(const std::string& gender) {

    // 성별 형식 맞는지 검사

    return gender == "남자" || gender == "여자";
}


// 로그인 구현
bool UserManager::loginUser() {

    std::vector<User> users = loadUsers();
    std::string userID;
    std::string userPW;

    while (true) {

        std::cout << "아이디를 입력해주세요 : ";
        std::cin >> userID;
        if (!isValidIDorID(userID)) {
            std::cerr << "올바른 형식의 아이디를 입력해주세요 (영어, 숫자, 기호만 . _ % + - 사용 가능)." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "비밀번호를 입력해주세요 : ";
        std::cin >> userPW;
        if (!isValidIDorPW(userPW)) {
            std::cerr << "올바른 형식의 비밀반호를 입력해주세요 (영어, 숫자, 기호 사용 가능)." << std::endl;
        }
        else {
            break;
        }
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

// 회원 삭제 구현
void UserManager::deleteUser() {

    std::vector<User> users = loadUsers();
    std::string userID, userPW;

    while (true)
    {
        std::cout << "탈퇴를 위한 회원님의 아이디를 입력해주세요 : ";
        std::cin >> userID;
        if (!isValidIDorID(userID)) {
            std::cerr << "올바른 형식의 아이디를 입력해주세요 (영어, 숫자, 기호 . _ % + - 사용 가능)." << std::endl;
        }
        else {
            break;
        }
    }
    
    while (true)
    {
        std::cout << "비밀번호를 입력해주세요 : ";
        std::cin >> userPW;
        if (!isValidIDorPW(userPW)) {
            std::cerr << "올바른 형식의 비밀번호를 입력해주세요 (영어, 숫자, 기호 사용 가능)." << std::endl;
        }
        else {
            break;
        }
    }


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

// 아이디 찾기 구현
void UserManager::findUserID() {

    std::vector<User> users = loadUsers();
    std::string name, birthdate, phone, email;

    std::cout << "이름을 입력해주세요 : ";
    std::cin >> name;


    while (true) {

        std::cout << "생년월일을 입력해주세요 (YYYYMMDD): ";
        std::cin >> birthdate;
        if (!isValidBirthdate(birthdate)) {
            std::cerr << "올바른 형식의 생년월일을 입력해주세요 (8자리 숫자)" << std::endl;
        }
        else {
            break;
        }
    }


    while (true) {
        std::cout << "이메일을 입력해주세요 : ";
        std::cin >> email;
        if (!isValidEmail(email)) {
            std::cerr << "올바른 형식의 이메일을 입력해주세요" << std::endl;
        }
        else {
            break;
        }
    }


    while (true) {

        std::cout << "전화번호를 입력해주세요 : ";
        std::cin >> phone;
        if (!isValidPhone(phone)) {
            std::cerr << "올바른 형식의 전화번호를 입력해주세요 (11자리 숫자)" << std::endl;
        }
        else {
            break;
        }
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

// 비밀번호 찾기 구현
void UserManager::findUserPW() {

    std::vector<User> users = loadUsers();
    std::string name, userID, phone, birthdate, email;

    std::cout << "이름을 입력하세요 : ";
    std::cin >> name;

    while (true) {
        std::cout << "아이디를 입력 해주세요 : ";
        std::cin >> userID;
        if (!isValidIDorID(userID)) {
            std::cerr << "올바른 형식의 아이디를 입력해주세요 (영어, 숫자, 기호 . _ % + - 사용 가능)." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {

        std::cout << "생년월일을 입력해주세요 (YYYYMMDD): ";
        std::cin >> birthdate;
        if (!isValidBirthdate(birthdate)) {
            std::cerr << "올바른 형식의 생년월일을 입력해주세요 (8자리 숫자)" << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "이메일을 입력해주세요 : ";
        std::cin >> email;
        if (!isValidEmail(email)) {
            std::cerr << "올바른 형식의 이메일을 입력해주세요" << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {

        std::cout << "전화번호를 입력해주세요 : ";
        std::cin >> phone;
        if (!isValidPhone(phone)) {
            std::cerr << "올바른 형식의 전화번호를 입력해주세요 (11자리 숫자)" << std::endl;
        }
        else {
            break;
        }
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

// 회원 생성 구현
void UserManager::registerUser() {
    std::vector<User> users = loadUsers();
    User newUser;

    std::cout << "회원 가입을 시작합니다." << std::endl;

    std::cout << "이름을 입력해주세요 : ";
    std::cin >> newUser.name;

    while (true) {
        std::cout << "아이디를 입력해주세요 : ";
        std::cin >> newUser.userID;
        if (!isValidIDorID(newUser.userID)) {
            std::cout << "올바른 형식의 아이디를 입력해주세요 (영어, 숫자, 기호 . _ % + - 만 사용 가능)" << std::endl;
        }
        else if (isUserExists(users, "userID", newUser.userID)) {
            std::cout << "아이디가 중복입니다. 다시 입력해주세요." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "비밀번호를 입력해주세요 : ";
        std::cin >> newUser.userPW;
        if (!isValidIDorPW(newUser.userPW)) {
            std::cout << "올바른 형식의 비밀번호를 입력해주세요 (영어, 숫자, 기호만 사용 가능)" << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "이메일을 입력해주세요 : ";
        std::cin >> newUser.email;
        if (!isValidEmail(newUser.email)) {
            std::cout << "올바른 이메일 형식이 아닙니다. 다시 입력해주세요." << std::endl;
        }
        else if (isUserExists(users, "email", newUser.email)) {
            std::cout << "이메일이 중복입니다. 다시 입력해주세요." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "생년월일을 입력해주세요 (8자리, YYYYMMDD): ";
        std::cin >> newUser.birthdate;
        if (!isValidBirthdate(newUser.birthdate)) {
            std::cout << "올바른 생년월일 형식이 아닙니다. 다시 입력해주세요." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "전화번호를 입력해주세요 (11자리, 숫자만): ";
        std::cin >> newUser.phone;
        if (!isValidPhone(newUser.phone)) {
            std::cout << "올바른 전화번호 형식이 아닙니다. 다시 입력해주세요." << std::endl;
        }
        else if (isUserExists(users, "phone", newUser.phone)) {
            std::cout << "전화번호가 중복입니다. 다시 입력해주세요." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "성별을 입력해주세요 (남자/여자): ";
        std::cin >> newUser.gender;
        if (!isValidGender(newUser.gender)) {
            std::cout << "올바른 성별 형식이 아닙니다. '남자' 또는 '여자'로 입력해주세요." << std::endl;
        }
        else {
            break;
        }
    }

    std::ofstream file("users.txt", std::ios::app);
    if (file.is_open()) {
        file << newUser.userID << " " << newUser.userPW << " " << newUser.email << " " << newUser.name << " " << newUser.birthdate << " " << newUser.phone << " " << newUser.gender << std::endl;
        file.close();
        std::cout << "회원 가입이 성공적으로 완료되었습니다!" << std::endl;
    }
    else {
        std::cerr << "파일을 열 수 없습니다." << std::endl;
    }
}

// 회원 변경 구현
void UserManager::updateUser() {

    std::vector<User> users = loadUsers();
    std::string userID, userPW;

    while (true)
    {
        std::cout << "회원변경을 위한 회원님의 아이디를 입력해주세요 : ";
        std::cin >> userID;
        if (!isValidIDorID(userID)) {
            std::cerr << "올바른 형식의 아이디를 입력해주세요 (영어, 숫자, 기호 사용 가능)." << std::endl;
        }
        else {
            break;
        }
    }

    while (true)
    {
        std::cout << "비밀번호를 입력해주세요 : ";
        std::cin >> userPW;
        if (!isValidIDorPW(userPW)) {
            std::cerr << "올바른 형식의 비밀번호를 입력해주세요 (영어, 숫자, 기호 사용 가능)." << std::endl;
        }
        else {
            break;
        }
    }

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
        std::cout << "무엇을 변경하시겠습니까? :\n";
        std::cout << " \n";
        std::cout << "1. 이메일\n";
        std::cout << " \n";
        std::cout << "2. 비밀번호\n";
        std::cout << " \n";
        std::cout << "3. 이름\n";
        std::cout << " \n";
        std::cout << "4. 생년월일\n";
        std::cout << " \n";
        std::cout << "5. 전화번호\n";
        std::cout << " \n";
        std::cout << "6. 성별\n";
        std::cout << " \n";
        std::cout << "7. 메인 메뉴로 돌아가기\n";
        std::cout << " \n";
        std::cout << "번호를 선택 해주세요 : ";
        std::cout << " \n";
        std::cout << " \n";
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
