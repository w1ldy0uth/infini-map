cmake_minimum_required(VERSION 3.16)
project(InfiniMap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

set(SOURCES
    src/main.cpp
    src/core/MapView.cpp
    src/core/MapScene.cpp
    src/terrain/Noise.cpp
    src/terrain/BiomeColor.cpp
    src/utils/ImageUtils.cpp
)

set(HEADERS
    src/core/MapView.h
    src/core/MapScene.h
    src/terrain/Noise.h
    src/terrain/BiomeColor.h
    src/utils/ImageUtils.h
)

add_executable(InfiniMap ${SOURCES} ${HEADERS})

target_include_directories(InfiniMap PRIVATE 
    src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(InfiniMap PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

set_target_properties(InfiniMap PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

if(WIN32)
    get_target_property(QT_BIN_DIR Qt6::Core LOCATION)
    get_filename_component(QT_BIN_DIR "${QT_BIN_DIR}" DIRECTORY)
    set(WINDEPLOYQT_EXECUTABLE "${QT_BIN_DIR}/windeployqt.exe")

    if(EXISTS "${WINDEPLOYQT_EXECUTABLE}")
        add_custom_command(TARGET InfiniMap POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                    "$<TARGET_FILE:InfiniMap>"
            COMMENT "Deploying Qt libraries with windeployqt..."
            VERBATIM
        )
    else()
        message(WARNING "windeployqt not found at: ${WINDEPLOYQT_EXECUTABLE}")
    endif()
endif()
