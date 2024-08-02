#include "order.h"

Order::Order(const Client& client_, const Address& address_, const std::map<unsigned int, unsigned int>& productsAndQuantities_, unsigned overallPriceGr_, const PaymentMethod& payment_, const std::string& NIP_) :
    client(client_), address(address_), productsAndQuantities(productsAndQuantities_), overallPriceGr(overallPriceGr_),payment(payment_),NIP(NIP_) {
    status = Status::oczekujeNaPlatnosc;
    SetDate();
    if(payment == PaymentMethod::faktura)
        Logger::Info("<order.h> Zamowienie id " + std::to_string(GetId()) + " zostalo utworzone na fatkture");
    else if(payment == PaymentMethod::paragon)
        Logger::Info("<order.h> Zamowienie id " + std::to_string(GetId()) + " zostalo utworzone na paragon");
}

Order::Order(const Client& client_, const Address& address_, const std::map<unsigned int, unsigned int>& productsAndQuantities_,
             unsigned overallPriceGr_, const std::string& date_) :
    client(client_), address(address_), productsAndQuantities(productsAndQuantities_), overallPriceGr(overallPriceGr_), date(date_)
{
    Logger::Info("<order.h> Zamowienie id " + std::to_string(GetId()) + " zostalo pobrane z pliku");
}

Client Order::GetClient() const
{
    return client;
}

Address Order::GetAddress() const
{
    return address;
}

Status Order::GetStatus() const
{
    return status;
}

std::string Order::GetDate() const
{
    return date;
}

PaymentMethod Order::GetPayment() const
{
    return payment;
}
std::string Order::GetNIP() const
{
    return NIP;
}

unsigned Order::GetOverallPrice() const
{
    return overallPriceGr;
}

std::map<unsigned int, unsigned int> Order::GetProductsAndQuantities() const
{
    return productsAndQuantities;
}

std::string Order::GetStatusStr() const
{
    if (status == Status::oczekujeNaPlatnosc){
        return "oczekuje na platnosc";
    } else if (status == Status::wRealizacji) {
        return "w realizacji";
    } else if (status == Status::wTrakcieDostawy){
        return "w trakcie dostawy";
    } else if (status == Status::zrealizowano){
        return "zrealizowano";
    } else if (status == Status::zwrot){
        return "zwrot";
    } else {
        return "anulowano";
    }
}

void Order::SetStatus(Status status_)
{
    status = status_;
    Logger::Info("<order.h> Zamowienie id " + std::to_string(GetId()) + " zmienilo swoj status na " + GetStatusStr());
}

void Order::SetOverallPriceGr(unsigned overallPriceGr_)
{
    overallPriceGr = overallPriceGr_;
    Logger::Info("<order.h> Cena zamowienia id " + std::to_string(GetId()) + " zostala zmieniona");
}

void Order::SetDate()
{
    time_t now = time(0);
    tm *local_time = localtime(&now);
    int year = 1900 + local_time->tm_year;
    int month = 1 + local_time->tm_mon;
    int day = local_time->tm_mday;
    std::stringstream sso;
    sso << day << "/" << month << "/" << year;
    date = sso.str();
}
