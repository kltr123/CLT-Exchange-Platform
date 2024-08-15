#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain
{
public:
    MerkelMain();
    /** Call this to start the sim */
    void init();

private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);

    // Start of Assignment Items
    void printCandlestickTable();
    void printCandlestickPlot();
    void printAdditionalPlot();
    void processUserTableSelection(int userSelection);
    void processUserPlotSelection(int userSelection);
    void processUserAdditionalPlotSelection(int userSelection);
    // Task 2 & 3
    std::vector<Candlestick> getBidCandlestickData(std::string product);
    std::vector<Candlestick> getAskCandlestickData(std::string product);
    // End of Assignment Items

    std::string currentTime;
    OrderBook orderBook{"20200317.csv"};
    Wallet wallet;
};
