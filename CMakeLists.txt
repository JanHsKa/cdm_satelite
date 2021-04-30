cmake_minimum_required(VERSION 3.14)

project(cdm_satellite
    VERSION 1.0
    DESCRIPTION "embedded Software Labor Task 3, c++ version"
    #LANGUAGES CXX
)

include(CTest)
#enable_testing()

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_STANDARD 17) 
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


file(GLOB_RECURSE source_list "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_library(lib STATIC ${source_list})
target_include_directories(lib PUBLIC include)


add_executable(cdm_satellite main.cpp)
target_link_libraries(cdm_satellite lib)


