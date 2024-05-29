#pragma once
#ifndef PILA_ESTATICA_H
#define PILA_ESTATICA_H

#define MAX_SIZE 100

template <typename T>
struct PilaEstatica {
    T elementos[MAX_SIZE];
    int tope;

    PilaEstatica();

    bool estaLlena() const;

    bool estaVacia() const;

    void push(const T& elemento);

    T pop();

    T& peek() const;
};

#endif // PILA_ESTATICA_H