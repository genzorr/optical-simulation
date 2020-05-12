cmake_minimum_required(VERSION 3.17)
project(optical_simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

# SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(optical_simulation PUBLIC include)
file(GLOB SOURCES
        src/*.cpp
        src/sfml/*.cpp
        src/sfml/*.h
        interface/*.*
        )
add_executable(optical_simulation ${SOURCES})

target_link_libraries(optical_simulation Qt5::Core Qt5::Widgets Qt5::Quick)
target_link_libraries(optical_simulation sfml-graphics sfml-window sfml-system)
