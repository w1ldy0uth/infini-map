cmake_minimum_required(VERSION 3.16)
project(InfiniMap VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui Test)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Enable testing
enable_testing()

set(SOURCES
    src/main.cpp
    src/core/MapView.cpp
    src/core/MapScene.cpp
    src/terrain/Noise.cpp
    src/terrain/BiomeColor.cpp
    src/utils/ImageUtils.cpp
    src/utils/Random.cpp
)

set(HEADERS
    src/core/MapView.h
    src/core/MapScene.h
    src/terrain/Noise.h
    src/terrain/BiomeColor.h
    src/utils/ImageUtils.h
    src/utils/Random.h
)

add_executable(InfiniMap ${SOURCES} ${HEADERS})

target_include_directories(InfiniMap PRIVATE 
    src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(InfiniMap PRIVATE Qt6::Widgets Qt6::Gui Qt6::Core)

include(GNUInstallDirs)
install(TARGETS InfiniMap
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Test executable
set(TEST_SOURCES
    tests/TestNoise.cpp
    tests/TestBiomeColor.cpp
    tests/TestImageUtils.cpp
    tests/TestConfig.cpp
    tests/main.cpp
    src/terrain/Noise.cpp
    src/terrain/BiomeColor.cpp
    src/utils/ImageUtils.cpp
)

# Create test executable
add_executable(InfiniMapTests ${TEST_SOURCES})

target_include_directories(InfiniMapTests PRIVATE
    src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(InfiniMapTests PRIVATE
    Qt6::Widgets
    Qt6::Gui
    Qt6::Core
    Qt6::Test
)

# Add test to CTest
add_test(NAME InfiniMapTests COMMAND InfiniMapTests)

if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt
        HINTS
            "$ENV{QTDIR}/bin"
            "${Qt6_DIR}/../../../bin"
            "$ENV{QT_DIR}/bin"
            "$ENV{QT6_DIR}/bin"
        PATH_SUFFIXES bin
        DOC "Path to windeployqt executable"
    )

    if(WINDEPLOYQT_EXECUTABLE)
        message(STATUS "Found windeployqt: ${WINDEPLOYQT_EXECUTABLE}")

        add_custom_command(TARGET InfiniMap POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                    --verbose 0
                    --no-translations
                    --no-system-d3d-compiler
                    --no-opengl-sw
                    --no-compiler-runtime
                    "$<TARGET_FILE:InfiniMap>"
            WORKING_DIRECTORY "$<TARGET_FILE_DIR:InfiniMap>"
            COMMENT "Deploying Qt libraries and plugins..."
            VERBATIM
        )

        add_custom_target(deploy
            COMMAND "${WINDEPLOYQT_EXECUTABLE}"
                    --verbose 1
                    --no-translations
                    "$<TARGET_FILE:InfiniMap>"
            WORKING_DIRECTORY "$<TARGET_FILE_DIR:InfiniMap>"
            COMMENT "Manual deployment with verbose output"
            VERBATIM
        )
    else()
        message(WARNING "windeployqt not found. Application may not run on systems without Qt installed.")
        message(STATUS "Searched in: $ENV{QTDIR}/bin, ${Qt6_DIR}/../../../bin, $ENV{QT_DIR}/bin, $ENV{QT6_DIR}/bin")
        message(STATUS "You can set QTDIR environment variable to Qt installation directory.")
        message(STATUS "Or install Qt Creator/ Qt maintenance tool to get windeployqt.")

        if(CMAKE_BUILD_TYPE STREQUAL "Release")
            message(STATUS "For manual deployment, run:")
            message(STATUS "  windeployqt.exe <path-to-InfiniMap.exe>")
        endif()
    endif()
endif()
