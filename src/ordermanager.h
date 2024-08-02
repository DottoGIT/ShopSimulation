#pragma once

#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <vector>
#include "order.h"
#include "promocode.h"
#include "ordernotfoundexception.h"
#include "codenotfoundexception.h"


class OrderManager
{
public:
    OrderManager();
    void SetPromoCodes(const std::vector<PromoCode>& promoCodes_);
    void AddOrder(const Order& order);
    Order& FindOrderById(unsigned id);
    void AddOrder(Order& order, const std::string& code);
    PromoCode FindPromoCodeByStr(const std::string& codeStr) const;
    std::vector<Order> GetOrdersVector() const;
    unsigned CalculatePriceWithCode(unsigned priceGr, const std::string& code);
private:
    std::vector<Order> orders;
    std::vector<PromoCode> promoCodes;
};

#endif // ORDERMANAGER_H
