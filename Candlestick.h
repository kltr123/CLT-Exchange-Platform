#pragma once
#include <string>
#include <vector>
#include "OrderBookEntry.h"

class Candlestick
{
public:
    // Properties
    Candlestick(std::string dateTime,
                std::string product,
                std::string type,
                double high,
                double low,
                double open,
                double close);
    std::string dateTime;
    std::string product;
    std::string type;
    double high;
    double low;
    double open;
    double close;

    // Task 1
    void printCandlestick();
    static void printCandlestickTable(std::vector<Candlestick> candles);
};