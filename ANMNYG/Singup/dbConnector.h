#pragma once

using namespace System;

public ref class dbConnector
{
public:
    bool CheckDuplicate(String^ id, String^ email, String^ phone);
    bool RegisterUser(String^ id, String^ password, String^ email, String^ name, String^ birthday, String^ phone, String^ gender);
};
