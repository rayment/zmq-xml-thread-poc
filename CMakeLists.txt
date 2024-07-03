cmake_minimum_required(VERSION 3.27)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(zmq-xml-thread-poc LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

include(cmake/contrib.cmake)
if(WIN32 AND MINGW)
    include(cmake/mingw_deploy.cmake)
endif() # WIN32 AND MINGW

add_executable(piper)

target_sources(
    piper PRIVATE
    src/main.cpp
    src/processor/filter.cpp
    src/processor/node.cpp
    src/processor/sink.cpp
    src/processor/tap.cpp
    src/processor/sinks/sink_file.cpp
    src/processor/taps/tap_file.cpp
    src/types/uuid.cpp
    src/util/file_io.cpp
    src/xml/xml_document.cpp
    src/xml/xml_schema.cpp
    src/xml/xml_validator.cpp
    src/xml/node/xml_node.cpp
    src/xml/node/xml_node_cdata.cpp
    src/xml/node/xml_node_comment.cpp
    src/xml/node/xml_node_element.cpp
    src/xml/node/xml_node_text.cpp
)

target_include_directories(
    piper PRIVATE src ${CMAKE_BINARY_DIR}/gen
)

target_link_libraries(
    piper PRIVATE
    fmt::fmt
    LibXml2::LibXml2
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    libzmq
)

file(READ xsd/xsd-pipe.xsd XSD_FILE_CONTENT)
configure_file(xsd/xsd_pipe.hpp.in gen/xsd/xsd_pipe.hpp @ONLY)
