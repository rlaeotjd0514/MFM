cmake_minimum_required(VERSION 3.20)
project(BackTester)

add_executable(BackTester src/main.cpp)

# 3. 헤더 경로 설정 (격리 원칙 준수)
target_include_directories(BackTester
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(BackTester
PRIVATE
TradeCenterConnector)