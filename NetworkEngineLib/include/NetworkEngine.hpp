#ifndef NETWORK_ENGINE_HPP
#define NETWORK_ENGINE_HPP

#include <string>

// OKX Perpetual(선물) 스트림을 시작하는 함수
void run_okx_perpetual_stream(const std::string& instId = "BTC-USDT-SWAP");

#endif