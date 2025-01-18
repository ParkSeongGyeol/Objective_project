#ifndef USERC_CREATE_H
#define USERC_CREATE_H

#include "UserManager.h"
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

#endif