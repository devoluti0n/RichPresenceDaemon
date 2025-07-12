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


SET(SOURCES

    main.cpp
    CustomTray.cpp
    window.cpp


)

SET(HEADERS
    CustomTray.h
    window.h

)


qt_standard_project_setup()

qt_add_executable(RichSocketTray ${SOURCES} ${HEADERS}
    Config.h Config.cpp
    CustomListener.h CustomListener.cpp
    WSServer.h WSServer.cpp
    MediaObject.h MediaObject.cpp

)

set_target_properties(RichSocketTray PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(RichSocketTray PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::WebSockets
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






