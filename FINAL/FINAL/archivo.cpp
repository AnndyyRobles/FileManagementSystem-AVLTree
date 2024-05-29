#include "archivo.h"
#include <iostream>

//Constructor
archivo::archivo(const std::string& nombre)
        : nombre(nombre) {
    std::cout << "Se ha creado el archivo " << nombre << std::endl;
}

// METODO: (EDITAR ARCHIVO)
void archivo::editarArchivo(const std::string& nombreArchivo, const std::string& datos) {
    std::ofstream archivo(nombreArchivo, std::ios::out);
    if (archivo.is_open()) {
        archivo << datos << std::endl;
        std::cout << "Datos escritos en el archivo '" << nombreArchivo << "'." << std::endl;
        archivo.close();
    }
    else {
        std::cout << "Error al abrir el archivo '" << nombreArchivo << "' para escritura." << std::endl;
    }
}

// METODO: (CERRAR ARCHIVO)
void archivo::cerrarArchivo(std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::app);

    // Se verifica si el archivo se abrió correctamente
    if (archivo.is_open()) {
        archivo.close();
        std::cout << "El archivo '" << nombreArchivo << "' ha sido cerrado." << std::endl;
    }
    else {
        std::cout << "Error al cerrar el archivo '" << nombreArchivo << "' ya esta cerrado." << std::endl;

        // Se muestra un mensaje indicando que el archivo ha sido cerrado
        std::cout << "El archivo '" << nombreArchivo << "' ha sido cerrado." << std::endl;
    }
}

//JalarNombre del archivo
std::string archivo::getNombre() const {
    return nombre;
}
