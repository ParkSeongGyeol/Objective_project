#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <regex>

bool isValidBirthdate(const std::string& birthdate);
bool isValidEmail(const std::string& email);
bool isValidGender(const std::string& gender);
bool isValidIDorPW(const std::string& idOrPW);
bool isValidPhone(const std::string& phone);

#endif