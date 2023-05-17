#pragma once
#include <iostream>

template<template <class T, class Allocator = std::allocator<T>> class Container>
void myHistoOutput(Container<double> res, double min, double max, size_t quantity_of_elemes, size_t stocks, std::ostream& out) {
    int64_t precision = static_cast<int64_t>(std::log10(static_cast<double>(quantity_of_elemes)));
    out << std::fixed << std::setprecision(precision) << std::right;
    for (size_t i = 0; i < res.size(); ++i) {
        out << "[" << std::setprecision(precision - 3) <<
            std::setw(static_cast<int64_t>(static_cast<int64_t>(std::log10(max)) + precision + (min < 0 ? 1 : 0)) - 1)
            << (min + i * ((max - min)) / res.size()) << ";"
            << std::setw(static_cast<int64_t>(static_cast<int64_t>(std::log10(max)) + precision + (min < 0 ? 1 : 0)) - 1)
            << (min + (i + 1) * ((max - min)) / res.size())
            << "]     "
            << std::setprecision(precision)
            << res[i]
            << std::endl;
    }
}

template<template <class T> class Container>
void myHistoOutput(Container<double> res, double min, double max, size_t quantity_of_elemes, size_t stocks, std::ostream& out) {
    int64_t precision = static_cast<int64_t>(std::log10(static_cast<double>(quantity_of_elemes)));
    out << std::fixed << std::setprecision(precision) << std::right;
    for (size_t i = 0; i < res.size(); ++i) {
        out << "[" << std::setprecision(precision - 3) <<
            std::setw(static_cast<int64_t>(static_cast<int64_t>(std::log10(max)) + precision + (min < 0 ? 1 : 0)) - 1)
            << (min + i * ((max - min)) / res.size()) << ";"
            << std::setw(static_cast<int64_t>(static_cast<int64_t>(std::log10(max)) + precision + (min < 0 ? 1 : 0)) - 1)
            << (min + (i + 1) * ((max - min)) / res.size())
            << "]     "
            << std::setprecision(precision)
            << res[i]
            << std::endl;
    }
}


void ClearConsole()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

inline void loading() {
    std::cout << "Loading, wait please..." << std::endl;
}

inline size_t introduction() {
    size_t num = 0;
    std::cout << "Welcome. Choose pseudo-generator:" << std::endl
        << "Plain distribution:" << std::endl
        << "   0. Hardware random (if hardware random is available for your OS)" << std::endl
        << "   1. Linear congruential" << std::endl
        << "   2. Square linear congruential" << std::endl
        << "   3. Fibonacci congruential" << std::endl
        << "   4. Reverse congruential" << std::endl
        << "All next generators actually are complicated generators (they use plain generators for working)" << std::endl
        << "Plain distribution:" << std::endl
        << "   5. (First_gen - Second_gen) congruential" << std::endl
        << "Normal distribution:" << std::endl
        << "   6. \"3-sigma rule\"" << std::endl
        << "   7. Polar cordinates method" << std::endl
        << "   8. Ratio method" << std::endl
        << "Exponential distribution:" << std::endl
        << "   9. Logarithm method" << std::endl
        << "Gamma distribution:" << std::endl
        << "   10. Arens's method for gamma distribution with rate parameter > 1" << std::endl
        << " Write num ( 0 - 10 )" << std::endl;
    std::cin >> num;
    return num;
}

inline size_t repeat_text() {
    size_t num;
    std::cout
        << "Plain distribution:" << std::endl
        << "   0. Hardware random (if hardware random is available for your OS)" << std::endl
        << "   1. Linear congruential" << std::endl
        << "   2. Square linear congruential" << std::endl
        << "   3. Fibonacci congruential" << std::endl
        << "   4. Reverse congruential" << std::endl
        << "All next generators actually are complicated generators (they use plain generators for working)" << std::endl
        << "Plain distribution:" << std::endl
        << "   5. (First_gen - Second_gen) congruential" << std::endl
        << "Normal distribution:" << std::endl
        << "   6. \"3-sigma rule\"" << std::endl
        << "   7. Polar cordinates method" << std::endl
        << "   8. Ratio method" << std::endl
        << "Exponential distribution:" << std::endl
        << "   9. Logarithm method" << std::endl
        << "Gamma distribution:" << std::endl
        << "   10. Arens's method for gamma distribution with rate parameter > 1" << std::endl
        << " Write num ( 0 - 10 )" << std::endl
        << std::endl
        << "If you want to call another method, write method's num ( 0 - 10 )" << std::endl
        << "in else way, write a number, bigger than 10, or anything else." << std::endl
        << "!!!   If you just close, there will be a MEMORY LEAK  !!!" << std::endl;
    std::cin >> num;
    return num;
}