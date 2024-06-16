#include "UserCreate.h"
#include "UserChange.h"
#include <iostream>
#include <fstream>
#include <regex> // ���� ǥ���� ����� ���� ��� �߰�
using namespace std;

bool isValidIDorPW(const std::string& str) {
    // ���� ǥ�������� ����, ����, ��ȣ�� �����ϴ��� �˻�
    const std::regex pattern(R"([A-Za-z0-9._%+-]+)");
    return std::regex_match(str, pattern);
}

// ���� ǥ������ ����Ͽ� �Է� ������ �˻��ϴ� �Լ���
bool isValidEmail(const std::string& email) {
    // �̸��� ���� �˻� ���� ǥ����
    const std::regex pattern(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z|a-z]{2,}\b)");
    return std::regex_match(email, pattern);
}

bool isValidPhone(const std::string& phone) {
    // ��ȭ��ȣ ���� �˻� ���� ǥ����
    const std::regex pattern(R"(\d{11})");
    return std::regex_match(phone, pattern);
}

bool isValidBirthdate(const std::string& birthdate) {
    // ������� ���� �˻� ���� ǥ����
    const std::regex pattern(R"(\d{8})");
    return std::regex_match(birthdate, pattern);
}

bool isValidGender(const std::string& gender) {
    // ���� ���� �˻�
    return gender == "����" || gender == "����";
}

// ����ڸ� ������Ʈ�ϴ� �Լ�
void updateUser() {
    std::vector<User> users = loadUsers();
    std::string userID, userPW;
    std::cout << "���̵� �Է����ּ��� : ";
    std::cin >> userID;
    std::cout << "��й�ȣ�� �Է����ּ��� : ";
    std::cin >> userPW;

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
        std::cout << "������ �����Ͻðڽ��ϱ�?:\n";
        std::cout << "1. �̸���\n";
        std::cout << "2. ��й�ȣ\n";
        std::cout << "3. �̸�\n";
        std::cout << "4. �������\n";
        std::cout << "5. ��ȭ��ȣ\n";
        std::cout << "6. ����\n";
        std::cout << "7. ���� �޴��� ���ư���\n";
        std::cout << "��ȣ�� ���� ���ּ���.: ";
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
