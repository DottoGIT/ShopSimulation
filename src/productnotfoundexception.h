#pragma once

#ifndef PRODUCTNOTFOUNDEXCEPTION_H
#define PRODUCTNOTFOUNDEXCEPTION_H

#include <stdexcept>

class ProductNotFoundException : std::invalid_argument
{
public:
    ProductNotFoundException(unsigned wrong_id);
};

#endif // PRODUCTNOTFOUNDEXCEPTION_H
