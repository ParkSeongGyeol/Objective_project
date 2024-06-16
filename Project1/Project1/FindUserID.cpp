#include "UserCreate.h"
#include "FindUserID.h"
#include <iostream>
#include <regex>

// ���� ǥ������ ����Ͽ� �Է� ������ �˻��ϴ� �Լ���
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

// ���̵� ã�� �Լ�
void findUserID() {
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