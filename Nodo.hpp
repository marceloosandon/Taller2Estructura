#pragma once
#include "Paciente.hpp"
#include "Departamento.hpp"

class Nodo {
private:
    Paciente p;
    Departamento d;

    Nodo* N1; 
    Nodo* N2; 

    int altura;
    int clave; 

public:
    Nodo(Departamento d);
    Nodo(Paciente p);
    Nodo(Paciente p, int clave_avl);

    Nodo* ObtenerPacienteSiguiente();
    Nodo* ObtenerPacienteAnterior();
    Nodo* registrarPaciente(Paciente p);
    void SetNodoSiguiente(Nodo* N1);
    void SetNodoAnterior(Nodo* N2);
    int obtenerSize(Nodo* n);
    bool estaVacio();
    void InsertarPacienteIndice(Paciente p, int indice);
    Nodo* InsertarPacienteFinal(Paciente p);
    Paciente VerPacienteInverso(Nodo* n, int numeroactual);
    Paciente verPacienteIndice(int indice);
    void vaciarLista(Nodo* lista);
    Paciente verPaciente();
    Departamento verDepartamento();
    Nodo* eliminarPacienteIndice(Nodo* n, int indice);
    Nodo* eliminarPacientePrimero(Nodo* n);

    Nodo* encolar(Paciente pa);
    Nodo* desencolar(Nodo* frenteCola, Paciente& pacienteAtendido);
    Paciente verFrente();

    void agregarDecision(Nodo* opcionIzquierda_Si, Nodo* opcionDerecha_No);
    Nodo* tomarCaminoIzquierdo();
    Nodo* tomarCaminoDerecho();
    bool esHojaDecision();

    int getAltura(Nodo* n);
    int obtenerFactorBalance(Nodo* n);
    Nodo* rotacionDerecha(Nodo* y);
    Nodo* rotacionIzquierda(Nodo* x);

    Nodo* insertarAVL(Nodo* nodo, Paciente p, int clave);

    ~Nodo() {}
};