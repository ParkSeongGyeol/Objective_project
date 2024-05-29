#include "pch.h"
#include "dbConnector.h"
#include <msclr/marshal_cppstd.h>

using namespace msclr::interop;

bool dbConnector::CheckDuplicate(System::String^ id, System::String^ email, System::String^ phone)
{
    // 데이터베이스 연결 및 중복 확인 쿼리를 구현합니다.
    std::string stdId = marshal_as<std::string>(id);
    std::string stdEmail = marshal_as<std::string>(email);
    std::string stdPhone = marshal_as<std::string>(phone);

    // 데이터베이스에서 중복을 확인하고, 중복이 있으면 true를 반환합니다.
    // 데모를 위해, 중복이 없다고 가정합니다.
    return false;
}

bool dbConnector::RegisterUser(System::String^ id, System::String^ password, System::String^ email, System::String^ name, System::String^ birthday, System::String^ phone, System::String^ gender)
{
    // 데이터베이스 연결 및 사용자 등록 쿼리를 구현합니다.
    std::string stdId = marshal_as<std::string>(id);
    std::string stdPassword = marshal_as<std::string>(password);
    std::string stdEmail = marshal_as<std::string>(email);
    std::string stdName = marshal_as<std::string>(name);
    std::string stdBirthday = marshal_as<std::string>(birthday);
    std::string stdPhone = marshal_as<std::string>(phone);
    std::string stdGender = marshal_as<std::string>(gender);

    // 데이터베이스에 사용자를 삽입하고 성공하면 true를 반환합니다.
    // 데모를 위해, 등록이 성공했다고 가정합니다.
    return true;
}
