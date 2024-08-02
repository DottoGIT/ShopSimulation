#include "ordermanager.h"

OrderManager::OrderManager() {}

void OrderManager::SetPromoCodes(const std::vector<PromoCode>& promoCodes_)
{
    Logger::Info("<orderManager.h> Ustawiono nowa baze kodow promocyjnych");
    promoCodes = promoCodes_;
}

PromoCode OrderManager::FindPromoCodeByStr(const std::string& codeStr) const
{
    for (const auto& code: promoCodes){
        if (code.GetCode() == codeStr){
            Logger::Info("<orderManager.h> Znaleziono kod promocyjny " + codeStr);
            return code;
        }
    }
    Logger::Warning("<orderManager.h> Kod promocyjny " + codeStr + " nie zostal znaleziony");
    throw CodeNotFoundException(codeStr);
}

void OrderManager::AddOrder(const Order& order)
{

    orders.push_back(order);
    Logger::Info("<orderManager.h> Zamowienie id: " + std::to_string(order.GetId()) + " zostalo dodane do bazy");
}

void OrderManager::AddOrder(Order& order, const std::string& code)
{
    unsigned basePrice = order.GetOverallPrice();
    order.SetOverallPriceGr(CalculatePriceWithCode(basePrice, code));
    orders.push_back(order);
    Logger::Info("<orderManager.h> Zamowienie id: " + std::to_string(order.GetId()) + "z kodem " + code + " zostalo dodane do bazy");
}

std::vector<Order> OrderManager::GetOrdersVector() const
{
    return orders;
}

Order& OrderManager::FindOrderById(unsigned id)
{
    for(auto& order: orders){
        if (order.GetId() == id){
            Logger::Debug("<orderManager.h> Zamowienie id " + std::to_string(id) + " zostalo znalezione");
            return order;
        }
    }
    Logger::Warning("<orderManager.h> Zamowienie id " + std::to_string(id) + " nie zostalo znalezione");
    throw OrderNotFoundException(id);
}

unsigned OrderManager::CalculatePriceWithCode(unsigned int priceGr, const std::string& code)
{
    PromoCode promoCd = FindPromoCodeByStr(code);
    return priceGr * promoCd.GetPriceFactor();
}
