cmake_minimum_required(VERSION 3.20)
project(NetworkEngineLib)

# 정책 설정 (FindBoost 경고 방지)
cmake_policy(SET CMP0167 NEW)

# 1. 패키지 로드
find_package(Boost REQUIRED COMPONENTS json)
find_package(OpenSSL REQUIRED)

# 2. 타겟 정의
add_library(NetworkEngineLib STATIC src/NetworkEngine.cpp include/NetworkEngine.hpp)
add_executable(NetworkEngineApp src/main.cpp)

# 3. 헤더 경로 설정 (격리 원칙 준수)
target_include_directories(NetworkEngineLib
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 4. 라이브러리 연결 (JSON 컴포넌트 포함)
target_link_libraries(NetworkEngineLib
    PRIVATE
        Boost::json
        OpenSSL::SSL
        OpenSSL::Crypto
)

# App에도 동일하게 연결
target_link_libraries(NetworkEngineApp
    PRIVATE
        NetworkEngineLib
        Boost::json
        OpenSSL::SSL
        OpenSSL::Crypto
)

# 5. MSVC 옵션
if(MSVC)
    target_compile_options(NetworkEngineLib PRIVATE /W4 /utf-8 /permissive-)
    target_compile_definitions(NetworkEngineLib PRIVATE
        _WIN32_WINNT=0x0A00
        BOOST_ASIO_NO_DEPRECATED
    )
endif()