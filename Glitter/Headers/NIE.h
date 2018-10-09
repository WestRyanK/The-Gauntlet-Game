#pragma once

#include <stdexcept>
#include <string>

class NotImplementedException : public std::logic_error
{
public:
    NotImplementedException(std::string method_name): std::logic_error("Function not implemented yet: " + method_name) { };
};