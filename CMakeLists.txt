cmake_minimum_required(VERSION 3.16)

project(RichSocketTray LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    WebSockets
)

# Sources du projet
SET(SOURCES
    main.cpp
    CustomTray.cpp
    window.cpp
    Config.cpp
    CustomListener.cpp
    WSServer.cpp
    MediaObject.cpp
    RichPresenceManager.cpp
    discord_impl.cpp
)

SET(HEADERS
    CustomTray.h
    window.h
    Config.h
    CustomListener.h
    WSServer.h
    MediaObject.h
    RichPresenceManager.h
    Secrets.h
)

qt_standard_project_setup()

qt_add_executable(RichSocketTray ${SOURCES} ${HEADERS}
    discord_impl.cpp
)

set_target_properties(RichSocketTray PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)


# https://discord.com/developers/docs/discord-social-sdk/getting-started/using-c++


# Define some handy Social SDK variables
set(DISCORD_SDK_ROOT "${CMAKE_SOURCE_DIR}/lib/discord_social_sdk")
set(DISCORD_SDK_LIB_DIR "${DISCORD_SDK_ROOT}/lib/release")
set(DISCORD_SDK_BIN_DIR "${DISCORD_SDK_ROOT}/bin/release")
set(DISCORD_SDK_INCLUDE_DIR "${DISCORD_SDK_ROOT}/include")

# Include for Social SDK headers
target_include_directories(RichSocketTray PRIVATE ${DISCORD_SDK_INCLUDE_DIR})

# Platform-specific Social SDK library paths
if(WIN32)

    set(DISCORD_SHARED_LIB "${DISCORD_SDK_BIN_DIR}/discord_partner_sdk.dll")
    if(MSVC)
        set(DISCORD_LIB_PATH "${DISCORD_SDK_LIB_DIR}/discord_partner_sdk.lib")

        message(STATUS "TEST")
    elseif(MINGW)
        set(DISCORD_LIB_PATH "${DISCORD_SDK_LIB_DIR}/discord_partner_sdk.dll.a")

    endif()



elseif(APPLE)
    set(DISCORD_LIB_PATH "${DISCORD_SDK_LIB_DIR}/libdiscord_partner_sdk.dylib")
    set(DISCORD_SHARED_LIB "${DISCORD_SDK_LIB_DIR}/libdiscord_partner_sdk.dylib")
else() # Linux
    set(DISCORD_LIB_PATH "${DISCORD_SDK_LIB_DIR}/libdiscord_partner_sdk.so")
    set(DISCORD_SHARED_LIB "${DISCORD_SDK_LIB_DIR}/libdiscord_partner_sdk.so")
endif()





# Lier toutes les bibliothèques
target_link_libraries(RichSocketTray PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::WebSockets
    ${DISCORD_LIB_PATH} #discord api
)

# Set the runtime search path (RPATH) for Linux and macOS
if(UNIX)
    # Use RPATH when building
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    # Set the RPATH to use the lib directory relative to the executable
    set(CMAKE_INSTALL_RPATH "$ORIGIN")
    if(APPLE)
        set(CMAKE_INSTALL_RPATH "@executable_path")
    endif()
endif()


# Copy Social SDK shared library to output directory, so it's available at runtime.
add_custom_command(TARGET RichSocketTray POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${DISCORD_SHARED_LIB}"
    $<TARGET_FILE_DIR:RichSocketTray>
)


# Installation
include(GNUInstallDirs)
install(TARGETS RichSocketTray
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
