#include "shoppingcart.h"

bool ShoppingCart::isInCart(unsigned id) const
{
    auto it = productsInCart.find(id);
    if (it != productsInCart.end()){
        return true;
    }else{
        return false;
    }
}

void ShoppingCart::setQuantity(unsigned id, unsigned quantity)
{
    if (isInCart(id)){
        if (quantity != 0){
            Logger::Info("<shoppingCart.h> ilosc produktu o id " + std::to_string(id) + " zostala zmieniona na " + std::to_string(quantity));
            productsInCart.at(id) = quantity;
        }else{
            deleteFromCart(id);
        }
    }else{
        productsInCart.insert({id, quantity});
    }
}

void ShoppingCart::addToCart(unsigned id, unsigned quantity)
{
    setQuantity(id, (getQuanity(id) + quantity));
}

void ShoppingCart::deleteFromCart(unsigned id)
{
    auto it = productsInCart.find(id);
    if (it != productsInCart.end()){
        Logger::Info("<shoppingCart.h> Produkt o id " + std::to_string(id) + " zostal usuniety z koszyka");
        productsInCart.erase(it);
        return;
    }
    Logger::Warning("<shoppingCart.h> Produkt o id " + std::to_string(id) + " nie znajduje sie w koszyku");
}

unsigned ShoppingCart::getQuanity(unsigned id) const
{
    if (isInCart(id)){
        return productsInCart.at(id);
    }else{
        return 0;
    }
}

void ShoppingCart::clearCart()
{
    Logger::Info("<shoppingCart.h> Produkty z koszyka zostaly usuniete");
    productsInCart.clear();
}

std::map<unsigned int, unsigned int> ShoppingCart::getProductsInCartMap() const
{
    return productsInCart;

}
