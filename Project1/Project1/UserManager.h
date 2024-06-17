#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>

class UserManager {
public:
    void loginUser();
    void deleteUser();
    void findUserID();
    void findUserPW();
    void registerUser();
    void updateUser();
};

#endif
