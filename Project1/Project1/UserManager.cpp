#include "UserManager.h"
#include "utils.h"
#include <iostream>


void UserManger::registerUser() {

    vector<User> loadUsers() {
        vector<User> users;
        ifstream file("users.txt");
        if (file.is_open()) {
            User user;
            while (file >> user.userID >> user.userPW >> user.email >> user.name >> user.birthdate >> user.phone >> user.gender) {
                users.push_back(user);
            }
            file.close();
        }
        return users;
    }

    bool isUserExists(const vector<User>&users, const string & field, const string & value) {
        for (const auto& user : users) {
            if ((field == "userID" && user.userID == value) ||
                (field == "email" && user.email == value) ||
                (field == "phone" && user.phone == value)) {
                return true;
            }
        }
        return false;
    }

    void registerUser() {
        vector<User> users = loadUsers();
        User newUser;

        cout << "회원 가입을 시작합니다." << endl;

        cout << "이름을 입력해주세요 : ";
        cin >> newUser.name;

        while (true) {
            cout << "아이디를 입력해주세요 : ";
            cin >> newUser.userID;
            if (!isValidIDorPW(newUser.userID)) {
                cout << "올바른 형식의 아이디를 입력해주세요 (영어, 숫자, 기호 사용 가능)" << endl;
            }
            else if (isUserExists(users, "userID", newUser.userID)) {
                cout << "아이디가 중복입니다. 다시 입력해주세요." << endl;
            }
            else {
                break;
            }
        }

        cout << "비밀번호를 입력해주세요 : ";
        cin >> newUser.userPW;

        while (true) {
            cout << "이메일을 입력해주세요 : ";
            cin >> newUser.email;
            if (!isValidEmail(newUser.email)) {
                cout << "올바른 이메일 형식이 아닙니다. 다시 입력해주세요." << endl;
            }
            else if (isUserExists(users, "email", newUser.email)) {
                cout << "이메일이 중복입니다. 다시 입력해주세요." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "생년월일을 입력해주세요 (8자리, YYYYMMDD): ";
            cin >> newUser.birthdate;
            if (!isValidBirthdate(newUser.birthdate)) {
                cout << "올바른 생년월일 형식이 아닙니다. 다시 입력해주세요." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "전화번호를 입력해주세요 (11자리, 숫자만): ";
            cin >> newUser.phone;
            if (!isValidPhone(newUser.phone)) {
                cout << "올바른 전화번호 형식이 아닙니다. 다시 입력해주세요." << endl;
            }
            else if (isUserExists(users, "phone", newUser.phone)) {
                cout << "전화번호가 중복입니다. 다시 입력해주세요." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "성별을 입력해주세요 (남자/여자): ";
            cin >> newUser.gender;
            if (!isValidGender(newUser.gender)) {
                cout << "올바른 성별 형식이 아닙니다. '남자' 또는 '여자'로 입력해주세요." << endl;
            }
            else {
                break;
            }
        }

        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << newUser.userID << " " << newUser.userPW << " " << newUser.email << " " << newUser.name << " " << newUser.birthdate << " " << newUser.phone << " " << newUser.gender << endl;
            file.close();
            cout << "회원 가입이 성공적으로 완료되었습니다!" << endl;
        }
        else {
            cout << "파일을 열 수 없습니다." << endl;
        }
    }
}

void UserManager::findUserID() {

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