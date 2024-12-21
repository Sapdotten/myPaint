cmake_minimum_required(VERSION 3.16)

project(kursach LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_executable(kursach
        main.cpp
        include/brush.h
        include/canvas.h
        include/layer.h
        src/layer.cpp
        src/brush.cpp
        src/canvas.cpp
        include/palette.h
        src/palette.cpp
        include/shape.h
        include/lineshape.h
        include/rectangleshape.h
        include/circleshape.h
        include/triangleshape.h
        include/polygonshape.h
)

target_link_libraries(kursach Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

include(GNUInstallDirs)
install(TARGETS kursach
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
