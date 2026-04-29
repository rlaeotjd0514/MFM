#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif

#include <string>
#include <functional>
#include <chrono>
#include <boost/date_time.hpp>

class BaseConnector;

enum class TransactionType { LONG, SHORT };
enum class ContractType { LIMIT, MARKET, LOC };

class BaseTransaction {
public:
    BaseTransaction()=default;
private:
    std::string _t_id;
    TransactionType _t_type;
    ContractType _c_type;
    std::weak_ptr<BaseConnector> _connector;
    std::string _symbol;
    double _entry_price;
    double _current_price;
    double _pnl;
    double _break_even_price;
    std::string _transaction_status;
    double _profit;
    std::function<bool()> _sl_logic;
    std::function<bool()> _tp_logic;
    std::chrono::system_clock::time_point _start_time;
    std::chrono::system_clock::time_point _end_time;
};
