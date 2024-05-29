#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "carpeta.h"
#include "archivo.h"
#include "Tree.h"
#include "AVLTree.h"
using namespace std;
//-------------------------------------
void menuAVL(AVLByTree<archivo>& avl);
void printError();
void titles();
void ends();
void menu();
void menuSubCarpeta();
void limpiarPantalla();
//-------------------------------------
int main() {
    BinarySearchTree directorios;
    AVLByTree<archivo> archivoAVL;
    carpeta carpetaPrincipal("Carpeta Principal");
    int opc;
    // INICIO DEL PROGRAMA
    titles();
    cout << endl << endl << "Presione Enter para continuar...";
    cin.get();
    limpiarPantalla();
    cout << "B I E N V E N I D O   A   D E S K M A G O  " << endl;
    cout << "=> U S U A R I O: ACTIVO " << endl;
    cout << "\n" << endl;

    do {
        menu(); // MENU PRINCIPAL
        cout << "SELECCIONE UNA OPC: ";
        cin >> opc;
        if (carpetaPrincipal.obtenerNumeroElementos() == 0 && (opc == 1 || opc == 3 || opc == 4 || opc == 5 || opc == 6 || opc == 8 || opc == 9)) {
            printError();
            this_thread::sleep_for(chrono::milliseconds(3000));
            limpiarPantalla();
            continue;
        }
        limpiarPantalla(); // Conviene llamar una sola vez esta func. en vez de en cada case
        switch (opc) {
        case 1: { // LISTA ELEMENTOS
            carpetaPrincipal.listarContenido();
            break;
        }
        case 2: {
            string nombreArch, datosAGuardar, linea;

            cout << "=== CREAR ARCHIVO NUEVO ===" << endl;
            cout << "Ingrese el nombre del archivo: ";
            cin >> nombreArch;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer del teclado

            cout << "Ingrese los datos del archivo:\n Nota: Después de ingresar los datos, presione Enter en una linea vacia para finalizar (2 veces enter).\n: ";
            while (getline(cin, linea) && !linea.empty()) {
                datosAGuardar += linea + "\n"; // Agregar la línea al contenido del archivo
            }
            carpetaPrincipal.crearArchivo(nombreArch, datosAGuardar);
            cout << "\n" << endl;
            carpetaPrincipal.listarContenido();
            break;
        }
        case 3: { // ABRE ARCHIVO
            string nombreArch;

            cout << "=== ABRIR ARCHIVO EXISTENTE ===" << endl;
            carpetaPrincipal.listarContenido();

            cout << "Ingrese el nombre del archivo a abrir: ";
            cin >> nombreArch;
            archivo* archivoAbrir = carpetaPrincipal.buscarArchivoEnCarpeta(nombreArch);
            // Verificar si se encontrÃ³ el archivo y abrirlo si es asÃ­
            if (archivoAbrir != nullptr) {
                carpetaPrincipal.abrirArchivo(nombreArch);
            }
            cout << "\n" << endl;
            break;
        }
        case 4: { // EDITAR UN ARCHIVO
            string nombreArch, datosAGuardar, linea;

            cout << "=== EDICION DE UN ARCHIVO ===" << endl;
            carpetaPrincipal.listarContenido();

            cout << "Ingrese el nombre del archivo a editar: ";
            cin >> nombreArch;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer del teclado

            cout << "Ingrese los nuevos datos del archivo:\n Nota: Presione Enter en una linea vacia para finalizar.\n Nota: El contenido anterior se eliminara.\n" << endl;
            while (getline(cin, linea) && !linea.empty()) {
                datosAGuardar += linea + "\n"; // Agregar la línea al contenido del archivo
            }
            archivo* archivoEditar = carpetaPrincipal.buscarArchivoEnCarpeta(nombreArch);
            if (archivoEditar != nullptr) {
                if (archivoEditar->getNombre() == nombreArch) {
                    archivoEditar->editarArchivo(nombreArch, datosAGuardar);
                    cout << "\n" << endl;
                    carpetaPrincipal.listarContenido();
                    cout << "\n" << endl; break;
                }
                // Omitimos el else, ya que, por defecto, si no entra el if, va a ejecutar la acción alterna, solo hay que agregar un break.
                cout << "ERROR STATUS: El archivo '" << nombreArch << "' no fue encontrado en la carpeta principal" << endl; break;
            }
            cout << "ERROR STATUS: El archivo '" << nombreArch << "' no fue encontrado en la carpeta principal" << endl;
            break;
        }
        case 5: { //CERRAR UN ARCHIVO
            string nombreArch;

            cout << "=== CERRAR UN ARCHIVO ===" << endl;;
            carpetaPrincipal.listarContenido();

            cout << "Ingrese el nombre del archivo a cerrar: ";
            cin >> nombreArch;

            // Buscar el archivo en la carpeta
            archivo* archivoCerrar = carpetaPrincipal.buscarArchivoEnCarpeta(nombreArch);

            if (archivoCerrar != nullptr) {
                archivoCerrar->cerrarArchivo(nombreArch); break;
            }
            cout << "El archivo '" << nombreArch << "' no se encontro en la carpeta principal." << endl;
            break;
        }
        case 6: { //ELIMINAR ARCHIVO
            string nombreArch;

            cout << "=== ELIMINAR UN ARCHIVO ===" << endl;;
            carpetaPrincipal.listarContenido();

            cout << "Ingrese el nombre del archivo a eliminar: ";
            cin >> nombreArch;
            carpetaPrincipal.eliminarArchivoEnCarpeta(nombreArch);
            break;
        }
        case 7: { //CREAR SUBCARPETA
            string nombreArch;

            cout << "=== CREACION DE UNA SUBCARPETA ===" << endl;;

            cout << "Ingrese el nombre de la subcarpeta a crear: ";
            cin >> nombreArch;

            carpetaPrincipal.crearSubcarpeta(nombreArch);
            cout << "\n" << endl;
            carpetaPrincipal.listarContenido();
            break;
        }
        case 8: { // ABRIR SUBCARPETA
            string nombreArch;
            cout << "Ingrese el nombre de la subcarpeta a abrir: ";
            cin >> nombreArch;
            TreeNode* nodo = directorios.search(directorios.root, nombreArch);
            if (nodo) {
                cout << "Subcarpeta '" << nodo->nombreArchivo << "' abierta.\n"; break;
            }
            cout << "Subcarpeta no encontrada.\n";
            break;
        }
        case 9: { // ELIMINAR SUBCARPETA
            string nombreArch;

            cout << "Ingrese el nombre de la subcarpeta a eliminar: ";
            cin >> nombreArch;
            directorios.root = directorios.deleteNode(directorios.root, nombreArch);
            cout << "Subcarpeta eliminada.\n";
            break;
        }
        case 10: { // GESTIÓN AVL
                menuAVL(archivoAVL);
                break;
        }
        case 11: {
            ends();
            break;
        }
        default: {
            cout << "STATUS ERROR: Opcion digitada valida (Ingrese solo valores numericos pertenecientes al menu)" << endl;
        }
        }
        cin.get();
        this_thread::sleep_for(chrono::milliseconds(5000)); // Esperar 200 milisegundos
        limpiarPantalla();
    } while (opc != 11);
    return 0;
}

//----------------------------------------------------------------------------------



void menuAVL(AVLByTree<archivo>& avl) {
    while (true) {
//        cout << "\n============= Menu del Arbol AVL =============" << endl;
//        cout << "= 1. Agregar archivo al árbol                  =" << endl;
//        cout << "= 2. Buscar un archivo en el árbol             =" << endl;
//        cout << "= 3. Eliminar un archivo del árbol             =" << endl;
//        cout << "= 4. Mostrar todos los archivos en orden       =" << endl;
//        cout << "= 5. Volver al menú principal                  =" << endl;
//        cout << "= Seleccione una opcion:                       =";
//        cout << "\n==============================================" << endl;
        cout << "\n" << char(201) << string(50, char(205)) << char(187) << "\n";
        cout << char(186) << "                                                  " << char(186) << "\n";
        cout << char(186) << "                Menu del Arbol AVL                " << char(186) << "\n";
        cout << char(186) << "                                                  " << char(186) << "\n";
        cout << char(204) << string(50, char(205)) << char(185) << "\n";
        cout << char(186) << "  1. Agregar archivo al arbol                     " << char(186) << "\n";
        cout << char(186) << "  2. Buscar un archivo en el arbol                " << char(186) << "\n";
        cout << char(186) << "  3. Eliminar un archivo del arbol                " << char(186) << "\n";
        cout << char(186) << "  4. Mostrar todos los archivos en orden          " << char(186) << "\n";
        cout << char(186) << "  5. Volver al menu principal                     " << char(186) << "\n";
        cout << char(186) << "                                                  " << char(186) << "\n";
        cout << char(186) << "  Seleccione una opcion:                          " << char(186) << "\n";
        cout << char(200) << string(50, char(205)) << char(188) << "\n";
        int opcion;
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (opcion == 5) break;

        switch (opcion) {
            case 1: {
                cout << "Ingrese el nombre del archivo: ";
                string nombre;
                getline(cin, nombre);
                archivo* nuevoArchivo = new archivo(nombre);
                avl.insert(nombre, nuevoArchivo);
                cout << "Archivo anadido al arbol AVL.\n";
                break;
            }
            case 2: {
                cout << "Ingrese el nombre del archivo a buscar: ";
                string nombre;
                getline(cin, nombre);
                archivo* encontrado = avl.search(nombre);
                if (encontrado != nullptr) {
                    cout << "Archivo encontrado: " << encontrado->getNombre() << endl;
                } else {
                    cout << "Archivo no encontrado.\n";
                }
                break;
            }
            case 3: {
                cout << "Ingrese el nombre del archivo a eliminar: ";
                string nombre;
                getline(cin, nombre);
                avl.remove(nombre);
                cout << "Archivo eliminado del arbol AVL.\n";
                break;
            }
            case 4: {
                cout << "Archivos en el arbol AVL (en orden): \n";
                avl.displayInOrder();
                break;
            }
            default:
                cout << "Opcion no valida.\n";
        }
    }
}


void printError() {
    cout << "\n\nError. No se han creado elementos todavia.\n";
}

// Función para limpiar la pantalla en Linux, MacOS o Windows
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void titles() {
    string titulo1 = " _______   _______     _______. __  ___ .___  ___.      ___       _______   ______   ";
    string titulo2 = "|       \\ |   ____|   /       ||  |/  / |   \\/   |     /   \\     /  _____| /  __  \\  ";
    string titulo3 = "|  .--.  ||  |__     |   (----`|  '  /  |  \\  /  |    /  ^  \\   |  |  __  |  |  |  | ";
    string titulo4 = "|  |  |  ||   __|     \\   \\    |    <   |  |\\/|  |   /  /_\\  \\  |  | |_ | |  |  |  | ";
    string titulo5 = "|  '--'  ||  |____.----)   |   |  .  \\  |  |  |  |  /  _____  \\ |  |__| | |  `--'  | ";
    string titulo6 = "|_______/ |_______|_______/    |__|\\__\\ |__|  |__| /__/     \\__\\ \\______|  \\______/  ";
    // Mostrar la animación de título
    cout << endl;
    cout << titulo1 << endl;
    this_thread::sleep_for(chrono::milliseconds(200)); // Esperar 200 milisegundos
    cout << titulo2 << endl;
    this_thread::sleep_for(chrono::milliseconds(200)); // Esperar 200 milisegundos
    cout << titulo3 << endl;
    this_thread::sleep_for(chrono::milliseconds(200)); // Esperar 200 milisegundos
    cout << titulo4 << endl;
    this_thread::sleep_for(chrono::milliseconds(200)); // Esperar 200 milisegundos
    cout << titulo5 << endl;
    this_thread::sleep_for(chrono::milliseconds(200)); // Esperar 200 milisegundos
    cout << titulo6 << endl;

    string titulo = "DeskMago: Gestor de instancias y ficheros";
    string animacion = "Cargando...";

    // Mostrar el titles del proyecto
    cout << endl;
    cout << string(20, '-') << " " << titulo << " " << string(20, '-') << endl;
    cout << endl;

    // Mostrar la animaicion de carga
    for (char c : animacion) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(250));
    }
}

// Animation de salida
void ends() {
    cout << "=> U S U A R I O: INACTIVO " << endl;
    string salida = "Saliendo del programa...";
    string despedida = "\nHasta Pronto... ";
    string feli = "\n:)";
    for (char c : salida) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(175));
    }
    for (char c : despedida) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(175));
    }
    for (char c : feli) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void menu() {
    cout << "=========================== O P E R A C I O N E S =========================" << endl;
    cout << "1.  (LISTAR ELEMENTOS)      Listar las instancias de esta carpeta" << endl;
    cout << "2.  (CREAR ARCHIVO)         Crear archivo en carpeta principal" << endl;
    cout << "3.  (ABRIR ARCHIVO)         Acceder a un archivo instanciado en carpeta principal" << endl;
    cout << "4.  (EDITAR ARCHIVO)        Escribir en archivos instanciados en carpeta principal" << endl;
    cout << "5.  (CERRAR ARCHIVO)        Cerrar archivo instanciados en carpeta principal" << endl;
    cout << "6.  (ELIMINAR ARCHIVO)      Eliminar archivo en carpeta principal" << endl;
    cout << "7.  (CREAR SUBCARPETA)      Crear una subcarpeta" << endl;
    cout << "8.  (ABRIR SUBCARPETA)      Acceder a una subcarpeta creada" << endl;
    cout << "9.  (ELIMINAR SUBCARPETA)   Eliminar subcarpeta en carpeta principal" << endl;
    cout << "10. (GESTION (AVL TREE))    Gestionar archivos con AVL Tree" << endl; // Nueva opción para el menú AVL
    cout << "11. (SALIR)                 Salir del programa " << endl;
    cout << "============================================================================" << endl;
}

void menuSubCarpeta() {
    cout << "########################## O P E R A C I O N E S #############################" << endl;
    cout << "1.  ! (LISTAR ELEMENTOS)      Listar las instancias de esta subcarpeta" << endl;
    cout << "2.  ! (CREAR ARCHIVO)         Crear un archivo en esta SubCarpeta" << endl;
    cout << "3.  ! (ABRIR ARCHIVO)         Acceder a un archivo instanciado en carpeta principal" << endl;
    cout << "4.  ! (EDITAR ARCHIVO)        Escribir en archivos instanciados en carpeta principal" << endl;
    cout << "5.  ! (CERRAR ARCHIVO)        Cerrar archivo instanciados en carpeta principal" << endl;
    cout << "6.  ! (ELIMINAR ARCHIVO)      Eliminar archivo en carpeta principal" << endl;
    cout << "7.  ! (CREAR SUBCARPETA)      Crear una subcarpeta en esta subcarpeta" << endl;
    cout << "8.  ! (ABRIR SUBCARPETA)      Acceder a una subcarpeta creada" << endl;
    cout << "9.  ! (ELIMINAR SUBCARPETA)   Eliminar subcarpeta en esta subcarpeta" << endl;
    cout << "10. (VOLVER)                Volver al carpeta/opcion anterior" << endl;
    cout << "11. (SALIR)                 Salir del programa " << endl;
    cout << "################################################################################" << endl;
    cout << "WARNING: Las opciones (1-9) No estan disponibles para esta entrega :" << endl;
    cout << "El uso de subcarpetas e instancias recursivas forma parte de estructuras de tipo dinamico y arboles de busqueda;" << endl;
    cout << "Estas funciones seran implementadas en las posteriores entregas (entrega 2- entrega 3)" << endl;
};