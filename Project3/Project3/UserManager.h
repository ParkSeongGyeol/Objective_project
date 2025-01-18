// UserManager.h
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <vector>
#include <string>
#include "User.h"

class UserManager {


public:

    std::vector<User> loadUsers();
    bool isUserExists(const std::vector<User>& users, const std::string& field, const std::string& value);

    bool isValidIDorID(const std::string& idOrID);
    bool isValidIDorPW(const std::string& idOrPW);
    bool isValidBirthdate(const std::string& birthdate);
    bool isValidPhone(const std::string& phone);
    bool isValidEmail(const std::string& email);
    bool isValidGender(const std::string& gender);
    

    bool loginUser();
    void deleteUser();
    void findUserID();
    void findUserPW();
    void registerUser();
    void updateUser();
};

#endif // USER_MANAGER_H