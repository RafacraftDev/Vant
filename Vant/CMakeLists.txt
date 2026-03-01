cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Vant)

# Definimos el nombre una sola vez
SET(programName Vant)

# Carpeta donde guardaste los FindSDL2_xxx.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMakeFiles/")

# Listado de archivos fuente
# Nota: He usado ${programName} como nombre del ejecutable
add_executable(${programName} 
    Main.cpp 
    main.h 
    anyops.h 
    builtin.h 
    strops.cpp 
    strops.h 
    eval.cpp 
    eval.h 
    graphics.h 
    Vant.h 
    color.hpp
)

# Buscar dependencias
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Configuración de Boost
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED COMPONENTS system) 

# Directorios de inclusión
include_directories(
    ${Boost_INCLUDE_DIRS} 
    ${SDL2_INCLUDE_DIRS} 
    ${SDL2_IMAGE_INCLUDE_DIRS} 
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Enlace de librerías
# 'm' es para la librería matemática en Linux, el resto son tus dependencias
target_link_libraries(${programName} 
    m 
    ${Boost_LIBRARIES} 
    ${SDL2_LIBRARIES} 
    ${SDL2_IMAGE_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES}
)
