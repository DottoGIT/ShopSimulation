#pragma once

#ifndef ORDERNOTFOUNDEXCEPTION_H
#define ORDERNOTFOUNDEXCEPTION_H

#include <stdexcept>

class OrderNotFoundException : std::invalid_argument
{
public:
    OrderNotFoundException(unsigned wrong_id);
};

#endif // ORDERNOTFOUNDEXCEPTION_H
