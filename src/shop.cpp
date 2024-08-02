#include "shop.h"

Shop::Shop()
    : productManager(std::make_unique<ProductManager>()),
    clientManager(std::make_unique<ClientManager>()),
    orderManager(std::make_unique<OrderManager> ()),
    serializer(std::make_unique<Serializer> (*(orderManager.get()), *(productManager.get()), *(clientManager.get()))),
    shoppingCart(std::make_unique<ShoppingCart>())
{
    Logger::Info("<shop.h> Sklep zostal zainicjowany");
}

ProductManager* Shop::GetProductManager()
{
    return productManager.get();
}

ClientManager* Shop::GetClientManager()
{
    return clientManager.get();
}

OrderManager* Shop::GetOrderManager()
{
    return orderManager.get();
}

Serializer* Shop::GetSerializer()
{
    return serializer.get();
}

ShoppingCart* Shop::GetShoppingCart()
{
    return shoppingCart.get();
}
