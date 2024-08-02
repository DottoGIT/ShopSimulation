#pragma once

#ifndef SERIALIZER_H
#define SERIALIZER_H

#define PRODUCTS_DATABASE "./Database/products.csv"
#define CLIENTS_DATABASE "./Database/clients.csv"
#define ORDERS_DATABASE "./Database/orders.json"
#define PROMOCODES_DATABASE "./Database/promoCodes.csv"
#define RECEIPT_FOLDER "./Paragony/"

#include "productmanager.h"
#include "clientmanager.h"
#include "ordermanager.h"
#include "rapidcsv.h"
#include "json.hpp"
#include "logger.h"


class Serializer
{
public:
    Serializer(OrderManager& orderManager_, ProductManager& productManager_, ClientManager& clientManager_);
    void LoadOrdersFromFile();
    void LoadPromoCodes();
    void LoadProducts();
    void LoadClients();
    void StoreOrdersInFile();
    void SaveClients();
    void SaveReceipt(const Order& order) const;
private:
    OrderManager& orderManager;
    ProductManager& productManager;
    ClientManager& clientManager;
};

#endif // SERIALIZER_H
