#ifndef OKXCONNECTOR_HPP
#define OKXCONNECTOR_HPP
#endif // OKXCONNECTOR_HPP

#include "../Base/BaseConnector.hpp"
#include "../Base/BaseTransaction.hpp"
#include "OKXPriceTick.h"
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <ranges>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;
namespace json = boost::json;
using tcp = net::ip::tcp;

class OKXConnector : public BaseConnector, std::enable_shared_from_this<OKXConnector> {
public:
    OKXConnector(std::string APIKEY, std::string WS_KEY) : BaseConnector(APIKEY, WS_KEY) {}
    bool connect() override {
        ssl::context ctx{ssl::context::tlsv12_client};
        ctx.set_verify_mode(ssl::verify_none); // 개발용 인증서 검증 생략

        tcp::resolver resolver{ioc};
        // beast::tcp_stream을 사용하여 타임아웃 처리를 용이하게 함
        ws = std::make_unique<websocket::stream<beast::ssl_stream<beast::tcp_stream>>>(ioc, ctx);

        // 1. DNS Resolution
        auto const results = resolver.resolve(ws_connect_string, ws_connect_port);

        // 2. TCP Connect (asio::connect를 사용하여 주소 리스트 대응)
        beast::get_lowest_layer(*ws).connect(results);

        // 3. SSL SNI 설정 (가장 중요: 핸드셰이크 실패 해결책)
        if(!SSL_set_tlsext_host_name(ws->next_layer().native_handle(), ws_connect_string.c_str())) {
            throw beast::system_error(
                beast::error_code(static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()),
                "Failed to set SNI Hostname"
                );
        }

        // 4. SSL Handshake
        ws->next_layer().handshake(ssl::stream_base::client);

        // 5. WebSocket Handshake
        ws->handshake(ws_connect_string, ws_connect_path);
        return true;
    }

    bool isconnected() override {
        return true;
    }

    bool add_price_stream(std::string symbol) override {
        json::object subscribe_msg;
        subscribe_msg["op"] = "subscribe";
        subscribe_msg["args"] = json::array{
            {{"channel", "tickers"}, {"instId", symbol}},
        };
        int sent = ws->write(net::buffer(json::serialize(subscribe_msg)));
        _subscription_list.insert({symbol, std::make_shared<boost::signals2::signal<void(const BasePriceTick&)>>(boost::signals2::signal<void(const BasePriceTick&)>())});
        return sent == symbol.size();
    }

private:
    const std::string ws_connect_string = "ws.okx.com";
    const std::string ws_connect_port = "8443";
    const std::string ws_connect_path = "/ws/v5/public";
    net::io_context ioc;
    std::unique_ptr<websocket::stream<beast::ssl_stream<beast::tcp_stream>>> ws;

    void do_read() {
        // self-reference를 캡처하여 비동기 작업 동안 객체 생존 보장
        auto self(shared_from_this());

        ws->async_read(_buffer,
       [this, self](beast::error_code ec, std::size_t bytes_transferred) {
           if (!ec) {               
                // 1. 시그널 발생 (데이터 전송)
                //std::string rawdata = beast::buffers_to_string(_buffer.data());
                std::string_view sv{static_cast<const char*>(_buffer.data().data()), _buffer.data().size()};
                const auto& currenttick = parsejson(sv);

                // 2. 버퍼 비우기
                _buffer.consume(bytes_transferred);

                auto cur_sig = _subscription_list[currenttick.symbol];
                (*cur_sig)(currenttick);
                // 3. 비동기 재귀 호출: 다음 메시지 읽기 예약
                do_read();
           } else {
               std::cout << ec.message() << "\n";
           }
       });
    }

    OKXPriceTick parsejson(std::string_view rawdata) const {
        OKXPriceTick ret;
        auto json = json::parse(rawdata).as_object();

        if(json.contains("event") == true) {
            // op명령에 대한 내용 로그 기록
        }
        else if(json.contains("arg") && json.contains("data")) {
            std::string channel = json.at("arg").as_object().at("channel").as_string().c_str();
            json::value const& data_arr = json.at("data").as_array()[0];
            if(channel == "tickers") {
                auto symbol = data_arr.at("instId").as_string();
                std::copy_n(symbol.data(), std::min(symbol.size(), ret.symbol.size() - 1), ret.symbol.begin());
                auto tick = data_arr.at("ts").as_string();
                long long ts = 0;
                std::from_chars(tick.begin(), tick.end(), ts);
                ret.point = std::chrono::system_clock::time_point{std::chrono::milliseconds(ts)};
                ret.price = data_arr.at("last").as_double();
                return ret;
            }
            if(channel == "candlestick") {
                // 캔듣 스틱 관련 데이터 작성
            }
        }
        return {};
    }

    static constexpr std::string_view channel_str = "\"channel\":\"";
    static constexpr std::string_view price_str = "\"last\":\"";
    static constexpr std::string_view end_str = "\"";
    OKXPriceTick parsejson_raw(std::string_view rawdata) const {
        OKXPriceTick ret;
        string_util::findjsonstring(rawdata, price_str);
        double price = 0.0;
        std::from_chars(_price.data(), _price.data() + _price.size(), price, std::chars_format::general);
    }

    beast::flat_buffer _buffer;
};
