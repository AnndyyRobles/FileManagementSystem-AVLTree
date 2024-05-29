#ifndef ARCHIVO_H
#define ARCHIVO_H
#include <string>
#include <fstream>

class archivo {
private:
    std::string nombre;
    std::string fecha;

public:
    //Constru
    archivo(const std::string& nombre);

    //METODOS DE OPERATIVIDAD
    void editarArchivo(const std::string& nombreArchivo, const std::string& datos);
    void cerrarArchivo(std::string& nombreArchivo);

    //METODOS DE OBTENCION
    //void setFechaHora(const std::string& fechaHora);
    std::string getNombre() const;
};
#endif // ARCHIVO_H
