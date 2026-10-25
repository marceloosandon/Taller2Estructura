#pragma once
#include "Paciente.hpp"
#include <string>

class NodoDecision {
public:
    int tipoCondicion;
    std::string servicio;
    NodoDecision* izquierdo_Si;
    NodoDecision* derecho_No;

    NodoDecision(int condicion)
        : tipoCondicion(condicion), servicio(""), izquierdo_Si(nullptr), derecho_No(nullptr) {
    }

    NodoDecision(std::string serv)
        : tipoCondicion(0), servicio(serv), izquierdo_Si(nullptr), derecho_No(nullptr) {
    }
};

class ArbolDecision {
private:
    NodoDecision* raiz;
    void destruirRecursivo(NodoDecision* nodo);
    bool evaluarCondicion(Paciente p, int tipoCondicion);

public:
    ArbolDecision();
    ~ArbolDecision();
    std::string evaluar(Paciente p);
};