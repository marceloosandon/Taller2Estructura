#define _HAS_STD_BYTE 0
#include <iostream>
#include "Nodo.hpp"
#include "Paciente.hpp"
#include "Departamento.hpp"
#include "lector.hpp"
#include <string>
#include <windows.h>

using namespace std;

void imprimirPorDepartamento(Nodo* nodo, string depto, int& contador) {
    if (nodo == nullptr) return;

    imprimirPorDepartamento(nodo->tomarCaminoIzquierdo(), depto, contador);

    if (nodo->verPaciente().getServicio() == depto) {
        cout << nodo->verPaciente().getNombre() << " " << nodo->verPaciente().getID() << " | ";
        contador++;
    }

    imprimirPorDepartamento(nodo->tomarCaminoDerecho(), depto, contador);
}

int main() {
    bool Terminar = false;
    int opcion;
    int contador = 0;
    lector l;
    Nodo* raizAVL = nullptr;   
    Nodo* Departamentos = nullptr;
    Nodo* frenteCola = l.cargar(); 
    int contadorCiclo = 0;
    if (frenteCola != nullptr) {
        contadorCiclo = frenteCola->obtenerSize(frenteCola);
    }
    else {
        cout << "No está el archivo de pacientes.txt, colocalo en la misma ubicación del compilado" << endl;
    }
    while (!Terminar) {
        cout << "\n === HOSPITAL MARMAJA === " << endl;
        cout << "1. Atender Pacientes " << endl;
        cout << "2. Ver Departamento " << endl;
        cout << "3. Revisar Historial de Atencion" << endl;
        cout << "4. Salir \n" << endl;
        cout << "Seleccionar opcion: ";
        cin >> opcion;
        cout << endl;

        if (opcion == 1) {
            contador = 0;
            int Cantidad = 0;
            Nodo* respaldo = frenteCola;

            if (respaldo != nullptr) cout << " === PACIENTES EN ESPERA === " << endl;
            else cout << " No hay Pacientes en espera " << endl;

            if (contadorCiclo > 0) {
                while (respaldo != nullptr) {
                    Paciente pe = respaldo->verPaciente();
                    contador++;
                    cout << contador << ". " << pe.getID() << " - " << pe.getNombre() << endl;
                    respaldo = respaldo->ObtenerPacienteSiguiente();
                }

                cout << "Indique la cantidad de pacientes a atender: ";
                cin >> Cantidad;
                cout << endl;

                if (Cantidad < 0) cout << " Cantidad Invalida de pacientes a atender " << endl;

                if (contadorCiclo > 0 && Cantidad <= contadorCiclo && Cantidad > 0) {
                    cout << " === ATENDIENDO PACIENTES === " << endl;

                    for (int i = 0; i < Cantidad; i++) {
                        if (frenteCola != nullptr) {
                            Paciente p = frenteCola->verPaciente();
                            p = l.cargarSUBDATOS(p);
                            p.setServicio(l.cargarDatosPaciente(p));
                            string resultado = p.ValidarDatos(p);

                            if (resultado != "Invalido" && p.getNombre() != "" && p.getEdad() >= 0) {
                                cout << "ID: " << p.getID() << "\nNombre: " << p.getNombre()
                                    << "\nEdad: " << p.getEdad() << "\nruta: " << resultado << "\n\n"
                                    << "Servicio Asignado: " << p.getServicio() << "\n\n"
                                    << "Paciente insertado en el AVL de " << p.getServicio() << "\n\n";

                                int clave_avl;
                                try { clave_avl = stoi(p.getID()); }
                                catch (...) { clave_avl = p.getEdad(); } 

                                raizAVL = (raizAVL == nullptr) ? new Nodo(p, clave_avl)
                                    : raizAVL->insertarAVL(raizAVL, p, clave_avl);
                            }
                            else {
                                cout << "Persona Invalida Ingresada, Eliminando \n";
                            }

                            Paciente atendido;
                            frenteCola = frenteCola->desencolar(frenteCola, atendido);
                        }
                        else {
                            break;
                        }
                    }
                    contadorCiclo -= Cantidad;
                }
            }
        }
        else if (opcion == 2) {
            Departamentos = l.cargarDepartamento();
            if (Departamentos != nullptr) {
                cout << " === ESTADO DE LOS DEPARTAMENTOS === " << endl;

                Nodo* iteradorDept = Departamentos;
                while (iteradorDept != nullptr) {
                    string nombreDepartamento = iteradorDept->verDepartamento().getTipo();
                    cout << "\n" << nombreDepartamento << endl;
                    cout << "Pacientes: ";

                    int contadorDept = 0;

                    imprimirPorDepartamento(raizAVL, nombreDepartamento, contadorDept);

                    if (contadorDept == 0) {
                        cout << "Sin pacientes";
                    }
                    cout << endl;

                    iteradorDept = iteradorDept->ObtenerPacienteSiguiente();
                }
            }
            else {
                cout << "Departamento Invalido o nulo" << endl;
            }
            cout << endl;
        }
        else if (opcion == 3) {
            string caracter;
            if (raizAVL == nullptr) {
                cout << "No hay Pacientes Guardados en el Historial AVL" << endl << endl;
            }
            else {
                cout << " === BUSCAR PACIENTE ===" << endl;
                cout << "Indique el ID o Nombre del paciente: ";
                cin >> caracter;
                cout << "Buscando en el AVL...\n";

                l.buscar(raizAVL, caracter);
                
                //funcion asociada a la busqueda

                cout << endl;
            }
        }
        else if (opcion == 4) {
            Terminar = true;
            cout << "Hasta luego :D." << endl;
            break;
        }
    }
    return 0;
}
