#include "Departamento.hpp"
#include "Nodo.hpp"

Nodo::Nodo(Paciente p) {
    this->p = p;
    this->N1 = nullptr;
    this->N2 = nullptr;
    this->altura = 1;
    this->clave = 0;
}

Nodo::Nodo(Departamento d) {
    this->d = d;
    this->N1 = nullptr;
    this->N2 = nullptr;
    this->altura = 1;
    this->clave = 0;
}

Nodo::Nodo(Paciente p, int clave_avl) {
    this->p = p;
    this->N1 = nullptr;
    this->N2 = nullptr;
    this->altura = 1;
    this->clave = clave_avl;
}

Nodo* Nodo::ObtenerPacienteAnterior() { return this->N2; }
void Nodo::SetNodoAnterior(Nodo* n) { this->N2 = n; }
Nodo* Nodo::ObtenerPacienteSiguiente() { return this->N1; }
Nodo* Nodo::registrarPaciente(Paciente p) { this->p = p; return this; }
void Nodo::SetNodoSiguiente(Nodo* N1) { this->N1 = N1; }
Paciente Nodo::verPaciente() { return this->p; }
Departamento Nodo::verDepartamento() { return this->d; }

int Nodo::obtenerSize(Nodo* n) {
    int size = 0;
    while (n != nullptr) {
        size++;
        n = n->ObtenerPacienteSiguiente();
    }
    return size;
}

bool Nodo::estaVacio() {
    return this->N1 == nullptr;
}

void Nodo::InsertarPacienteIndice(Paciente p, int indice) {
    if ((indice == 0) || (estaVacio())) {
        Nodo* nuevoNodo = new Nodo(p);
        nuevoNodo->SetNodoSiguiente(this->N1);
        this->N1 = nuevoNodo;
    }
    else {
        Nodo* actual = this;
        for (int i = 0; i < indice - 1 && actual != nullptr; i++) {
            actual = actual->ObtenerPacienteSiguiente();
        }
        if (actual != nullptr) {
            Nodo* nuevoNodo = new Nodo(p);
            nuevoNodo->SetNodoSiguiente(actual->ObtenerPacienteSiguiente());
            actual->SetNodoSiguiente(nuevoNodo);
        }
    }
}

Paciente Nodo::verPacienteIndice(int indice) {
    Nodo* actual = this;
    for (int i = 0; i < indice && actual != nullptr; i++) {
        actual = actual->ObtenerPacienteSiguiente();
    }
    if (actual != nullptr) return actual->verPaciente();
    else return Paciente("", "", 0, ""); 
}

void Nodo::vaciarLista(Nodo* n) {
    while (n != nullptr) {
        Nodo* siguiente = n->ObtenerPacienteSiguiente();
        delete n;
        n = siguiente;
    }
}

Nodo* Nodo::eliminarPacienteIndice(Nodo* n, int indice) {
    if (n == nullptr) return nullptr;
    if (indice == 0) {
        Nodo* siguiente = n->ObtenerPacienteSiguiente();
        delete n;
        return siguiente;
    }
    Nodo* actual = n;
    Nodo* anterior = nullptr;
    for (int i = 0; i < indice && actual != nullptr; i++) {
        anterior = actual;
        actual = actual->ObtenerPacienteSiguiente();
    }
    if (actual != nullptr) {
        anterior->SetNodoSiguiente(actual->ObtenerPacienteSiguiente());
        delete actual;
    }
    return n;
}

Nodo* Nodo::eliminarPacientePrimero(Nodo* n) {
    if (n != nullptr) { 
        Nodo* siguiente = n->ObtenerPacienteSiguiente();
        delete n;
        return siguiente;
    }
    return nullptr;
}

Nodo* Nodo::InsertarPacienteFinal(Paciente pa) {
    Nodo* aux = this;
    while (aux->ObtenerPacienteSiguiente() != nullptr) {
        aux = aux->ObtenerPacienteSiguiente();
    }
    Nodo* nuevo = new Nodo(pa);
    aux->SetNodoSiguiente(nuevo);
    return nuevo;
}

Paciente Nodo::VerPacienteInverso(Nodo* n, int numeroActual) {
    Nodo* auxiliar = n;
    int numero1 = numeroActual;
    int contador = auxiliar->obtenerSize(auxiliar);
    while (auxiliar != nullptr) {
        numero1++;
        if (numero1 < contador) {
            auxiliar = auxiliar->ObtenerPacienteSiguiente();
        }
        else break;
    }
    return auxiliar->verPaciente();
}

Nodo* Nodo::encolar(Paciente pa) {
    return InsertarPacienteFinal(pa);
}

Nodo* Nodo::desencolar(Nodo* frenteCola, Paciente& pacienteAtendido) {
    if (frenteCola == nullptr) return nullptr;
    pacienteAtendido = frenteCola->verPaciente();
    Nodo* nuevoFrente = frenteCola->ObtenerPacienteSiguiente();
    delete frenteCola;
    return nuevoFrente;
}

Paciente Nodo::verFrente() {
    return this->p;
}

void Nodo::agregarDecision(Nodo* opcionIzquierda_Si, Nodo* opcionDerecha_No) {
    this->N1 = opcionIzquierda_Si;
    this->N2 = opcionDerecha_No;
}

Nodo* Nodo::tomarCaminoIzquierdo() { return this->N1; }
Nodo* Nodo::tomarCaminoDerecho() { return this->N2; }

bool Nodo::esHojaDecision() {
    return (this->N1 == nullptr && this->N2 == nullptr);
}

int Nodo::getAltura(Nodo* n) {
    if (n == nullptr) return 0;
    return n->altura;
}

int Nodo::obtenerFactorBalance(Nodo* n) {
    if (n == nullptr) return 0;
    return getAltura(n->N1) - getAltura(n->N2);
}

Nodo* Nodo::rotacionDerecha(Nodo* y) {
    Nodo* x = y->N1;
    Nodo* T2 = x->N2;

    x->N2 = y;
    y->N1 = T2;

    y->altura = std::max(getAltura(y->N1), getAltura(y->N2)) + 1;
    x->altura = std::max(getAltura(x->N1), getAltura(x->N2)) + 1;

    return x; 
}

Nodo* Nodo::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->N2;
    Nodo* T2 = y->N1;

    y->N1 = x;
    x->N2 = T2;

    x->altura = std::max(getAltura(x->N1), getAltura(x->N2)) + 1;
    y->altura = std::max(getAltura(y->N1), getAltura(y->N2)) + 1;

    return y;
}

Nodo* Nodo::insertarAVL(Nodo* nodo, Paciente p, int claveBusqueda) {
    if (nodo == nullptr) {
        return new Nodo(p, claveBusqueda);
    }

    if (claveBusqueda < nodo->clave)
        nodo->N1 = insertarAVL(nodo->N1, p, claveBusqueda);
    else if (claveBusqueda > nodo->clave)
        nodo->N2 = insertarAVL(nodo->N2, p, claveBusqueda);
    else
        return nodo; 

    nodo->altura = 1 + std::max(getAltura(nodo->N1), getAltura(nodo->N2));

    int balance = obtenerFactorBalance(nodo);

    if (balance > 1 && claveBusqueda < nodo->N1->clave)
        return rotacionDerecha(nodo);

    if (balance < -1 && claveBusqueda > nodo->N2->clave)
        return rotacionIzquierda(nodo);

    if (balance > 1 && claveBusqueda > nodo->N1->clave) {
        nodo->N1 = rotacionIzquierda(nodo->N1);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && claveBusqueda < nodo->N2->clave) {
        nodo->N2 = rotacionDerecha(nodo->N2);
        return rotacionIzquierda(nodo);
    }

    return nodo; 
}