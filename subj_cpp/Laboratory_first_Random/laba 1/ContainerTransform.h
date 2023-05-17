#pragma once
#include <cstdint>
#include <vector> // for std::allocator
#include <iostream>
#include <iomanip>

template<template <class T, class Allocator = std::allocator<T>> class Container>
inline Container<double> toHisto(Container<double> const& gen, double min, double max, size_t stocks) { //operator[], .size()

    Container<size_t> tmp(stocks);
    for (size_t i = 0; i != stocks; ++i) {
        tmp[i] = 0;
    }
    for (size_t i = 0; i != gen.size(); ++i) {
        ++tmp[static_cast<size_t>(stocks*(gen[i] - min) / (max - min))];
    }
    Container<double> res(stocks);
    for (size_t i = 0; i != res.size(); ++i) {
        res[i] = 0;
    }
    for (size_t i = 0; i != res.size(); ++i) {
        res[i] = static_cast<double>(tmp[i]) / gen.size();
    }
    return res;
}

template<template <class T> class Container>
inline Container<double> toHisto(Container<double> const& gen, double min, double max, size_t stocks) { //operator[], .size()

    Container<size_t> tmp(stocks);
    for (size_t i = 0; i != stocks; ++i) {
        tmp[i] = 0;
    }
    for (size_t i = 0; i != gen.size(); ++i) {
        ++tmp[static_cast<size_t>(stocks * (gen[i] - min) / (max - min))];
    }
    Container<double> res(stocks);
    for (size_t i = 0; i != res.size(); ++i) {
        res[i] = 0;
    }
    for (size_t i = 0; i != res.size(); ++i) {
        res[i] = static_cast<double>(tmp[i]) / gen.size();
    }
    return res;
}
