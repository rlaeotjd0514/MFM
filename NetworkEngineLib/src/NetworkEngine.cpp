#include "NetworkEngine.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/json.hpp>
#include <iostream>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;
namespace json = boost::json;
using tcp = net::ip::tcp;

void run_okx_perpetual_stream(const std::string& instId) {
    try {
        std::string host = "ws.okx.com";
        std::string port = "8443";
        std::string path = "/ws/v5/public";

        net::io_context ioc;
        ssl::context ctx{ssl::context::tlsv12_client};
        ctx.set_verify_mode(ssl::verify_none); // 개발용 인증서 검증 생략

        tcp::resolver resolver{ioc};
        // beast::tcp_stream을 사용하여 타임아웃 처리를 용이하게 함
        websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws{ioc, ctx};

        // 1. DNS Resolution
        auto const results = resolver.resolve(host, port);

        // 2. TCP Connect (asio::connect를 사용하여 주소 리스트 대응)
        beast::get_lowest_layer(ws).connect(results);

        // 3. SSL SNI 설정 (가장 중요: 핸드셰이크 실패 해결책)
        if(! SSL_set_tlsext_host_name(ws.next_layer().native_handle(), host.c_str())) {
            throw beast::system_error(
                beast::error_code(static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()),
                "Failed to set SNI Hostname"
                );
        }

        // 4. SSL Handshake
        ws.next_layer().handshake(ssl::stream_base::client);

        // 5. WebSocket Handshake
        ws.handshake(host, path);
        std::cout << ">>> Connected to OKX Perpetual WebSocket: " << instId << std::endl;

        // 6. Subscribe Message (JSON)
        json::object subscribe_msg;
        subscribe_msg["op"] = "subscribe";
        subscribe_msg["args"] = json::array{
            {{"channel", "tickers"}, {"instId", instId}},
            {{"channel", "books5"}, {"instId", instId}}
        };
        ws.write(net::buffer(json::serialize(subscribe_msg)));

        // 7. Data Receive Loop
        for (;;) {
            beast::flat_buffer buffer;
            ws.read(buffer);

            std::string raw_data = beast::buffers_to_string(buffer.data());
            json::value jv = json::parse(raw_data);
            json::object const& obj = jv.as_object();
            std::cout << raw_data << "\n";

            continue;
            if (obj.contains("event")) continue;

            if (obj.contains("arg") && obj.contains("data")) {
                std::string channel = obj.at("arg").as_object().at("channel").as_string().c_str();
                json::array const& data_arr = obj.at("data").as_array();

                if (channel == "tickers") {
                    auto const& ticker = data_arr[0].as_object();
                    std::cout << "[Ticker] " << instId << " Price: " << ticker.at("last") << std::endl;
                }
                else if (channel == "books5") {
                    auto const& book = data_arr[0].as_object();
                    auto const& ask = book.at("asks").as_array()[0].as_array();
                    auto const& bid = book.at("bids").as_array()[0].as_array();
                    std::cout << "[Orderbook] Ask: " << ask[0] << " | Bid: " << bid[0] << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
    }
}