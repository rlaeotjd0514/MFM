#include <iostream>
#include "../OKX/OKXConnector.hpp"

int main() {
    std::shared_ptr<OKXConnector> _okx_conn = std::make_shared<OKXConnector>("FC23D134A35DD3A57C349CC576881E4D", "");
    _okx_conn->connect();
    _okx_conn->add_price_stream("BTC-USDT-SWAP");
    _okx_conn->
}