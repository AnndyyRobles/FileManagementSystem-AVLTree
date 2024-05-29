#ifndef COLA_ESTATICA_H
#define COLA_ESTATICA_H

#define MAX_SIZE 100

template <typename T>
struct ColaEstatica {
    T elementos[MAX_SIZE];
    int frente, final;

    ColaEstatica();

    bool estaLlena() const;

    bool estaVacia() const;

    void enqueue(const T& elemento);

    T dequeue();

    T& front() const;
};

#endif // COLA_ESTATICA_H
