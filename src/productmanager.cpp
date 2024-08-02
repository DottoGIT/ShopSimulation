#include "productmanager.h"
#include "productnotfoundexception.h"


void ProductManager::AddProduct(const Product& product)
{
    products.push_back(product);
    Logger::Info("<productManager.h> produkt " + product.GetName() + " o id: " + std::to_string(product.GetId()) + " zostal dodany do bazy");
}

Product ProductManager::FindProductById(unsigned id)
{
    for (const auto& product : products)
    {
        if (product.GetId() == id){
            Logger::Debug("<productManager.h> Produkt o id " + std::to_string(id) + " zostal znaleziony");
            return product;
        }
    }
    Logger::Warning("<productManager.h> Produkt o id " + std::to_string(id) + " nie zostal znaleziony");
    throw ProductNotFoundException(id);
}

std::vector<Product> ProductManager::GetProductsList(const SearchFilter& searchFilter) const
{
    std::vector<Product> productsToShow;
    // Wybierz tylko produkty spełniające kryteria
    std::copy_if(products.begin(), products.end(), std::back_inserter(productsToShow), [&searchFilter](const auto& p){
        return searchFilter.CheckItem(p);
    });
    // Posortuj listę produktów spełniających kryteria
    std::sort(productsToShow.begin(), productsToShow.end(), [&searchFilter](const Product& p1, const Product& p2){
        return searchFilter.GetSortCompariser(p1, p2);
    });
    return productsToShow;
}

std::vector<Product> ProductManager::GetProductsList() const
{
    return products;
}
