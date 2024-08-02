#pragma once

#ifndef CODENOTFOUNDEXCEPTION_H
#define CODENOTFOUNDEXCEPTION_H

#include <stdexcept>

class CodeNotFoundException : std::invalid_argument
{
public:
    CodeNotFoundException(std::string wrongCode);
};

#endif // CODENOTFOUNDEXCEPTION_H
