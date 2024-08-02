#pragma once

#ifndef PROMOCODE_H
#define PROMOCODE_H

#include <string>
#include "logger.h"

class PromoCode
{
public:
    PromoCode(const std::string& code_, double priceFactor_);
    std::string GetCode() const;
    double GetPriceFactor() const;
private:
    std::string code;
    double priceFactor;
};

#endif // PROMOCODE_H
