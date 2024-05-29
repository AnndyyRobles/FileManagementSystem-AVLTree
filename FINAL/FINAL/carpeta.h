#ifndef CARPETA_H
#define CARPETA_H
#include <string>
#include <vector>
#include <iomanip>
#include "archivo.h" //clase archivo
class archivo; // Declaracion anticipada de la clase archivo
class carpeta; // Declaracion anticipada de la clase carpeta

using namespace std;

// Constantes para los tipos de instancias
enum TipoNodo {
    ARCHIVO,
    CARPETA
};

class Nodo {
public:
    Nodo(archivo* arch) : tipo(ARCHIVO), archivoPtr(arch), carpetaPtr(nullptr), siguiente(nullptr) {}
    Nodo(carpeta* carp) : tipo(CARPETA), archivoPtr(nullptr), carpetaPtr(carp), siguiente(nullptr) {}

    TipoNodo tipo;
    archivo* archivoPtr;
    carpeta* carpetaPtr;
    Nodo* siguiente;
};

//Clase Carpeta
class carpeta {
private:
    string nombre;
    Nodo* instancias; // Puntero a la lista enlazada de subcarpetas

public:
    carpeta(const string& nombre);
    ~carpeta();

    //METODOS PARA LA LISTA DE INSTANCIAS
    bool estaLlena() const;
    int obtenerNumeroElementos() const;

    //METODOS DE OPERATIVIDAD
    void crearArchivo(const string& nombre, const string& datos);
    void abrirArchivo(const string& nombreArchivo) const;
    void crearSubcarpeta(const string& nombreSubcarpeta);
    void abrirSubcarpeta(const string& nombreSubcarpeta);
    void listarContenido() const;
    archivo* buscarArchivoEnCarpeta(const string& nombreArchivo);
    void eliminarArchivoEnCarpeta(const string& nombreArchivo);
    void eliminarSubcarpeta(const string& nombreSubcarpeta);

    //METODOS DE OBTENCION
    string getNombre() const;
    Nodo* getInstancias() const {
        return instancias;
    }
};
#endif // CARPETA_H

