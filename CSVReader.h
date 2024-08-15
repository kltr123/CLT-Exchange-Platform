#pragma once

#include "OrderBookEntry.h"
#include "Candlestick.h"
#include <vector>
#include <string>

class CSVReader
{
    public:
        CSVReader();

        static std::vector<OrderBookEntry> readCSV(std::string csvFile);

        static std::vector<std::string> tokenise(std::string csvLine, char separator);
    
        static OrderBookEntry stringsToOBE(std::string price, 
                                        std::string amount, 
                                        std::string timestamp, 
                                        std::string product, 
                                        OrderBookType OrderBookType);
        // Start of Assignment Items
        static std::vector<Candlestick> readCSVCandlestick(std::string csvFile);
        // End of Assignment Items
    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
     
};