#pragma once

#ifndef ORDER_H
#define ORDER_H

#include <map>
#include <ctime>
#include <sstream>
#include <fstream>
#include "entity.h"
#include "client.h"
#include "address.h"
#include "logger.h"

enum class Status {
    oczekujeNaPlatnosc,
    wRealizacji,
    wTrakcieDostawy,
    zrealizowano,
    zwrot,
    anulowano
};

enum class PaymentMethod
{
    paragon,
    faktura
};

class Order : public Entity
{
public:
    Order(const Client& client_, const Address& address_, const std::map<unsigned int, unsigned int>& productsAndQuantities_,
          unsigned overallPriceGr_, const PaymentMethod& payment_, const std::string& NIP_ = "");
    Order(const Client& client_, const Address& address_, const std::map<unsigned int, unsigned int>& productsAndQuantities_,
          unsigned overallPriceGr_, const std::string& date_);
    Client GetClient() const;
    Address GetAddress() const;
    Status GetStatus() const;
    std::string GetDate() const;
    PaymentMethod GetPayment() const;
    std::string GetNIP() const;
    unsigned GetOverallPrice() const;
    std::map<unsigned int, unsigned int> GetProductsAndQuantities() const;
    std::string GetStatusStr() const;
    void SetStatus(Status status_);
    void SetOverallPriceGr(unsigned overallPriceGr_);
private:
    Client client;
    Address address;
    std::map<unsigned int, unsigned int> productsAndQuantities;
    unsigned overallPriceGr;
    std::string date;
    Status status;
    PaymentMethod payment;
    std::string NIP;
    void SetDate();
};

#endif // ORDER_H
