add_compile_definitions(JSON_NOEXCEPTION=1)
FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v${JSON_TAG_VERSION}/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)
