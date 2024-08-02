#pragma once

#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <string>
#include "rapidcsv.h"
#include "product.h"
#include "searchfilter.h"
#include "ordernotfoundexception.h"
#include "codenotfoundexception.h"
#include "logger.h"

class ProductManager
{
public:
    void AddProduct(const Product& product);
    Product FindProductById(unsigned id);
    std::vector<Product> GetProductsList(const SearchFilter& searchFilter) const;
    std::vector<Product> GetProductsList() const;
private:
    std::vector<Product> products;
};

#endif // PRODUCTMANAGER_H
