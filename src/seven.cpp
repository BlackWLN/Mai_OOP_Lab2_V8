#include "../include/seven.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>

Seven::Seven() : data(nullptr), size(0) {}

Seven::~Seven() noexcept {
    delete[] data;
    data = nullptr;
    size = 0;
}

Seven::Seven(const size_t &n, unsigned char defaultVal) {
    if (defaultVal > 6)
        throw std::invalid_argument("Digit must be in [0..6]");
    size = n;
    data = new unsigned char[size];
    std::fill(data, data + size, defaultVal);
}

Seven::Seven(const std::initializer_list<unsigned char> &initVals) {
    size = initVals.size();
    data = new unsigned char[size];
    size_t i = 0;

    for (unsigned char val : initVals) {
        if (val > 6)
        throw std::string("Digit must be in [0..6]");
        data[i++] = val;
    }
}

Seven::Seven(const std::string &srcStr) {
    size = srcStr.size();
    data = new unsigned char[size];

    for (size_t i = 0; i < size; ++i) {
        char c = srcStr[i];
        if (!std::isdigit(c) || c < '0' || c > '6')
        throw std::invalid_argument("Invalid base-7 digit");
        data[i] = c - '0';
    }
}

Seven::Seven(const Seven &other) {
    size = other.size;
    data = new unsigned char[size];
    std::copy(other.data, other.data + size, data);
}

Seven::Seven(Seven &&other) noexcept : data(other.data), size(other.size) {
    other.data = nullptr;
    other.size = 0;
}

Seven &Seven::operator=(const Seven &other) {

    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new unsigned char[size];
        std::copy(other.data, other.data + size, data);
  }
    return *this;
}

Seven &Seven::operator=(Seven &&other) noexcept {

    if (this != &other) {
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
  return *this;
}

Seven Seven::operator+(const Seven &other) const {
    size_t maxSize = std::max(size, other.size);
    size_t resultSize = maxSize + 1;
    unsigned char *resultData = new unsigned char[resultSize]();
    unsigned char carry = 0;

    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char a = (i < size) ? data[i] : 0;
        unsigned char b = (i < other.size) ? other.data[i] : 0;
        unsigned char sum = a + b + carry;
        resultData[i] = sum % 7;
        carry = sum / 7;
    }
    resultData[maxSize] = carry;

    while (resultSize > 1 && resultData[resultSize - 1] == 0)
        --resultSize;

    Seven result;
    result.size = resultSize;
    result.data = new unsigned char[resultSize];
    std::copy(resultData, resultData + resultSize, result.data);
    delete[] resultData;

    return result;
}

Seven Seven::operator-(const Seven &other) const {
    if (!(*this >= other))
        throw std::invalid_argument("Subtraction would result in negative number");

    size_t resultSize = size;
    unsigned char *resultData = new unsigned char[resultSize]();
    int borrow = 0;
    for (size_t i = 0; i < resultSize; ++i) {
        int a = (i < size) ? data[i] : 0;
        int b = (i < other.size) ? other.data[i] : 0;
        a -= borrow;
        if (a < b) {
            a += 7;
            borrow = 1;
        } else
            borrow = 0;
        resultData[i] = a - b;
    }

    while (resultSize > 1 && resultData[resultSize - 1] == 0)
        --resultSize;

    Seven result;
    result.size = resultSize;
    result.data = new unsigned char[resultSize];
    std::copy(resultData, resultData + resultSize, result.data);
    delete[] resultData;

    return result;
}

bool Seven::operator==(const Seven &other) const {

    if (size != other.size)
        return false;

    for (size_t i = 0; i < size; ++i)
        if (data[i] != other.data[i])
            return false;

    return true;
}

bool Seven::operator>=(const Seven &other) const {

    if (size > other.size)
        return true;

    if (size < other.size)
        return false;

    for (size_t i = size; i > 0; --i) {
        if (data[i - 1] > other.data[i - 1])
            return true;
        if (data[i - 1] < other.data[i - 1])
            return false;
    }
        return true;
}

std::ostream &operator<<(std::ostream &os, const Seven &f) {
    if (f.size == 0) {
        os << '0';
        return os;
    }
    for (size_t i = f.size; i > 0; --i)
        os << static_cast<int>(f.data[i - 1]);
    return os;
}