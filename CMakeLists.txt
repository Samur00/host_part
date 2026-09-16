cmake_minimum_required(VERSION 3.16)

project(host VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Добавляем Network к компонентам Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Quick Network)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(apphost
    main.cpp
)

# 2. Разделяем QML_FILES и SOURCES
qt_add_qml_module(apphost
    URI host
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        client/myhost.h
        client/myhost.cpp
)
target_include_directories(apphost PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/client
)
set_target_properties(apphost PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 3. Линкуем сетевой модуль к исполняемому файлу
target_link_libraries(apphost
    PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS apphost
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
