#pragma once

#ifndef PRODUCT_H
#define PRODUCT_H

#include <sstream>
#include <stdexcept>
#include <vector>
#include "entity.h"
#include "producttags.h"
#include "logger.h"

class Product: public Entity
{
public:
    Product(const std::string& name_, unsigned int priceZl_, unsigned int priceGr_,
            const std::vector<ProductTags>& tags_, const std::string& imgPath_);
    std::string GetName() const;
    unsigned int GetPriceGr() const;
    std::string GetImgPath() const;
    std::vector<ProductTags> GetTags() const;
    std::string PriceToString() const;

    operator std::string() const;
private:
    std::string name;
    std::vector<ProductTags> tags;
    std::string imgPath;
    unsigned int priceGr;
    std::string TagsToString() const;
};

#endif // PRODUCT_H
