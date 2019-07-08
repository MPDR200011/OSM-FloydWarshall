#pragma once

#include <exception>

class NonExistantNode : public std::exception {
    unsigned long id;
public:
    NonExistantNode(const unsigned long id);
    const char * what() const noexcept override;
};