cmake_minimum_required(VERSION 3.20)
project(TradeCenterConnector)

find_package(Boost REQUIRED COMPONENTS json)
find_package(OpenSSL REQUIRED)

add_library(TradeCenterConnector
    STATIC
    Base/BaseConnector.hpp src/BaseConnector.cpp
    Base/BaseTransaction.hpp src/BaseTransaction.cpp
    OKX/OKXConnector.cpp
    OKX/OKXTransaction.cpp
    Base/BasePriceTick.hpp
    OKX/OKXConnector.hpp
    OKX/OKXTransaction.hpp
    OKX/OKXPriceTick.h
)

target_link_libraries(TradeCenterConnector
    PUBLIC
        Boost::system
        Boost::headers
        Boost::json
)

target_include_directories(TradeCenterConnector
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/Base
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
)