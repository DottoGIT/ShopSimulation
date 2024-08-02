#include "searchfilter.h"

bool SearchFilter::CheckItem(const Product& product) const
{
    return IsInPriceBrackets(product.GetPriceGr()) && ContainsPhrase(product.GetName()) && ContainsTags(product.GetTags());
}

bool SearchFilter::GetSortCompariser(const Product& p1, const Product& p2) const
{
    bool condition;
    switch (sortType)
    {
    case SortType::ByIdHighest: condition = p1.GetId() > p2.GetId(); break;
    case SortType::ByIdLowest: condition = p1.GetId() < p2.GetId(); break;
    case SortType::ByPriceHighest: condition = p1.GetPriceGr() > p2.GetPriceGr(); break;
    case SortType::ByPriceLowest: condition = p1.GetPriceGr() < p2.GetPriceGr(); break;
    default: throw std::invalid_argument("Niepoprawny typ sortowania");
    }
    return condition;
}

bool SearchFilter::IsInPriceBrackets(unsigned int priceGr) const
{
    return priceGr >= priceBottomGr && priceGr <= priceCeilGr;
}

bool SearchFilter::ContainsPhrase(const std::string& productName) const
{
    std::string productNameToLower, phraseToLower;
    std::ranges::transform(productName, std::back_inserter(productNameToLower), [](const auto& c){return std::tolower(c);});
    std::ranges::transform(phrase, std::back_inserter(phraseToLower), [](const auto& c){return std::tolower(c);});
    return std::search(productNameToLower.begin(), productNameToLower.end(), phraseToLower.begin(), phraseToLower.end()) != productNameToLower.end();
}

bool SearchFilter::ContainsTags(const std::vector<ProductTags>& productTags) const
{
    for(const auto& tag : tags)
    {
        auto findResult = std::find(productTags.begin(), productTags.end(), tag);
        if (findResult != productTags.end()) {
            return true;
        }
    }
    return false;
}
