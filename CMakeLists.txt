cmake_minimum_required(VERSION 3.16)
project(InfiniMap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

add_executable(InfiniMap
    src/main.cpp
    src/MapView.h src/MapView.cpp
    src/MapScene.h src/MapScene.cpp
    src/Noise.h src/Noise.cpp
)

target_include_directories(InfiniMap PRIVATE src)

target_link_libraries(InfiniMap Qt6::Widgets Qt6::Gui Qt6::Core)

set_target_properties(InfiniMap PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
