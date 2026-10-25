#include "Paciente.hpp"

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

ArbolDecision::ArbolDecision() {
    NodoDecision* hojaPediatria = new NodoDecision("Pediatria");
    NodoDecision* hojaCirugia = new NodoDecision("Cirugia");
    NodoDecision* hojaTraumatologia = new NodoDecision("Traumatologia");
    NodoDecision* hojaNeurologia = new NodoDecision("Neurologia");
    NodoDecision* hojaCardiologia = new NodoDecision("Cardiologia");
    NodoDecision* hojaUrgencias = new NodoDecision("Urgencias");
    NodoDecision* hojaHospitalizacion = new NodoDecision("Hospitalizacion");
    NodoDecision* hojaGeneral = new NodoDecision("Medicina General");

    NodoDecision* cond7 = new NodoDecision(7);
    cond7->izquierdo_Si = hojaHospitalizacion;
    cond7->derecho_No = hojaGeneral;

    NodoDecision* cond6 = new NodoDecision(6);
    cond6->izquierdo_Si = hojaUrgencias;
    cond6->derecho_No = cond7;

    NodoDecision* cond5 = new NodoDecision(5);
    cond5->izquierdo_Si = hojaCardiologia;
    cond5->derecho_No = cond6;

    NodoDecision* cond4 = new NodoDecision(4);
    cond4->izquierdo_Si = hojaNeurologia;
    cond4->derecho_No = cond5;

    NodoDecision* cond3 = new NodoDecision(3);
    cond3->izquierdo_Si = hojaCirugia;
    cond3->derecho_No = hojaTraumatologia;

    NodoDecision* cond2 = new NodoDecision(2);
    cond2->izquierdo_Si = cond3;
    cond2->derecho_No = cond4;

    raiz = new NodoDecision(1);
    raiz->izquierdo_Si = hojaPediatria;
    raiz->derecho_No = cond2;
}

void ArbolDecision::destruirRecursivo(NodoDecision* nodo) { 
    if (nodo != nullptr) {
        destruirRecursivo(nodo->izquierdo_Si);
        destruirRecursivo(nodo->derecho_No);
        delete nodo;
    }
}

ArbolDecision::~ArbolDecision() {
    destruirRecursivo(raiz);
}

bool ArbolDecision::evaluarCondicion(Paciente p, int tipoCondicion) {
    switch (tipoCondicion) {
    case 1: return p.getEdad() < 14;
    case 2: return p.getTrauma() == 1;
    case 3: return p.getrequiereCirugía() == 1;
    case 4: return p.getsintomasNeurologicos() == 1;
    case 5: return p.getTipoDolor() == "pecho";
    case 6: return (p.getTemperatura() > 38.5f || p.getDolor() >= 8);
    case 7: return p.getDiasHospitalizacion() >= 2;
    default: return false;
    }
}

std::string ArbolDecision::evaluar(Paciente p) {
    NodoDecision* actual = raiz; 
    while (actual->tipoCondicion != 0) {
        if (evaluarCondicion(p, actual->tipoCondicion)) {
            actual = actual->izquierdo_Si;
        }
        else {
            actual = actual->derecho_No;
        }
    }
    return actual->servicio;
}