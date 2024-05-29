#include "pch.h"
#include "dbConnector.h"
#include <msclr/marshal_cppstd.h>

using namespace msclr::interop;

bool dbConnector::CheckDuplicate(System::String^ id, System::String^ email, System::String^ phone)
{
    // �����ͺ��̽� ���� �� �ߺ� Ȯ�� ������ �����մϴ�.
    std::string stdId = marshal_as<std::string>(id);
    std::string stdEmail = marshal_as<std::string>(email);
    std::string stdPhone = marshal_as<std::string>(phone);

    // �����ͺ��̽����� �ߺ��� Ȯ���ϰ�, �ߺ��� ������ true�� ��ȯ�մϴ�.
    // ���� ����, �ߺ��� ���ٰ� �����մϴ�.
    return false;
}

bool dbConnector::RegisterUser(System::String^ id, System::String^ password, System::String^ email, System::String^ name, System::String^ birthday, System::String^ phone, System::String^ gender)
{
    // �����ͺ��̽� ���� �� ����� ��� ������ �����մϴ�.
    std::string stdId = marshal_as<std::string>(id);
    std::string stdPassword = marshal_as<std::string>(password);
    std::string stdEmail = marshal_as<std::string>(email);
    std::string stdName = marshal_as<std::string>(name);
    std::string stdBirthday = marshal_as<std::string>(birthday);
    std::string stdPhone = marshal_as<std::string>(phone);
    std::string stdGender = marshal_as<std::string>(gender);

    // �����ͺ��̽��� ����ڸ� �����ϰ� �����ϸ� true�� ��ȯ�մϴ�.
    // ���� ����, ����� �����ߴٰ� �����մϴ�.
    return true;
}
