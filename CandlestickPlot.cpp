#include "CandlestickPlot.h"
#include <iostream>
#include <iomanip>

// Task 2
void CandlestickPlot::printCandlestickPlot(std::vector<Candlestick> candles)
{
    double highest = candles[0].high;
    double lowest = candles[0].low;
    for (Candlestick &e : candles)
    {
        // returns the greater value
        highest = std::max(highest, e.high);
        // returns the lower value
        lowest = std::min(lowest, e.low);
    }

    const int steps = 60; // Number of steps in the y-axis
    double yRange = highest - lowest;

    // Ensure the lowest "low" value is covered in the steps
    double newLowest = lowest - 0.05 * yRange;   // Add some buffer to ensure the lowest "low" is within the range
    double newHighest = highest + 0.05 * yRange; // Add some buffer to ensure the lowest "high" is within the range
    double newYRange = newHighest - newLowest;
    double stepSize = newYRange / steps;

    for (double y = newHighest; y > newLowest; y -= stepSize)
    {
        std::cout << std::setw(15) << std::left << y;
        int maxSize = candles.size();

        for (int i = 0; i < maxSize; i++)
        {
            Candlestick candle = candles[i];
            // the empty spaces of the plot
            if (y > candle.high || y < candle.low)
            {
                std::cout << "     ";
            }
            // the "stem" part of the candlestick
            else if ((y <= candle.high && y > candle.open && y > candle.close) ||
                     (y >= candle.low && y < candle.open && y < candle.close))
            {
                std::cout << "  |  ";
            }
            // the "positive" part of the candlestick
            else if ((candle.open < candle.close))
            {
                std::cout << " +++ ";
            }
            // the "negative" part of the candlestick
            else if ((candle.open > candle.close))
            {
                std::cout << " --- ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Task 3 Candlestick Plot
void CandlestickPlot::printAdditionalCandlestickPlot(std::vector<Candlestick> candles)
{
    double highest = candles[0].high;
    double lowest = candles[0].low;
    for (Candlestick &e : candles)
    {
        // returns the greater value
        highest = std::max(highest, e.high);
        // returns the lower value
        lowest = std::min(lowest, e.low);
    }

    const int steps = 80; // Number of steps in the y-axis
    double yRange = highest - lowest;
    double stepSize = yRange / steps;

    for (double y = highest; y > lowest; y -= stepSize)
    {
        std::cout << std::setw(15) << std::left << y;
        int maxSize = 30;

        if (maxSize > candles.size())
        {
            int maxSize = candles.size();
        }

        for (int i = 0; i < maxSize; i++)
        {
            Candlestick candle = candles[i];
            // the empty spaces of the plot
            if (y > candle.high || y < candle.low)
            {
                std::cout << "     ";
            }
            // the "stem" part of the candlestick
            else if ((y <= candle.high && y > candle.open && y > candle.close) ||
                     (y >= candle.low && y < candle.open && y < candle.close))
            {
                std::cout << "  |  ";
            }
            // the "positive" part of the candlestick
            else if ((candle.open < candle.close))
            {
                std::cout << " +++ ";
            }
            // the "negative" part of the candlestick
            else if ((candle.open > candle.close))
            {
                std::cout << " --- ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


// Task 3 Area Plot
void CandlestickPlot::printAdditionalAreaPlot(std::vector<Candlestick> candles)
{
    double highest = candles[0].high;
    double lowest = candles[0].low;
    for (Candlestick &e : candles)
    {
        // returns the greater value
        highest = std::max(highest, e.high);
        // returns the lower value
        lowest = std::min(lowest, e.low);
    }

    const int steps = 80; // Number of steps in the y-axis
    double yRange = highest - lowest;

    double newLowest = lowest - 0.05 * yRange;   // Add some buffer to ensure the lowest "low" is within the range
    double newHighest = highest + 0.05 * yRange; // Add some buffer to ensure the lowest "high" is within the range
    double newYRange = newHighest - newLowest;
    double stepSize = newYRange / steps;

    for (double y = newHighest; y > newLowest; y -= stepSize)
    {
        std::cout << std::setw(15) << std::left << y;
        int maxSize = 30;

        if (maxSize > candles.size())
        {
            int maxSize = candles.size();
        }

        for (int i = 0; i < maxSize; i++)
        {
            Candlestick candle = candles[i];
            // the empty spaces of the plot
            if (y > candle.high)
            {
                std::cout << "     ";
            }
            // show " +++ " for the area plot if the "close" is more than "open"
            else if ((candle.open < candle.close))
            {
                std::cout << " +++ ";
            }
            // show " --- " for the area plot if the "close" is more than "open"
            else if ((candle.open > candle.close))
            {
                std::cout << " --- ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
