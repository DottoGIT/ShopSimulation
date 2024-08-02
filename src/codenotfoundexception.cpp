#include "codenotfoundexception.h"

CodeNotFoundException::CodeNotFoundException(std::string wrongCode) :
    std::invalid_argument("Couldnt find the code: " + wrongCode) {}
