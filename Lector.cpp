#include "Paciente.hpp"
#include "Nodo.hpp"

class Lector {
private:
    Nodo* primerNodo;
public:
    Lector(Nodo* inicio = nullptr) {
        this->primerNodo = inicio;
    }
    Nodo* LeerDesdeElComienzo() {
        return this->primerNodo;
    }
    void mostrarTodosLosPacientes() {
        Nodo* actual = LeerDesdeElComienzo();
        while (actual != nullptr) {
            Paciente p = actual->verPaciente();
            actual = actual->ObtenerPacienteSiguiente();
        }
    }
};