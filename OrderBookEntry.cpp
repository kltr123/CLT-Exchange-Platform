#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType, 
                        std::string _username)
: price(_price), 
  amount(_amount), 
  timestamp(_timestamp),
  product(_product), 
  orderType(_orderType),
  username(_username)
{
    
}

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
  if (s == "ask")
  {
    return OrderBookType::ask;
  }
  if (s == "bid")
  {
    return OrderBookType::bid;
  }
  return OrderBookType::unknown;
}

// Start of Assignment Items
std::string OrderBookEntry::obtToString(OrderBookType type)
{
  if (type == OrderBookType::ask)
  {
    return "ask";
  }
  if (type == OrderBookType::bid)
  {
    return "bid";
  }
  return "unknown";
}
// End of Assignment Items