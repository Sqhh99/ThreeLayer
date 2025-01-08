cmake_minimum_required(VERSION 3.16)

project(ThreeLayer VERSION 0.1 LANGUAGES CXX)
set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/Icon.rc")

message(${app_icon_resource_windows})
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Charts)

set(PROJECT_SOURCES
        main.cpp
        threelayer.cpp
        threelayer.h
        threelayer.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ThreeLayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${app_icon_resource_windows}
        DataAccessLayer/mysqlconn.h DataAccessLayer/mysqlconn.cpp
        DataAccessLayer/sqcsv.h DataAccessLayer/sqcsv.cpp
        PresentationLayer/sqlinechart.h PresentationLayer/sqlinechart.cpp
        PresentationLayer/sqbarchart.h PresentationLayer/sqbarchart.cpp


        BusinessLogicLayer/csvcontroller.h BusinessLogicLayer/csvcontroller.cpp
        BusinessLogicLayer/pointconversion.h BusinessLogicLayer/pointconversion.cpp
        BusinessLogicLayer/linechartpointconversion.h BusinessLogicLayer/linechartpointconversion.cpp
        BusinessLogicLayer/pointmath.h BusinessLogicLayer/pointmath.cpp
        PresentationLayer/sqpiechart.h PresentationLayer/sqpiechart.cpp
        PresentationLayer/sqboxchart.h PresentationLayer/sqboxchart.cpp
        BusinessLogicLayer/linearregressionhelper.h BusinessLogicLayer/linearregressionhelper.cpp
        BusinessLogicLayer/mysqlconncontroller.h BusinessLogicLayer/mysqlconncontroller.cpp
    )
else()
    if(ANDROID)
        add_library(ThreeLayer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ThreeLayer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ThreeLayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ThreeLayer PRIVATE Qt6::Sql)
target_link_libraries(ThreeLayer PRIVATE Qt6::Charts)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ThreeLayer)
endif()

set_target_properties(ThreeLayer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ThreeLayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ThreeLayer)
endif()
