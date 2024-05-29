#include "carpeta.h"
#include <iostream>
#include <algorithm>

// CONSTRUCTOR
carpeta::carpeta(const string& nombre) : nombre(nombre), instancias(nullptr) {
    cout << "CREATION STATUS: Uso del constructor de clase en: " << nombre << endl;
    cout << "SUCESS STATUS: Se ha creado la carpeta " << nombre << endl;
}

// DESTRUCTOR
carpeta::~carpeta() {
    // Liberar la memoria de la lista enlazada
    Nodo* actual = instancias;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

// METODO: (LISTAR ELEMENTOS)
void carpeta::listarContenido() const {
    if (instancias == nullptr) {
        cout << "C O N T E N I D O : " << nombre << endl;
        cout << left << setw(20) << "Nombre" << setw(15) << "Tipo" << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;
        cout << "STATUS ERROR: Vaya! Parece que aun no se han creado instancias de ninguna clase :( " << endl;
        cout << "-----------------------------------------------------------------------------------\n" << endl;
        return;
    }

    // Ordenamiento por burbuja
    Nodo* i = instancias;
    while (i != nullptr) {
        Nodo* j = i->siguiente;
        while (j != nullptr) {
            string nombreI = (i->archivoPtr != nullptr) ? i->archivoPtr->getNombre() : i->carpetaPtr->getNombre();
            string nombreJ = (j->archivoPtr != nullptr) ? j->archivoPtr->getNombre() : j->carpetaPtr->getNombre();

            if (nombreI > nombreJ) {
                // Intercambiar los nodos
                Nodo* temp = i;
                i = j;
                j = temp;
            }
            j = j->siguiente;
        }
        i = i->siguiente;
    }

    // Iniciamos con el puntero al inicio de la lista
    Nodo* actual = instancias;
    cout << "C O N T E N I D O : " << nombre << endl;
    cout << left << setw(20) << "Nombre" << setw(15) << "Tipo" << endl;
    cout << "-------------------------------------------------------------------------" << endl;
    while (actual != nullptr) {
        // Ver que elementos hay de Archivos
        if (actual->archivoPtr != nullptr) {
            cout << setw(20) << actual->archivoPtr->getNombre() << setw(15) << "Archivo" << endl;
        }
        // Ver que elementos hay de Carpeta
        else if (actual->carpetaPtr != nullptr) {
            cout << setw(20) << actual->carpetaPtr->getNombre() << setw(15) << "Carpeta" << endl;
        }
        actual = actual->siguiente;
    }
    cout << "-------------------------------------------------------------------------\n" << endl;
}



// METODO: (CREAR ARCHIVO)
void carpeta::crearArchivo(const string& nombre, const string& datos) {
    // Verificar que aun quede espacio
    if (estaLlena()) {
        cout << "STATUS ERROR: La carpeta '" << nombre << "' ya contiene el maximo numero de instancias permitidas" << endl;
        //Salir del metodo y volver a la pantalla inicial
        return;
    }
    // Crear una instancia de archivo
    archivo* nuevoArchivo = new archivo(nombre);

    // Logica para escritura en el archivo
    ofstream archivoStream(nombre);
    if (archivoStream.is_open()) {
        archivoStream << datos; // Escribir los datos en el archivo
        archivoStream.close(); // Cerrar el archivo
        cout << "Se ha creado el archivo '" << nombre << endl;
    }
    else {
        cout << "STATUS ERROR: No se pudo crear el archivo: " << nombre << endl;
        delete nuevoArchivo; // Liberar la memoria si no se pudo crear el archivo
        return;
    }

    // Crea nodo para la lista enlazada
    Nodo* nuevoNodo = new Nodo(nuevoArchivo);

    // Si aun hay espacio agregalo
    if (instancias == nullptr) {
        instancias = nuevoNodo;
    }
    else {
        Nodo* actual = instancias;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        // Agregar el nuevo nodo al final de la lista
        actual->siguiente = nuevoNodo;
    }
}

// METODO: (ABRIR ARCHIVO)
void carpeta::abrirArchivo(const string& nombreArchivo) const {
    cout << "Abriendo archivo: " << nombreArchivo << endl;
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        cout << "\nContenido:" << endl;
        string linea;
        while (getline(archivo, linea)) {
            cout << linea << endl;
        }
        archivo.close();
    }
    else {
        cout << "El archivo '" << nombreArchivo << "' no existe" << endl;
    }
}

// METODO: (ELIMINAR ARCHIVO)
void carpeta::eliminarArchivoEnCarpeta(const string& nombreArchivo) {
    // Verificar si la carpeta estÃ¡ vacÃ­a
    if (instancias == nullptr) {
        cout << "ERROR 404 NOT FOUND STATUS: La carpeta esta vacia" << endl;
        return;
    }
    // Setup al nodo
    Nodo* actual = instancias;
    Nodo* anterior = nullptr;

    // Buscar el archivo
    while (actual != nullptr) {
        // Verificar si el actual apunta a un archivo y si el nombre coincide
        if (actual->archivoPtr != nullptr && actual->archivoPtr->getNombre() == nombreArchivo) {
            // Eliminar el archivo encontrada
            Nodo* temp = actual;
            if (anterior == nullptr) {
                instancias = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }
            delete temp;
            cout << "SUCCESS STATUS: El archivo: " << nombreArchivo << " se ha eliminado de la carpeta" << endl;
            return;
        }
        // Set up a los nodos tras la configuracion
        anterior = actual;
        actual = actual->siguiente;
    }
    cout << "STATUS ERROR: El archivo: " << nombreArchivo << " no se encontro en la carpeta" << endl;
}


// METODO: (CREAR SUBCARPETA)
void carpeta::crearSubcarpeta(const string& nombreSubcarpeta) {
    if (estaLlena()) {
        cout << "STATUS ERROR: La carpeta  no puede almacenar a: '" << nombre << "' ya que contiene el maximo numero de instancias permitidas" << endl;
        cout << "Elimine alguna de las instancias creadas e intentelo de nuevo" << endl;
        return;
    }
    // Instancia
    carpeta* nuevaSubcarpeta = new carpeta(nombreSubcarpeta);
    Nodo* nuevoNodo = new Nodo(nuevaSubcarpeta);
    if (instancias == nullptr) {
        instancias = nuevoNodo;
    }
    else {
        // Encontrar el Ãºltimo nodo en la lista
        Nodo* actual = instancias;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        // Agregar el nuevo nodo al final de la lista
        actual->siguiente = nuevoNodo;
    }
}

// METODO:  (abrirSubcarpeta)
void carpeta::abrirSubcarpeta(const string& nombreSubcarpeta) {
    // Buscar la subcarpeta en la lista enlazada
    Nodo* actual = instancias;
    while (actual != nullptr) {
        if (actual->tipo == CARPETA && actual->carpetaPtr->getNombre() == nombreSubcarpeta) {
            // Mostrar el contenido de la subcarpeta y permitir al usuario interactuar con ella
            cout << "Abriendo subcarpeta: " << nombreSubcarpeta << endl;
            actual->carpetaPtr->listarContenido();
            // Menu de cases para interactuar con la subcarpeta
            // Después de que el usuario termine de interactuar con la subcarpeta, puedes salir del método
            return;
        }
        actual = actual->siguiente;
    }
    // Si no se encuentra la subcarpeta, mostrar un mensaje de error
    cout << "ERROR: La subcarpeta '" << nombreSubcarpeta << "' no se encontró en la carpeta principal." << endl;
}

// METODO BUSQUEDA
archivo* carpeta::buscarArchivoEnCarpeta(const string& nombreArchivo) {
    // Verificar si la carpeta estÃ¡ vacÃ­a
    if (instancias == nullptr) {
        cout << "STATUS ERROR: La carpeta esta vacia" << endl;
        return nullptr;
    }

    // Iniciar bÃºsqueda desde el primer nodo
    Nodo* actual = instancias;
    // Recorrer la lista enlazada de instancias de la carpeta
    while (actual != nullptr) {
        // Verificar si el nodo actual contiene un archivo y si su nombre coincide
        if (actual->archivoPtr != nullptr && actual->archivoPtr->getNombre() == nombreArchivo) {
            cout << "STATUS SUCCESS: El archivo: '" << nombreArchivo << " ha sido encontrado en la carpeta: " << nombre << endl;
            return actual->archivoPtr;
        }
        // Mover al siguiente nodo
        actual = actual->siguiente;
    }
    // Cuando no se esncuentra
    cout << "STATUS ERROR: El archivo '" << nombreArchivo << "' no existe en la carpeta: '" << nombre << endl;
    return nullptr;
}

// METODO: (ELIMINAR SUBCARPETA)
void carpeta::eliminarSubcarpeta(const string& nombreSubcarpeta) {
    Nodo* actual = instancias;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->carpetaPtr != nullptr && actual->carpetaPtr->getNombre() == nombreSubcarpeta) {
            // Eliminar la subcarpeta si se encuentra
            if (anterior == nullptr) {
                instancias = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual->carpetaPtr;
            delete actual;
            cout << "Subcarpeta '" << nombreSubcarpeta << "' eliminada de la carpeta '" << nombre << endl;
            return; // Salir de la funciÃ³n despuÃ©s de eliminar la subcarpeta
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    cout << "Subcarpeta '" << nombreSubcarpeta << "' no encontrada en la carpeta '" << nombre << endl;
}


// METODO: Verifica si la lista de instancias esta llena
bool carpeta::estaLlena() const {
    return obtenerNumeroElementos() >= 7;
}

// METODO: Jala el numero de elementos/instancias creadas en la lista
int carpeta::obtenerNumeroElementos() const {
    int contador = 0;
    Nodo* actual = instancias;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

// METODO: Jala el nombre de la carpeta
string carpeta::getNombre() const {
    return nombre;
}
