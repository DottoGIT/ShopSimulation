#include "client.h"

Client::Client(const std::string& login_, const std::string& password_,
               const std::string& name_, const std::string& surname_)
    : login{login_}, password{password_}, name{name_}, surname{surname_}
{
    Logger::Debug("<client.h> Zainicjowano nowego klienta: " + GetName() + " " + GetSurname());
}

std::string Client::GetName() const
{
    return name;
}

std::string Client::GetSurname() const
{
    return surname;
}

std::string Client::GetPassword() const
{
    return password;
}

std::string Client::GetLogin() const
{
    return login;
}

bool Client::operator==(const std::string& comparedStr) const
{
    return login == comparedStr;
}
