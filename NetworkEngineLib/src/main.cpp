#include "NetworkEngine.hpp"
#include <iostream>

int main() {
    std::cout << "Starting MMM Network Engine..." << std::endl;

    // OKX Perpetual BTC-USDT 무기한 선물 스트림 시작
    run_okx_perpetual_stream("BTC-USDT-SWAP");

    return 0;
}