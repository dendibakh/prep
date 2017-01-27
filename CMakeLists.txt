project(prep CXX C)
cmake_minimum_required(VERSION 2.8)

include(GNUInstallDirs)

# general settings
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-pedantic -Wall -Wextra -Wformat=2 -Werror -Wno-missing-braces -std=c++14 ${CMAKE_CXX_FLAGS}")

# build 
file(GLOB_RECURSE SRC_LIST "./*.cpp")
include_directories(./ /usr/local/include /usr/local/lib)
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} gtest_main gtest pthread dl)
link_directories(/usr/local/lib)
