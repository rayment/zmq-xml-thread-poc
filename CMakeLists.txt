cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(zmq-xml-thread-poc LANGUAGES C CXX)

include(cmake/contrib.cmake)

add_executable(piper)

target_sources(
    piper PRIVATE
    src/main.cpp
    src/xml_document.cpp
)

target_link_libraries(
    piper PRIVATE
    fmt::fmt
    LibXml2::LibXml2
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    libzmq
)
