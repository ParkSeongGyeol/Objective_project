#include "utils.h"
#include <regex>



    bool isValidIDorPW(const std::string& str) {
        // ���� ǥ�������� ����, ����, ��ȣ�� �����ϴ��� �˻�
        const std::regex pattern(R"([A-Za-z0-9._%+-]+)");
        return std::regex_match(str, pattern);
    }

    bool isValidEmail(const std::string& email) {
        const std::regex pattern(R"((\w+)(\.{1}\w+)*@(\w+)(\.\w+)+)");
        return std::regex_match(email, pattern);
    }

    bool isValidPhone(const std::string& phone) {
        const std::regex pattern(R"(\d{11})");
        return std::regex_match(phone, pattern);
    }

    bool isValidBirthdate(const std::string& birthdate) {
        const std::regex pattern(R"(\d{8})");
        return std::regex_match(birthdate, pattern);
    }

    bool isValidGender(const std::string& gender) {
        return gender == "����" || gender == "����";
    }
