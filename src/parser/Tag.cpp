#include "Tag.h"

using namespace std;

Tag::Tag(const string& key, const string& value) : key(key), value(value) {}

const string& Tag::getKey() const {
    return key;
}

const string& Tag::getValue() const {
    return value;
}