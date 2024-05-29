#include "PilaE.h"

template <typename T>
PilaEstatica<T>::PilaEstatica() : tope(-1) {}

template <typename T>
bool PilaEstatica<T>::estaLlena() const {
    return tope >= MAX_SIZE - 1;
}

template <typename T>
bool PilaEstatica<T>::estaVacia() const {
    return tope == -1;
}

template <typename T>
void PilaEstatica<T>::push(const T& elemento) {
    if (estaLlena()) {
        // Manejo de error: pila llena
        return;
    }
    elementos[++tope] = elemento;
}

template <typename T>
T PilaEstatica<T>::pop() {
    if (estaVacia()) {
        // Manejo de error: pila vac�a
        return T(); // Retornamos un valor por defecto
    }
    return elementos[tope--];
}

template <typename T>
T& PilaEstatica<T>::peek() const {
    if (estaVacia()) {
        // Manejo de error: pila vac�a
        // Retornamos una referencia inv�lida, podr�a lanzar una excepci�n en lugar de hacer esto.
        return elementos[0];
    }
    return elementos[tope];
}
