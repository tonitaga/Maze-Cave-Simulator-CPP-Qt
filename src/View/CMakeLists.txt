cmake_minimum_required(VERSION 3.5)

project(MazeAndCave VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS  "-std=c++17 -O2 -Wall")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(../Controller)
include_directories(../Model/include)
include_directories(../Model/internal)

set(PROJECT_SOURCES
        ../main.cc
        view.cc
        view.h
        scene.cc
        scene.h
        view.ui
        ../Controller/controller.h
        ../Model/include/data_wrapper.h
        ../Model/include/file_manager.h
        ../Model/include/file_types.h
        ../Model/include/generator_device.h
        ../Model/include/model.h
        ../Model/include/path_finder_device.h
        ../Model/internal/file_reader.h
        ../Model/internal/file_saver.h
        ../Model/internal/generator.h
        ../Model/internal/macros.h
        ../Model/internal/path_finder.h
)

set(FONT ${CMAKE_CURRENT_SOURCE_DIR}/PixelBoldFont.ttf)
set_source_files_properties(${FONT} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

set(MACOSX_BUNDLE_ICON_FILE mazecave.icns)
set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/mazecave.icns)
set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

qt_add_resources(PROJECT_SOURCES fonts.qrc)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MazeAndCave
        MANUAL_FINALIZATION
        fonts.qrc
        ${FONT}
        ${APP_ICON}
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET View APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MazeAndCave SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MazeAndCave
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MazeAndCave PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(MazeAndCave PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    RESOURCE "$RESOURCE_FILES"
)

install(TARGETS MazeAndCave
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MazeAndCave)
endif()
