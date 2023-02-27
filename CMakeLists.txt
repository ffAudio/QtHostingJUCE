cmake_minimum_required(VERSION 3.5)

project(QtHostingJUCE VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Not on QT 6 yet...
set(CMAKE_OSX_ARCHITECTURES x86_64)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES QtHostingJUCE_en_GB.ts)

set(PROJECT_SOURCES
        # QT
        ui/main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
        ${TS_FILES}
        # JUCE
        juce-stubs/stdafx.h
        juce-stubs/juce_config.h
        juce-stubs/juce_core_source.mm
        juce-stubs/juce_audio_basics_source.mm
        juce-stubs/juce_audio_devices_source.mm
        juce-stubs/juce_audio_formats_source.mm
        juce-stubs/juce_audio_processors_source.mm
        juce-stubs/juce_data_structures_source.mm
        juce-stubs/juce_events_source.mm
        juce-stubs/juce_graphics_source.mm
        juce-stubs/juce_gui_basics_source.mm
        juce-stubs/juce_gui_extras_source.mm
        # Player
        audio/audioplayer.h
        audio/audioplayer.cpp
        audio/pluginmanager.h
        audio/pluginmanager.cpp
        audio/audiopluginholder.h
        audio/audiopluginholder.cpp
)

set(APPLE_FRAMEWORKS
    "-framework AVFoundation"
    "-framework CoreAudioKit"
    "-framework CoreAudio"
    "-framework CoreVideo"
    "-framework CoreMidi"
    "-framework CoreMedia"
    "-framework QuartzCore"
    "-framework AudioToolbox"
    "-framework VideoToolbox"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework IOSurface"
    "-framework Accelerate"
    "-framework Metal"
    "-framework MetalKit"
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtHostingJUCE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtHostingJUCE APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(QtHostingJUCE SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtHostingJUCE
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_include_directories(QtHostingJUCE PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/JUCE/modules
    ${CMAKE_SOURCE_DIR}/JUCE/modules/juce_audio_processors/format_types/VST3_SDK/
)

target_link_libraries(QtHostingJUCE PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${APPLE_FRAMEWORKS})

set_target_properties(QtHostingJUCE PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtHostingJUCE
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtHostingJUCE)
endif()
