#include "ordernotfoundexception.h"

OrderNotFoundException::OrderNotFoundException(unsigned wrong_id):
    std::invalid_argument("Couldnt find order with id: " + std::to_string(wrong_id)){}
