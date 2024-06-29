set(SPDLOG_FMT_EXTERNAL ON)
set(SPDLOG_BUILD_SHARED TRUE)
set(SPDLOG_BUILD_PIC TRUE)
FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v${SPDLOG_TAG_VERSION}.tar.gz
)
FetchContent_MakeAvailable(spdlog)
