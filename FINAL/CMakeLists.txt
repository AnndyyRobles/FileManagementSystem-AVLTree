cmake_minimum_required(VERSION 3.28)
project(FINAL)

set(CMAKE_CXX_STANDARD 14)

include_directories(FINAL)

add_executable(FINAL
        FINAL/archivo.cpp
        FINAL/archivo.h
        FINAL/carpeta.cpp
        FINAL/carpeta.h
        FINAL/ColaE.cpp
        FINAL/ColaE.h
        FINAL/ListaE.cpp
        FINAL/ListaE.h
        FINAL/main.cpp
        FINAL/PilaE.cpp
        FINAL/PilaE.h
        FINAL/Tree.cpp
        FINAL/Tree.h)
