#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <boost/signals2.hpp>
#include <ranges>
#include "BasePriceTick.hpp"

class BaseTransaction;

class BaseConnector {
public:
    BaseConnector(std::string APIKEY, std::string WS_KEY) : OPENAPI_KEY(APIKEY), WS_KEY(WS_KEY) {};
    virtual ~BaseConnector() = default;
    virtual BaseTransaction withdraw(double amount);
    virtual BaseTransaction deposit(double amount);
    virtual BaseTransaction start_transaction(BaseTransaction transaction);
    std::vector<BaseTransaction> get_transaction_list();
    virtual bool connect() = 0;
    virtual bool isconnected() = 0;
    virtual bool add_price_stream(std::string symbol) = 0;
    std::vector<std::string> get_list_subscription(){
        auto name_list = _subscription_list | std::views::keys;
        return std::vector<std::string>(name_list.begin(), name_list.end());
    }

protected:
    const std::string OPENAPI_KEY;
    const std::string WS_KEY;
    double _current_balance;
    std::vector<std::shared_ptr<BaseTransaction>> _current_position;
    std::unordered_map<std::string, std::shared_ptr<boost::signals2::signal<void(const BasePriceTick&)>>> _subscription_list;
};
