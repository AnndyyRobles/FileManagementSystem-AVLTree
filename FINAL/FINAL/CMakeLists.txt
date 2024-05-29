cmake_minimum_required(VERSION 3.28)
project(FINAL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(FINAL
        archivo.cpp
        archivo.h
        carpeta.cpp
        carpeta.h
        ColaE.cpp
        ColaE.h
        ListaE.cpp
        ListaE.h
        main.cpp
        PilaE.cpp
        PilaE.h
        Tree.cpp
        Tree.h
        AVLTree.h
)
