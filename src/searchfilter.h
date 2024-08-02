#pragma once

#ifndef SEARCHFILTER_H
#define SEARCHFILTER_H

#include <stdexcept>
#include <string>
#include <algorithm>
#include "product.h"

enum class SortType
{
    ByIdLowest,
    ByIdHighest,
    ByPriceLowest,
    ByPriceHighest
};

class SearchFilter
{
public:
    SearchFilter(const unsigned int priceBottomGr_, const unsigned int priceCeilGr_,
                 const std::string& phrase_, const SortType sortType_, const std::vector<ProductTags>& tags_)
        :priceBottomGr(priceBottomGr_),priceCeilGr(priceCeilGr_), phrase(phrase_), sortType(sortType_), tags(tags_){}
    bool CheckItem(const Product& product) const;
    bool GetSortCompariser(const Product& p1, const Product& p2) const;
private:
    unsigned int priceBottomGr;
    unsigned int priceCeilGr;
    std::string phrase;
    SortType sortType;
    std::vector<ProductTags> tags;

    bool IsInPriceBrackets(unsigned int priceGr) const;
    bool ContainsPhrase(const std::string& productName) const;
    bool ContainsTags(const std::vector<ProductTags>& tags) const;

};
#endif // SEARCHFILTER_H
