cmake_minimum_required(VERSION 3.20)

project(MMM LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


# 2. C++ 표준 설정
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(NetworkEngineLib)
add_subdirectory(TradeLogic)
add_subdirectory(BackTester)
add_subdirectory(TradeCenterConnector)
add_subdirectory(DataManager)
add_subdirectory(Util)
add_subdirectory(MainApp)

add_executable(MMM
  main.cpp
  xingcore.h xingcore.cpp
)
target_link_libraries(MMM PRIVATE Qt${QT_VERSION_MAJOR}::Core)

include(GNUInstallDirs)
target_include_directories(MMM PUBLIC "C:/LS_SEC/xingAPI")
install(TARGETS MMM
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

