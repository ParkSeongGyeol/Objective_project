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

        cout << "ȸ�� ������ �����մϴ�." << endl;

        cout << "�̸��� �Է����ּ��� : ";
        cin >> newUser.name;

        while (true) {
            cout << "���̵� �Է����ּ��� : ";
            cin >> newUser.userID;
            if (!isValidIDorPW(newUser.userID)) {
                cout << "�ùٸ� ������ ���̵� �Է����ּ��� (����, ����, ��ȣ ��� ����)" << endl;
            }
            else if (isUserExists(users, "userID", newUser.userID)) {
                cout << "���̵� �ߺ��Դϴ�. �ٽ� �Է����ּ���." << endl;
            }
            else {
                break;
            }
        }

        cout << "��й�ȣ�� �Է����ּ��� : ";
        cin >> newUser.userPW;

        while (true) {
            cout << "�̸����� �Է����ּ��� : ";
            cin >> newUser.email;
            if (!isValidEmail(newUser.email)) {
                cout << "�ùٸ� �̸��� ������ �ƴմϴ�. �ٽ� �Է����ּ���." << endl;
            }
            else if (isUserExists(users, "email", newUser.email)) {
                cout << "�̸����� �ߺ��Դϴ�. �ٽ� �Է����ּ���." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "��������� �Է����ּ��� (8�ڸ�, YYYYMMDD): ";
            cin >> newUser.birthdate;
            if (!isValidBirthdate(newUser.birthdate)) {
                cout << "�ùٸ� ������� ������ �ƴմϴ�. �ٽ� �Է����ּ���." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "��ȭ��ȣ�� �Է����ּ��� (11�ڸ�, ���ڸ�): ";
            cin >> newUser.phone;
            if (!isValidPhone(newUser.phone)) {
                cout << "�ùٸ� ��ȭ��ȣ ������ �ƴմϴ�. �ٽ� �Է����ּ���." << endl;
            }
            else if (isUserExists(users, "phone", newUser.phone)) {
                cout << "��ȭ��ȣ�� �ߺ��Դϴ�. �ٽ� �Է����ּ���." << endl;
            }
            else {
                break;
            }
        }

        while (true) {
            cout << "������ �Է����ּ��� (����/����): ";
            cin >> newUser.gender;
            if (!isValidGender(newUser.gender)) {
                cout << "�ùٸ� ���� ������ �ƴմϴ�. '����' �Ǵ� '����'�� �Է����ּ���." << endl;
            }
            else {
                break;
            }
        }

        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << newUser.userID << " " << newUser.userPW << " " << newUser.email << " " << newUser.name << " " << newUser.birthdate << " " << newUser.phone << " " << newUser.gender << endl;
            file.close();
            cout << "ȸ�� ������ ���������� �Ϸ�Ǿ����ϴ�!" << endl;
        }
        else {
            cout << "������ �� �� �����ϴ�." << endl;
        }
    }
}

void UserManager::findUserID() {

    std::vector<User> users = loadUsers();
    std::string name, birthdate, phone;

    std::cout << "�̸��� �Է����ּ��� : ";
    std::cin >> name;

    std::cout << "��������� �Է����ּ��� (YYYYMMDD): ";
    std::cin >> birthdate;
    if (!isValidBirthdate(birthdate)) {
        std::cerr << "�ùٸ� ������ ��������� �Է����ּ��� (8�ڸ� ����)." << std::endl;
        return;
    }

    std::cout << "��ȭ��ȣ�� �Է����ּ��� : ";
    std::cin >> phone;
    if (!isValidPhone(phone)) {
        std::cerr << "�ùٸ� ������ ��ȭ��ȣ�� �Է����ּ��� (11�ڸ� ����)." << std::endl;
        return;
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