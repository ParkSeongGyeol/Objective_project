#ifndef USERC_CREATE_H
#define USERC_CREATE_H

#include <string>
#include <vector>

// 사용자 정보를 저장하는 구조체
struct User {
    std::string userID;
    std::string userPW;
    std::string email;
    std::string name;
    std::string birthdate;
    std::string phone;
    std::string gender;
};

// 함수 선언
std::vector<User> loadUsers();
bool isUserExists(const std::vector<User>& users, const std::string& field, const std::string& value);
void registerUser();

#endif