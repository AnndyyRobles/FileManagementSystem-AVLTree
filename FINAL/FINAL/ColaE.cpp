#include "ColaE.h"

template <typename T>
ColaEstatica<T>::ColaEstatica() : frente(-1), final(-1) {}

template <typename T>
bool ColaEstatica<T>::estaLlena() const {
    return (frente == 0 && final == MAX_SIZE - 1) || (frente == final + 1);
}

template <typename T>
bool ColaEstatica<T>::estaVacia() const {
    return frente == -1;
}

template <typename T>
void ColaEstatica<T>::enqueue(const T& elemento) {
    if (estaLlena()) {
        // Manejo de error: cola llena
        return;
    }
    if (frente == -1) {
        frente = 0;
        final = 0;
    }
    else if (final == MAX_SIZE - 1) {
        final = 0;
    }
    else {
        ++final;
    }
    elementos[final] = elemento;
}

template <typename T>
T ColaEstatica<T>::dequeue() {
    if (estaVacia()) {
        // Manejo de error: cola vac�a
        return T(); // Retornamos un valor por defecto
    }
    T elemento = elementos[frente];
    if (frente == final) {
        frente = -1;
        final = -1;
    }
    else if (frente == MAX_SIZE - 1) {
        frente = 0;
    }
    else {
        ++frente;
    }
    return elemento;
}

template <typename T>
T& ColaEstatica<T>::front() const {
    if (estaVacia()) {
        // Manejo de error: cola vac�a
        // Retornamos una referencia inv�lida, podr�a lanzar una excepci�n en lugar de hacer esto.
        return elementos[0];
    }
    return elementos[frente];
}


