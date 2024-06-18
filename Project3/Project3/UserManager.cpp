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


    // ���̵�� �̸��� ��ȭ��ȣ �ߺ��� �˻��ϴ� �Լ�
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

    // ���̵�, ��й�ȣ, �̸���, ��ȭ��ȣ, �������, ���� ������ �˻��ϴ� �Լ�
bool UserManager::isValidIDorID(const std::string& idOrID) {

    // ���� ǥ�������� ����, ����, ��ȣ�� �����ϴ��� �˻�

    const std::regex pattern(R"([A-Za-z0-9._%+-]+)");
    return std::regex_match(idOrID, pattern);
}

bool UserManager::isValidIDorPW(const std::string& idOrPW) {
    // ���� ���ĺ�(�빮�ڿ� �ҹ���)�� Ư�����ڸ� ����
    const std::regex pattern(R"(^[A-Za-z0-9!@#$%^&*()_+|~\-=?{}[\]:;"'<>,./]*$)");
    return std::regex_match(idOrPW, pattern);
}
    
bool UserManager::isValidEmail(const std::string& email) {

    // �̸��� ���� �´��� �˻�

    const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
    return std::regex_match(email, pattern);
}

bool UserManager::isValidPhone(const std::string& phone) {

    // ��ȭ��ȣ ���� �´��� �˻�

    const std::regex pattern(R"(\d{11})");
    return std::regex_match(phone, pattern);
}

bool UserManager::isValidBirthdate(const std::string& birthdate) {

    // ������� ���� �´��� �˻�

    const std::regex pattern(R"(\d{8})");
    return std::regex_match(birthdate, pattern);
}

bool UserManager::isValidGender(const std::string& gender) {

    // ���� ���� �´��� �˻�

    return gender == "����" || gender == "����";
}


// �α��� ����
bool UserManager::loginUser() {

    std::vector<User> users = loadUsers();
    std::string userID;
    std::string userPW;

    while (true) {

        std::cout << "���̵� �Է����ּ��� : ";
        std::cin >> userID;
        if (!isValidIDorID(userID)) {
            std::cerr << "�ùٸ� ������ ���̵� �Է����ּ��� (����, ����, ��ȣ�� . _ % + - ��� ����)." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "��й�ȣ�� �Է����ּ��� : ";
        std::cin >> userPW;
        if (!isValidIDorPW(userPW)) {
            std::cerr << "�ùٸ� ������ ��й�ȣ�� �Է����ּ��� (����, ����, ��ȣ ��� ����)." << std::endl;
        }
        else {
            break;
        }
    }

    auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
        return user.userID == userID && user.userPW == userPW;
        });

    if (it != users.end()) {
        std::cout << "���������� �α��� �Ǽ̽��ϴ�." << std::endl;
        return true;
    }
    else {
        std::cerr << "��ȿ���� ���� ���̵� �Ǵ� ��й�ȣ �Դϴ�." << std::endl;
        return false;
    }
}

// ȸ�� ���� ����
void UserManager::deleteUser() {

    std::vector<User> users = loadUsers();
    std::string userID, userPW;

    while (true)
    {
        std::cout << "Ż�� ���� ȸ������ ���̵� �Է����ּ��� : ";
        std::cin >> userID;
        if (!isValidIDorID(userID)) {
            std::cerr << "�ùٸ� ������ ���̵� �Է����ּ��� (����, ����, ��ȣ . _ % + - ��� ����)." << std::endl;
        }
        else {
            break;
        }
    }
    
    while (true)
    {
        std::cout << "��й�ȣ�� �Է����ּ��� : ";
        std::cin >> userPW;
        if (!isValidIDorPW(userPW)) {
            std::cerr << "�ùٸ� ������ ��й�ȣ�� �Է����ּ��� (����, ����, ��ȣ ��� ����)." << std::endl;
        }
        else {
            break;
        }
    }


    auto it = std::remove_if(users.begin(), users.end(), [&](const User& user) {
        return user.userID == userID && user.userPW == userPW;
        });

    if (it == users.end()) {
        std::cerr << "��ȿ���� ���� ���̵� �Ǵ� ��й�ȣ�Դϴ�." << std::endl;
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
        std::cout << "���������� ȸ��Ż�� �Ǽ̽��ϴ�." << std::endl;
    }
    else {
        std::cerr << "�����͸� ������Ʈ�ϴµ� ������ �߻��߽��ϴ�." << std::endl;
    }
}

// ���̵� ã�� ����
void UserManager::findUserID() {

    std::vector<User> users = loadUsers();
    std::string name, birthdate, phone, email;

    std::cout << "�̸��� �Է����ּ��� : ";
    std::cin >> name;


    while (true) {

        std::cout << "��������� �Է����ּ��� (YYYYMMDD): ";
        std::cin >> birthdate;
        if (!isValidBirthdate(birthdate)) {
            std::cerr << "�ùٸ� ������ ��������� �Է����ּ��� (8�ڸ� ����)" << std::endl;
        }
        else {
            break;
        }
    }


    while (true) {
        std::cout << "�̸����� �Է����ּ��� : ";
        std::cin >> email;
        if (!isValidEmail(email)) {
            std::cerr << "�ùٸ� ������ �̸����� �Է����ּ���" << std::endl;
        }
        else {
            break;
        }
    }


    while (true) {

        std::cout << "��ȭ��ȣ�� �Է����ּ��� : ";
        std::cin >> phone;
        if (!isValidPhone(phone)) {
            std::cerr << "�ùٸ� ������ ��ȭ��ȣ�� �Է����ּ��� (11�ڸ� ����)" << std::endl;
        }
        else {
            break;
        }
    }

auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
    return user.name == name && user.birthdate == birthdate && user.phone == phone;
    });

if (it != users.end()) {
    std::cout << "ȸ������ ���̵�� : " << it->userID << " �Դϴ�." << std::endl;
}
else {
    std::cerr << "ȸ���� ã�� �� �����ϴ�." << std::endl;
}
}

// ��й�ȣ ã�� ����
void UserManager::findUserPW() {

    std::vector<User> users = loadUsers();
    std::string name, userID, phone, birthdate, email;

    std::cout << "�̸��� �Է��ϼ��� : ";
    std::cin >> name;

    while (true) {
        std::cout << "���̵� �Է� ���ּ��� : ";
        std::cin >> userID;
        if (!isValidIDorID(userID)) {
            std::cerr << "�ùٸ� ������ ���̵� �Է����ּ��� (����, ����, ��ȣ . _ % + - ��� ����)." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {

        std::cout << "��������� �Է����ּ��� (YYYYMMDD): ";
        std::cin >> birthdate;
        if (!isValidBirthdate(birthdate)) {
            std::cerr << "�ùٸ� ������ ��������� �Է����ּ��� (8�ڸ� ����)" << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "�̸����� �Է����ּ��� : ";
        std::cin >> email;
        if (!isValidEmail(email)) {
            std::cerr << "�ùٸ� ������ �̸����� �Է����ּ���" << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {

        std::cout << "��ȭ��ȣ�� �Է����ּ��� : ";
        std::cin >> phone;
        if (!isValidPhone(phone)) {
            std::cerr << "�ùٸ� ������ ��ȭ��ȣ�� �Է����ּ��� (11�ڸ� ����)" << std::endl;
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
        std::cout << "ȸ������ ��й�ȣ�� : " << it->userPW << " �Դϴ�." << std::endl;
    }
    else {
        std::cerr << "ȸ���� ã�� �� ���ų� ȸ�������� ��ġ���� �ʽ��ϴ�." << std::endl;
    }
}

// ȸ�� ���� ����
void UserManager::registerUser() {
    std::vector<User> users = loadUsers();
    User newUser;

    std::cout << "ȸ�� ������ �����մϴ�." << std::endl;

    std::cout << "�̸��� �Է����ּ��� : ";
    std::cin >> newUser.name;

    while (true) {
        std::cout << "���̵� �Է����ּ��� : ";
        std::cin >> newUser.userID;
        if (!isValidIDorID(newUser.userID)) {
            std::cout << "�ùٸ� ������ ���̵� �Է����ּ��� (����, ����, ��ȣ . _ % + - �� ��� ����)" << std::endl;
        }
        else if (isUserExists(users, "userID", newUser.userID)) {
            std::cout << "���̵� �ߺ��Դϴ�. �ٽ� �Է����ּ���." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "��й�ȣ�� �Է����ּ��� : ";
        std::cin >> newUser.userPW;
        if (!isValidIDorPW(newUser.userPW)) {
            std::cout << "�ùٸ� ������ ��й�ȣ�� �Է����ּ��� (����, ����, ��ȣ�� ��� ����)" << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "�̸����� �Է����ּ��� : ";
        std::cin >> newUser.email;
        if (!isValidEmail(newUser.email)) {
            std::cout << "�ùٸ� �̸��� ������ �ƴմϴ�. �ٽ� �Է����ּ���." << std::endl;
        }
        else if (isUserExists(users, "email", newUser.email)) {
            std::cout << "�̸����� �ߺ��Դϴ�. �ٽ� �Է����ּ���." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "��������� �Է����ּ��� (8�ڸ�, YYYYMMDD): ";
        std::cin >> newUser.birthdate;
        if (!isValidBirthdate(newUser.birthdate)) {
            std::cout << "�ùٸ� ������� ������ �ƴմϴ�. �ٽ� �Է����ּ���." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "��ȭ��ȣ�� �Է����ּ��� (11�ڸ�, ���ڸ�): ";
        std::cin >> newUser.phone;
        if (!isValidPhone(newUser.phone)) {
            std::cout << "�ùٸ� ��ȭ��ȣ ������ �ƴմϴ�. �ٽ� �Է����ּ���." << std::endl;
        }
        else if (isUserExists(users, "phone", newUser.phone)) {
            std::cout << "��ȭ��ȣ�� �ߺ��Դϴ�. �ٽ� �Է����ּ���." << std::endl;
        }
        else {
            break;
        }
    }

    while (true) {
        std::cout << "������ �Է����ּ��� (����/����): ";
        std::cin >> newUser.gender;
        if (!isValidGender(newUser.gender)) {
            std::cout << "�ùٸ� ���� ������ �ƴմϴ�. '����' �Ǵ� '����'�� �Է����ּ���." << std::endl;
        }
        else {
            break;
        }
    }

    std::ofstream file("users.txt", std::ios::app);
    if (file.is_open()) {
        file << newUser.userID << " " << newUser.userPW << " " << newUser.email << " " << newUser.name << " " << newUser.birthdate << " " << newUser.phone << " " << newUser.gender << std::endl;
        file.close();
        std::cout << "ȸ�� ������ ���������� �Ϸ�Ǿ����ϴ�!" << std::endl;
    }
    else {
        std::cerr << "������ �� �� �����ϴ�." << std::endl;
    }
}

// ȸ�� ���� ����
void UserManager::updateUser() {

    std::vector<User> users = loadUsers();
    std::string userID, userPW;

    while (true)
    {
        std::cout << "ȸ�������� ���� ȸ������ ���̵� �Է����ּ��� : ";
        std::cin >> userID;
        if (!isValidIDorID(userID)) {
            std::cerr << "�ùٸ� ������ ���̵� �Է����ּ��� (����, ����, ��ȣ ��� ����)." << std::endl;
        }
        else {
            break;
        }
    }

    while (true)
    {
        std::cout << "��й�ȣ�� �Է����ּ��� : ";
        std::cin >> userPW;
        if (!isValidIDorPW(userPW)) {
            std::cerr << "�ùٸ� ������ ��й�ȣ�� �Է����ּ��� (����, ����, ��ȣ ��� ����)." << std::endl;
        }
        else {
            break;
        }
    }

    auto it = std::find_if(users.begin(), users.end(), [&](const User& user) {
        return user.userID == userID && user.userPW == userPW;
        });

    if (it == users.end()) {
        std::cerr << "��ȿ���� ���� ���̵� �Ǵ� ��й�ȣ �Դϴ�." << std::endl;
        return;
    }

    User& userToUpdate = *it;
    int choice;

    while (true) {
        std::cout << "������ �����Ͻðڽ��ϱ�? :\n";
        std::cout << " \n";
        std::cout << "1. �̸���\n";
        std::cout << " \n";
        std::cout << "2. ��й�ȣ\n";
        std::cout << " \n";
        std::cout << "3. �̸�\n";
        std::cout << " \n";
        std::cout << "4. �������\n";
        std::cout << " \n";
        std::cout << "5. ��ȭ��ȣ\n";
        std::cout << " \n";
        std::cout << "6. ����\n";
        std::cout << " \n";
        std::cout << "7. ���� �޴��� ���ư���\n";
        std::cout << " \n";
        std::cout << "��ȣ�� ���� ���ּ��� : ";
        std::cout << " \n";
        std::cout << " \n";
        std::cin >> choice;

        if (choice == 7) {
            break;
        }

        switch (choice) {
        case 1: {
            std::cout << "������ �̸����� �Է����ּ��� : ";
            std::string newEmail;
            std::cin >> newEmail;
            if (!isValidEmail(newEmail)) {
                std::cerr << "�ùٸ� �̸��� ������ �ƴմϴ�. �ٽ� �Է����ּ���." << std::endl;
            }
            else {
                userToUpdate.email = newEmail;
                std::cout << "�̸����� ���������� ����Ǿ����ϴ�." << std::endl;
            }
            break;
        }
        case 2: {
            std::cout << "������ ��й�ȣ�� �Է����ּ��� : ";
            std::string newPassword;
            std::cin >> newPassword;
            if (!isValidIDorPW(newPassword)) {
                std::cerr << "�ùٸ� ������ ��й�ȣ�� �Է����ּ��� (����, ����, ��ȣ ��� ����)." << std::endl;
            }
            else {
                userToUpdate.userPW = newPassword;
                std::cout << "��й�ȣ�� ���������� ����Ǿ����ϴ�." << std::endl;
            }
            break;
        }
        case 3:
            std::cout << "������ �̸��� �Է����ּ��� : ";
            std::cin >> userToUpdate.name;
            std::cout << "�̸��� ���������� ����Ǿ����ϴ�." << std::endl;
            break;
        case 4: {
            std::cout << "������ ��������� �Է����ּ��� (YYYYMMDD): ";
            std::string newBirthdate;
            std::cin >> newBirthdate;
            if (!isValidBirthdate(newBirthdate)) {
                std::cerr << "�ùٸ� ������� ������ �ƴմϴ�. �ٽ� �Է����ּ���." << std::endl;
            }
            else {
                userToUpdate.birthdate = newBirthdate;
                std::cout << "��������� ���������� ����Ǿ����ϴ�." << std::endl;
            }
            break;
        }
        case 5: {
            std::cout << "������ ��ȭ��ȣ�� �Է����ּ��� : ";
            std::string newPhone;
            std::cin >> newPhone;
            if (!isValidPhone(newPhone)) {
                std::cerr << "�ùٸ� ��ȭ��ȣ ������ �ƴմϴ�. �ٽ� �Է����ּ���." << std::endl;
            }
            else {
                userToUpdate.phone = newPhone;
                std::cout << "��ȭ��ȣ�� ���������� ����Ǿ����ϴ�." << std::endl;
            }
            break;
        }
        case 6: {
            std::cout << "������ ������ �Է����ּ��� : ";
            std::string newGender;
            std::cin >> newGender;
            if (!isValidGender(newGender)) {
                std::cerr << "�ùٸ� ���� ������ �ƴմϴ�. '����' �Ǵ� '����'�� �Է����ּ���." << std::endl;
            }
            else {
                userToUpdate.gender = newGender;
                std::cout << "������ ���������� ����Ǿ����ϴ�." << std::endl;
            }
            break;
        }
        default:
            std::cerr << "�ùٸ��� ���� ���� �Դϴ�. �ٽ� �õ����ֽʽÿ�." << std::endl;
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
        std::cerr << "������ �����͸� ������Ʈ�ϴµ� ������ �ֽ��ϴ�." << std::endl;
    }
}
