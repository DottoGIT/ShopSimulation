#include "promocode.h"

PromoCode::PromoCode(const std::string& code_, double priceFactor_) :
    code(code_), priceFactor(priceFactor_)
{
    Logger::Debug("<promocode.h> Zainicjowano kod promocyjny: " + code);
}

std::string PromoCode::GetCode() const
{
    return this->code;
}

double PromoCode::GetPriceFactor() const
{
    return this->priceFactor;
}
