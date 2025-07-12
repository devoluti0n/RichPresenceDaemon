cmake_minimum_required(VERSION 3.16)

project(RichSocketTray LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 REQUIRED COMPONENTS
    Gui
    Widgets
    WebSockets

)
find_package(Qt6 REQUIRED COMPONENTS Core)


# Définir le chemin du SDK
set(DISCORD_SDK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/discord_game_sdk")


file(GLOB_RECURSE DISC_HEADERS "${DISCORD_SDK_PATH}/cpp/*.h")

 # "${DISCORD_SDK_PATH}/cpp/*.cpp"



SET(SOURCES

    main.cpp
    CustomTray.cpp
    window.cpp
)

SET(HEADERS
    CustomTray.h
    window.h
    ${DISC_HEADERS}
)


qt_standard_project_setup()

qt_add_executable(RichSocketTray ${SOURCES} ${HEADERS}
    Config.h Config.cpp
    CustomListener.h CustomListener.cpp
    WSServer.h WSServer.cpp
    MediaObject.h MediaObject.cpp
    RichPresenceManager.h RichPresenceManager.cpp

)

set_target_properties(RichSocketTray PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)





# Resources:
# set(RichSocketTray_resource_files
#     "images/bad.png"
#     "images/heart.png"
#     "images/trash.png"
# )

qt_add_resources(RichSocketTray "RichSocketTray"
    PREFIX
        "/"
    FILES
        ${RichSocketTray_resource_files}
)



message(STATUS DISCORD_SDK_PATH)

add_library(discord_sdk SHARED IMPORTED)

# Configuration conditionnelle par plateforme
if(WIN32)
    # Windows : utiliser .dll.lib pour le linkage et .dll pour le runtime
    set_target_properties(discord_sdk PROPERTIES
        IMPORTED_LOCATION "${DISCORD_SDK_PATH}/lib/x86_64/discord_game_sdk.dll"
        IMPORTED_IMPLIB "${DISCORD_SDK_PATH}/lib/x86_64/discord_game_sdk.dll.lib"
    )
elseif(APPLE)
    # macOS : utiliser .dylib (ignorer le .bundle)
    set_target_properties(discord_sdk PROPERTIES
        IMPORTED_LOCATION "${DISCORD_SDK_PATH}/lib/x86_64/discord_game_sdk.dylib"
    )
elseif(UNIX)
    # Linux : utiliser .so
    set_target_properties(discord_sdk PROPERTIES
        IMPORTED_LOCATION "${DISCORD_SDK_PATH}/lib/x86_64/discord_game_sdk.so"
    )
endif()

# Link against discord library, that we defined earlier as a target
target_link_libraries(RichSocketTray PRIVATE discord_sdk)

# Add headers to project
target_include_directories(discord_sdk INTERFACE
    "${DISCORD_SDK_PATH}/cpp"
)


# Link against cute libraries
target_link_libraries(RichSocketTray PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::WebSockets
)
target_link_libraries(RichSocketTray PRIVATE Qt6::Core)

# qt_generate_deploy_app_script(
#     TARGET RichSocketTray
#     OUTPUT_SCRIPT deploy_script
#     NO_UNSUPPORTED_PLATFORM_ERROR
# )
# install(SCRIPT ${deploy_script})

include(GNUInstallDirs)
install(TARGETS RichSocketTray
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}

)



# if(COMMAND qt_create_translation)
#     qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# else()
#     qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
# endif()






