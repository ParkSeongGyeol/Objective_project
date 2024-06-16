#include "UserCreate.h"
#include "FindUserPW.h"
#include <iostream>
#include <regex>

// ���� ǥ������ ����Ͽ� �Է� ������ �˻��ϴ� �Լ���
bool isValidUserID(const std::string& userID) {
    // ����, ����, ��ȣ�� ����ϴ� ���� ǥ����
    const std::regex pattern(R"([A-Za-z0-9._%+-]+)");
    return std::regex_match(userID, pattern);
}

bool isValidPhone(const std::string& phone) {
    // 11�ڸ� ���ڸ� ����ϴ� ���� ǥ����
    const std::regex pattern(R"(\d{11})");
    return std::regex_match(phone, pattern);
}

bool isValidBirthdate(const std::string& birthdate) {
    // 8�ڸ� ���ڸ� ����ϴ� ���� ǥ����
    const std::regex pattern(R"(\d{8})");
    return std::regex_match(birthdate, pattern);
}

// ��й�ȣ�� ã�� �Լ�
void findUserPW() {
    std::vector<User> users = loadUsers();
    std::string name, userID, phone, birthdate;

    std::cout << "�̸��� �Է��ϼ��� : ";
    std::cin >> name;

    std::cout << "���̵� �Է� ���ּ��� : ";
    std::cin >> userID;
    if (!isValidUserID(userID)) {
        std::cerr << "�ùٸ� ������ ���̵� �Է����ּ��� (����, ����, ��ȣ ��� ����)." << std::endl;
        return;
    }

    std::cout << "��ȭ��ȣ�� �Է����ּ��� : ";
    std::cin >> phone;
    if (!isValidPhone(phone)) {
        std::cerr << "�ùٸ� ������ ��ȭ��ȣ�� �Է����ּ��� (11�ڸ� ����)." << std::endl;
        return;
    }

    std::cout << "��������� �Է����ּ��� (YYYYMMDD): ";
    std::cin >> birthdate;
    if (!isValidBirthdate(birthdate)) {
        std::cerr << "�ùٸ� ������ ��������� �Է����ּ��� (8�ڸ� ����)." << std::endl;
        return;
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