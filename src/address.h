#pragma once

#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>
#include "logger.h"

class Address
{
public:
    Address(const std::string& city_, const std::string& postalCode_,
           const std::string& streetAndNumber_);
    std::string GetCity() const;
    std::string GetPostalCode() const;
    std::string GetStreetAndNumber() const;
private:
    std::string city;
    std::string postalCode;
    std::string streetAndNumber;
};

#endif // ADDRESS_H
