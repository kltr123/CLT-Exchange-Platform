#include "Candlestick.h"
#include "CandlestickCalculation.h"
#include "OrderBook.h"
#include <iostream>
#include <iomanip>

// Task 1
Candlestick::Candlestick(std::string dateTime,
                         std::string product,
                         std::string type,
                         double high,
                         double low,
                         double open,
                         double close)
    : dateTime(dateTime),
      product(product),
      type(type),
      high(high),
      low(low),
      open(open),
      close(close)
{
}

void Candlestick::printCandlestick()
{
    std::cout << std::setw(30) << std::left << dateTime;
    std::cout << std::setw(15) << std::left << product;
    std::cout << std::setw(15) << std::left << type;
    std::cout << std::setw(15) << std::left << open;
    std::cout << std::setw(15) << std::left << high;
    std::cout << std::setw(15) << std::left << low;
    std::cout << std::setw(15) << std::left << close;
    std::cout << std::endl;
}
void Candlestick::printCandlestickTable(std::vector<Candlestick> candles)
{
    std::cout << "\n" << std::setw(30) << std::left << "Date/Time";
    std::cout << std::setw(15) << std::left << "Product";
    std::cout << std::setw(15) << std::left << "OrderType";
    std::cout << std::setw(15) << std::left << "Open";
    std::cout << std::setw(15) << std::left << "High";
    std::cout << std::setw(15) << std::left << "Low";
    std::cout << std::setw(15) << std::left << "Close";
    std::cout << std::endl;

    for (Candlestick &e : candles)
    {
        e.printCandlestick();
    }
}
