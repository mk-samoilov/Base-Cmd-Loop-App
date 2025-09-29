cmake_minimum_required(VERSION 3.16)
project(BaseCppCmdLoopApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(BaseApp
    src/main.cpp
    src/core.cpp
    src/core.hpp
    src/cr/commands_registry.cpp
    src/cr/commands_registry.hpp
    src/capi/console_api.cpp
    src/capi/console_api.hpp
)

target_include_directories(BaseApp PRIVATE scr scr/capi)

if(WIN32)
    target_link_libraries(BaseApp psapi)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(BaseApp PRIVATE DEBUG=1)
endif()

install(TARGETS BaseApp RUNTIME DESTINATION bin)