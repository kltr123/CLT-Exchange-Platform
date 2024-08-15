#include "CandlestickCalculation.h"
#include <iostream>

std::vector<Candlestick> CandlestickCalculation::calculateCandlesticks(std::vector<OrderBookEntry> entries)
{
    std::vector<Candlestick> candles;
    std::string product{entries[0].product};
    std::string dateTime{entries[0].timestamp};
    std::string type{OrderBookEntry::obtToString(entries[0].orderType)};

    double high;
    double low;
    double open;
    double close;
    double totalValue;
    double totalAmount;

    std::string firstTimestamp{entries[0].timestamp};

    for (OrderBookEntry &e : entries)
    {
        if (dateTime == e.timestamp)
        {
            totalValue += e.price * e.amount;
            totalAmount += e.amount;
            // returns the greater value
            high = std::max(high, e.price);
            // returns the lower value
            low = std::min(low, e.price);
        }
        else
        {
            // if first timestamp, update value of open.
            if (dateTime == firstTimestamp)
            {
                open = totalValue / totalAmount;
            }
            // push a candle to candles
            else
            {
                close = totalValue / totalAmount;
                candles.push_back(Candlestick{dateTime, product, type, high, low, open, close});
                open = close;
            }
            // reset everything
            dateTime = e.timestamp;
            product = e.product;
            type = OrderBookEntry::obtToString(e.orderType);

            high = low = e.price;
            totalValue = totalAmount = 0;
        }
    }
    // After processing entries, handle the last timestamp
    if (!entries.empty())
    {
        close = totalValue / totalAmount;

        // Create a candlestick for the last timestamp
        candles.push_back(Candlestick{dateTime, product, type, high, low, open, close});
    }
    return candles;
}
