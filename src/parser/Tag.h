#pragma once

#include <string>

class Tag {
    std::string key;
    std::string value;

public:
    Tag(const std::string& key, const std::string& value);

    const std::string& getKey() const;
    const std::string& getValue() const; 
};