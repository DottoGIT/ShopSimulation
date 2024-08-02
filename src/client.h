#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "logger.h"


class Client
{
public:
    Client(const std::string& login_, const std::string& password_,
           const std::string& name_, const std::string& surname_);
    std::string GetLogin() const;
    std::string GetPassword() const;
    std::string GetName() const;
    std::string GetSurname() const;
    bool operator==(const std::string& comparedStr) const;
private:
    std::string login;
    std::string password;
    std::string name;
    std::string surname;
};

#endif // CLIENT_H
