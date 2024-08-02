#pragma once

#ifndef SHOP_H
#define SHOP_H

#include <productmanager.h>
#include <memory>
#include "clientmanager.h"
#include "ordermanager.h"
#include "serializer.h"
#include "shoppingcart.h"
#include "logger.h"

class Shop
{
public:
    Shop();
    ~Shop(){}
    ProductManager* GetProductManager();
    ClientManager* GetClientManager();
    OrderManager* GetOrderManager();
    Serializer* GetSerializer();
    ShoppingCart* GetShoppingCart();



private:
    std::unique_ptr<ProductManager> productManager;
    std::unique_ptr<ClientManager> clientManager;
    std::unique_ptr<OrderManager> orderManager;
    std::unique_ptr<Serializer> serializer;
    std::unique_ptr<ShoppingCart> shoppingCart;
};

#endif // SHOP_H
