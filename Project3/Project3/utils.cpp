#include "utils.h"
#include <regex>



bool isValidIDorID(const std::string& idOrID) {
    // ���� ǥ�������� ����, ����, ��ȣ�� �����ϴ��� �˻�
    const std::regex pattern(R"([A-Za-z0-9._%+-]+)");
    return std::regex_match(idOrID, pattern);
}

bool isValidIDorPW(const std::string& idOrPW) {
    // ���� ���ĺ�(�빮�ڿ� �ҹ���)�� Ư�����ڸ� ����
    const std::regex pattern(R"(^[A-Za-z!@#$%^&*()_+|~\-=?{}[\]:;"'<>,./]*$)");
    return std::regex_match(idOrPW, pattern);
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
