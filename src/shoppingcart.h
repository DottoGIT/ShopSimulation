#pragma once

#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <map>
#include "logger.h"

class ShoppingCart
{
public:
    void setQuantity(unsigned id, unsigned quantity);
    void addToCart(unsigned id, unsigned quantity=1);
    void deleteFromCart(unsigned id);
    void clearCart();
    unsigned getQuanity(unsigned id) const;
    std::map<unsigned int, unsigned int> getProductsInCartMap() const;

private:
    std::map<unsigned int, unsigned int> productsInCart; // by id - key is id and value is quantity
    bool isInCart(unsigned id) const;
};

#endif // SHOPPINGCART_H
