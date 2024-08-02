#include "product.h"


Product::Product(const std::string& name_, unsigned int priceZl_, unsigned int priceGr_,
                 const std::vector<ProductTags>& tags_, const std::string& imgPath_)
    : name(name_), tags(tags_), imgPath(imgPath_)
{
    if(name_.empty())
    {
        throw std::invalid_argument("Nazwa produktu nie moze byc pusta");
        Logger::Error("<product.h> Wykryto próbę dodanie produktu bez nazwy");
    }
    if(tags_.empty())
    {
        throw std::invalid_argument("Produkt musi posiadac przynajmniej jeden tag");
        Logger::Error("<product.h> Wykryto próbę dodanie produktu bez tagu");
    }
    priceGr = priceZl_*100 + priceGr_;
    Logger::Debug("<product.h> Zainicjowano produkt " + GetName() + " o id " + std::to_string(GetId()));
}

std::string Product::GetName() const
{
    return name;
}

unsigned int Product::GetPriceGr() const
{
    return priceGr;
}

std::string Product::GetImgPath() const
{
    return imgPath;
}

std::vector<ProductTags> Product::GetTags() const
{
    return tags;
}

Product::operator std::string() const
{
    std::stringstream sso;
    sso << "\tNazwa: " << GetName() << "\n"
        << "\tCena: " << PriceToString() << "\t\t" << "Id: " << GetId() << "\n"
        << "\tTagi: " << TagsToString();
    return sso.str();
}

std::string Product::TagsToString() const
{
    std::stringstream sso;
    for(auto tag : tags)
    {
        switch(tag)
        {
        case ProductTags::meble: sso << "Meble "; break;
        case ProductTags::rozrywka: sso << "Rozrywka "; break;
        case ProductTags::sport: sso << "Sport "; break;
        case ProductTags::uroda: sso << "Uroda "; break;
        case ProductTags::zywnosc: sso << "Żywność "; break;
        default: sso << "BŁĘDNY TAG "; break;
        }
    }
    return sso.str();
}

std::string Product::PriceToString() const
{
    unsigned short gr = GetPriceGr()%100;
    unsigned int zl = (GetPriceGr()-gr)/100;
    std::stringstream sso;
    sso << " " << zl << "." << gr << "zl";
    return sso.str();
}
