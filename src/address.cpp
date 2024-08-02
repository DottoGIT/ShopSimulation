#include "address.h"

Address::Address(const std::string& city_, const std::string& postalCode_,
               const std::string& streetAndNumber_)
    : city{city_}, postalCode{postalCode_}, streetAndNumber{streetAndNumber_}
{
    Logger::Debug("<address.h> Zainicjowano nowy adres: " + GetCity() + " " + GetStreetAndNumber());
}

std::string Address::GetCity() const
{
    return city;
}

std::string Address::GetPostalCode() const
{
    return postalCode;
}

std::string Address::GetStreetAndNumber() const
{
    return streetAndNumber;
}
