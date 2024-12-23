cmake_minimum_required(VERSION 3.16)

project(kursach LANGUAGES CXX)

# Включить автоматическую обработку UIC, MOC и RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указать путь к OpenSSL (для MinGW)
set(OPENSSL_ROOT_DIR "C:/OpenSSL")
set(OPENSSL_INCLUDE_DIR "C:/OpenSSL/include")
# Удалите или закомментируйте следующую строку
# set(OPENSSL_LIBRARIES "C:/OpenSSL/lib")

# Добавить путь к OpenSSL в CMAKE_PREFIX_PATH
list(APPEND CMAKE_PREFIX_PATH "C:/OpenSSL")

# Найти OpenSSL
find_package(OpenSSL REQUIRED)

# Найти Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# Проверка, что OpenSSL найден
if(OpenSSL_FOUND)
    message(STATUS "OpenSSL найден: ${OPENSSL_VERSION}")
    message(STATUS "OpenSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OpenSSL_SSL_LIBRARY: ${OPENSSL_SSL_LIBRARY}")
    message(STATUS "OpenSSL_CRYPTO_LIBRARY: ${OPENSSL_CRYPTO_LIBRARY}")
else()
    message(FATAL_ERROR "OpenSSL не найден!")
endif()

# Добавить исполняемый файл и исходные файлы
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
        src/circleshape.cpp
        src/lineshape.cpp
        src/polygonshape.cpp
        src/rectangleshape.cpp
        src/triangleshape.cpp
        include/TrialChecker.h
        src/TrialChecker.cpp
)

# Установить директории с заголовочными файлами
target_include_directories(kursach PRIVATE
        ${OPENSSL_INCLUDE_DIR}
        include
)

# Линковка с Qt и OpenSSL
# Поскольку цели OpenSSL::SSL и OpenSSL::Crypto не определены, используем переменные
target_link_libraries(kursach PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
        ${OPENSSL_LIBRARIES}
)

# Установочные директории
include(GNUInstallDirs)
install(TARGETS kursach
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
