#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "Candlestick.h"
#include "CandlestickCalculation.h"
#include "CandlestickPlot.h"

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an ask " << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;

    // Start of Assignment Items
    // 6 print candlestick table
    std::cout << "6: Print CandleStick Table " << std::endl;
    // 7 print candlestick data plot
    std::cout << "7: Print CandleStick Plot " << std::endl;
    // 8 print additional  data plot
    std::cout << "8: Print Additional Plot (LTC/USD)" << std::endl;
    // End of Assignment Items

    // 9 continue
    std::cout << "9: Continue " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);
            obe.username = "simuser";

            if (wallet.canFulfilOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds." << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid: bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfilOrder(obe))
            {
                std::cout << "Wallet looks good." << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds." << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << " MerkelMain::enterBid: bad input " << std::endl;
        }
    }

    std::cout << "You typed: " << input << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string &p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-9" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    // Start of Assignment Items
    if (userOption == 6)
    {
        printCandlestickTable();
    }
    if (userOption == 7)
    {
        printCandlestickPlot();
    }
    if (userOption == 8)
    {
        printAdditionalPlot();
    }
    // End of Assignment Items
    if (userOption == 9)
    {
        gotoNextTimeframe();
    }
}

// Start of Assignment Items
// Tasks
void MerkelMain::printCandlestickTable()
{
    // choose a product
    std::cout << "printCandlestickTable:: Please select a product!" << std::endl;
    // 1 BTC/USDT
    std::cout << "1: BTC/USDT" << std::endl;
    // 2 DOGE/BTC
    std::cout << "2: DOGE/BTC" << std::endl;
    // 3 DOGE/USDT
    std::cout << "3: DOGE/USDT" << std::endl;
    // 4 ETH/BTC
    std::cout << "4: ETH/BTC" << std::endl;
    // 5 ETH/USDT
    std::cout << "5: ETH/USDT" << std::endl;
    // 6 ALL products
    std::cout << "6: All products" << std::endl;

    int userSelection = 0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userSelection = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "You chose: " << userSelection << std::endl;
    processUserTableSelection(userSelection);
}
void MerkelMain::printCandlestickPlot()
{
    // choose a product
    std::cout << "printCandlestickPlot:: Please select a product!" << std::endl;
    // 1 BTC/USDT
    std::cout << "1: BTC/USDT" << std::endl;
    // 2 DOGE/BTC
    std::cout << "2: DOGE/BTC" << std::endl;
    // 3 DOGE/USDT
    std::cout << "3: DOGE/USDT" << std::endl;
    // 4 ETH/BTC
    std::cout << "4: ETH/BTC" << std::endl;
    // 5 ETH/USDT
    std::cout << "5: ETH/USDT" << std::endl;
    // 6 ALL products
    std::cout << "6: All products" << std::endl;

    int userSelection = 0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userSelection = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "You chose: " << userSelection << std::endl;
    processUserPlotSelection(userSelection);
}
void MerkelMain::printAdditionalPlot()
{
    // choose a plot (candlestick / area)
    std::cout << "printAdditionalPlot:: Please select a type of plot!" << std::endl;
    // 1 Candlestick Plot
    std::cout << "1: LTC/USD Candlestick Plot" << std::endl;
    // 2 Area Plot
    std::cout << "2: LTC/USD Area Plot" << std::endl;
    // 3 All Plot
    std::cout << "3: All Plot" << std::endl;

    int userSelection = 0;
    std::string line;
    std::cout << "Type in 1-3" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userSelection = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "You chose: " << userSelection << std::endl;
    processUserAdditionalPlotSelection(userSelection);
}

void MerkelMain::processUserTableSelection(int userSelection)
{
    if (userSelection == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-5" << std::endl;
    }
    if (userSelection == 1)
    {
        Candlestick::printCandlestickTable(getBidCandlestickData("BTC/USDT"));
        Candlestick::printCandlestickTable(getAskCandlestickData("BTC/USDT"));
    }
    if (userSelection == 2)
    {
        Candlestick::printCandlestickTable(getBidCandlestickData("DOGE/BTC"));
        Candlestick::printCandlestickTable(getAskCandlestickData("DOGE/BTC"));
    }
    if (userSelection == 3)
    {
        Candlestick::printCandlestickTable(getBidCandlestickData("DOGE/USDT"));
        Candlestick::printCandlestickTable(getAskCandlestickData("DOGE/USDT"));
    }
    if (userSelection == 4)
    {
        Candlestick::printCandlestickTable(getBidCandlestickData("ETH/BTC"));
        Candlestick::printCandlestickTable(getAskCandlestickData("ETH/BTC"));
    }
    if (userSelection == 5)
    {
        Candlestick::printCandlestickTable(getBidCandlestickData("ETH/USDT"));
        Candlestick::printCandlestickTable(getAskCandlestickData("ETH/USDT"));
    }
    if (userSelection == 6)
    {
        for (std::string const &p : orderBook.getKnownProducts())
        {
            Candlestick::printCandlestickTable(getBidCandlestickData(p));
            Candlestick::printCandlestickTable(getAskCandlestickData(p));
        }
    }
}

void MerkelMain::processUserPlotSelection(int userSelection)
{
    if (userSelection == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-5" << std::endl;
    }
    if (userSelection == 1)
    {
        std::cout << "BTC/USDT Bid CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getBidCandlestickData("BTC/USDT"));
        std::cout << "BTC/USDT Ask CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getAskCandlestickData("BTC/USDT"));
    }
    if (userSelection == 2)
    {
        std::cout << "DOGE/BTC Bid CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getBidCandlestickData("DOGE/BTC"));
        std::cout << "DOGE/BTC Ask CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getAskCandlestickData("DOGE/BTC"));
    }
    if (userSelection == 3)
    {
        std::cout << "DOGE/USDT Bid CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getBidCandlestickData("DOGE/USDT"));
        std::cout << "DOGE/USDT Ask CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getAskCandlestickData("DOGE/USDT"));
    }
    if (userSelection == 4)
    {
        std::cout << "ETH/BTC Bid CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getBidCandlestickData("ETH/BTC"));
        std::cout << "ETH/BTC Ask CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getAskCandlestickData("ETH/BTC"));
    }
    if (userSelection == 5)
    {
        std::cout << "ETH/USDT Bid CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getBidCandlestickData("ETH/USDT"));
        std::cout << "ETH/USDT Ask CandlestickPlot" << std::endl;
        CandlestickPlot::printCandlestickPlot(getAskCandlestickData("ETH/USDT"));
    }
    if (userSelection == 6)
    {
        for (std::string const &p : orderBook.getKnownProducts())
        {
            std::cout << p << " Bid CandlestickPlot" << std::endl;
            CandlestickPlot::printCandlestickPlot(getBidCandlestickData(p));
            std::cout << p << " Ask CandlestickPlot" << std::endl;
            CandlestickPlot::printCandlestickPlot(getAskCandlestickData(p));
        }
    }
}

void MerkelMain::processUserAdditionalPlotSelection(int userSelection)
{
    std::vector<Candlestick> candles = CSVReader::readCSVCandlestick("LTC-USD.csv");

    if (userSelection == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-2" << std::endl;
    }
    if (userSelection == 1)
    {
        std::cout << "LTC/USD CandlestickPlot" << "\n" << std::endl;
        CandlestickPlot::printAdditionalCandlestickPlot(candles);
    }
    if (userSelection == 2)
    {
        std::cout << "LTC/USD AreaPlot" << "\n" << std::endl;
        CandlestickPlot::printAdditionalAreaPlot(candles);
    }
    if (userSelection == 3)
    {
        std::cout << "LTC/USD CandlestickPlot" << "\n" << std::endl;
        CandlestickPlot::printAdditionalCandlestickPlot(candles);
        std::cout << "LTC/USD AreaPlot" << "\n" << std::endl;
        CandlestickPlot::printAdditionalAreaPlot(candles);
    }
}

std::vector<Candlestick> MerkelMain::getBidCandlestickData(std::string product)
{
    std::vector<OrderBookEntry> bidOrders = orderBook.getOrders(OrderBookType::bid, product);
    std::vector<Candlestick> bidCandles = CandlestickCalculation::calculateCandlesticks(bidOrders);
    return bidCandles;
}
std::vector<Candlestick> MerkelMain::getAskCandlestickData(std::string product)
{
    std::vector<OrderBookEntry> askOrders = orderBook.getOrders(OrderBookType::ask, product);
    std::vector<Candlestick> askCandles = CandlestickCalculation::calculateCandlesticks(askOrders);
    return askCandles;
}

// End of Assignment Items