cmake_minimum_required(VERSION 3.16)
project(BaseCppCmdLoopApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(scr)

file(GLOB_RECURSE SOURCES 
    "scr/*.cpp"
    "scr/*.c"
)

add_executable(BaseApp ${SOURCES})

if(WIN32)
    target_link_libraries(BaseApp psapi)
endif()

set_target_properties(BaseApp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(BaseApp PRIVATE DEBUG=1)
endif()

install(TARGETS BaseApp DESTINATION bin)