#pragma once
#include <string>
#include <vector>
#include "Candlestick.h"
#include "OrderBookEntry.h"

class CandlestickCalculation
{
public:
    static std::vector<Candlestick> calculateCandlesticks(std::vector<OrderBookEntry> entries);
};
