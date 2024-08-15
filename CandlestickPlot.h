#pragma once
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "Candlestick.h"

class CandlestickPlot
{
public:
    // Task 2 & 3
    static void printCandlestickPlot(std::vector<Candlestick> candles);
    static void printAdditionalCandlestickPlot(std::vector<Candlestick> candles);
    static void printAdditionalAreaPlot(std::vector<Candlestick> candles);
};
