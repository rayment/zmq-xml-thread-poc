set(FMT_TAG_VERSION     10.2.1)
set(JSON_TAG_VERSION    3.11.3)
set(LIBXML2_TAG_VERSION 2.13.1)
set(SPDLOG_TAG_VERSION  1.14.0)
# TODO: Broken build on MinGW. Using master HEAD for now.
#set(ZEROMQ_TAG_VERSION  4.3.5)

include(FetchContent)

set(BUILD_SHARED ON)
set(BUILD_STATIC OFF)
set(BUILD_SHARED_LIBS ON)

include(cmake/deps/fmt.cmake)
include(cmake/deps/json.cmake)
include(cmake/deps/libxml2.cmake)
include(cmake/deps/spdlog.cmake)
include(cmake/deps/zeromq.cmake)

