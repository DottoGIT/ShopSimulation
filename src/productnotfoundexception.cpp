#include "productnotfoundexception.h"

ProductNotFoundException::ProductNotFoundException(unsigned wrong_id):
    std::invalid_argument("Couldnt find product with id: " + std::to_string(wrong_id)){}
