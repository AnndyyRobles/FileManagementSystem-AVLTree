#ifndef LISTA_DINAMICA_H
#define LISTA_DINAMICA_H

#include <vector>

template <typename T>
class ListaDinamica {
private:
    std::vector<T> elementos;

public:
    ListaDinamica() {}

    // Verifica si la lista está llena
    // En una lista dinámica, usualmente no necesitamos esta función
    // porque el vector puede expandirse según sea necesario.
    bool estaLlena() const {
        return false; // Un vector nunca está "lleno" en el sentido estático
    }

    // Verifica si la lista está vacía
    bool estaVacia() const {
        return elementos.empty();
    }

    // Inserta un elemento en una posición específica
    void insertar(const T& elemento, int posicion) {
        if (posicion < 0 || posicion > elementos.size()) {
            throw std::out_of_range("Posición fuera de rango");
        }
        elementos.insert(elementos.begin() + posicion, elemento);
    }

    // Elimina el elemento en una posición específica
    void eliminar(int posicion) {
        if (posicion < 0 || posicion >= elementos.size()) {
            throw std::out_of_range("Posición fuera de rango");
        }
        elementos.erase(elementos.begin() + posicion);
    }

    // Busca un elemento y devuelve su posición
    int buscar(const T& elemento) const {
        for (int i = 0; i < elementos.size(); ++i) {
            if (elementos[i] == elemento) {
                return i;
            }
        }
        return -1;  // Si no encuentra el elemento, retorna -1
    }
};

#endif // LISTA_DINAMICA_H
