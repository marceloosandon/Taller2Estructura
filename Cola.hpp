#pragma once
#include "Paciente.hpp"

class NodoCola {
public:
    Paciente p;
    NodoCola* siguiente;
    NodoCola(Paciente paciente) : p(paciente), siguiente(nullptr) {}
};

class Cola {
private:
    NodoCola* frente;
    NodoCola* final;
public:
    Cola() : frente(nullptr), final(nullptr) {}
    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    void encolar(Paciente p) {
        NodoCola* nuevo = new NodoCola(p);
        if (estaVacia()) {
            frente = final = nuevo;
        }
        else {
            final->siguiente = nuevo;
            final = nuevo;
        }
    }

    Paciente desencolar() {
        if (estaVacia()) return Paciente();
        NodoCola* temp = frente;
        Paciente p = temp->p;
        frente = frente->siguiente;
        if (frente == nullptr) final = nullptr;
        delete temp;
        return p;
    }

    bool estaVacia() { return frente == nullptr; }
};