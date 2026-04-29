#ifndef BASEPRICETICK_HPP
#define BASEPRICETICK_HPP
#pragma once

#endif // BASEPRICETICK_HPP
#include <chrono>
#include <string>
#include <array>

class BasePriceTick {
public:
    double price;
    std::array<char, 32> symbol = {'\0',};
    std::chrono::system_clock::time_point point;
};