#include <vector>
#include <stdexcept>

template <typename T>
class ListaDinamica {
private:
    std::vector<T> elementos;

public:
    ListaDinamica() {}

    // No es necesario el método estaLlena() para un vector, pero lo incluimos por completitud
    bool estaLlena() const {
        return false; // Un vector nunca está realmente "lleno"
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
        for (size_t i = 0; i < elementos.size(); ++i) {
            if (elementos[i] == elemento) {
                return i;  // Elemento encontrado, retorna la posición
            }
        }
        return -1;  // Elemento no encontrado
    }
};
