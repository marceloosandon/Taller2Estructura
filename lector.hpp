#include "Paciente.hpp"
#include "Nodo.hpp"
#include "Departamento.hpp"
#include "Lector.cpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

class lector {
public:
    Nodo* cargarDepartamento() {
        ifstream archivo("pacientes.txt");
        if (archivo.fail()) {
            cerr << endl;
        }
        Nodo* cabeza = nullptr;
        Nodo* actual = nullptr;
        string token0, token1, token2, token3;
        while (getline(archivo, token0, ';') &&
            getline(archivo, token1, ';') &&
            getline(archivo, token2, ';') &&
            getline(archivo, token3, '\n')) {
            if (token3 == "Cardiologia" || token3 == "Urgencias" || token3 == "Cirugia" || token3 == "Pediatria" || token3 == "Traumatologia" || token3 == "Neurologia" || token3 == "Medicina General" || token3 == "Hospitalizacion") {
                Departamento d(token3);
                bool existe = false;
                Nodo* aux = cabeza;
                while (aux != nullptr) {
                    if (aux->verDepartamento().getTipo() == d.getTipo()) {
                        existe = true;
                        break;
                    }
                    aux = aux->ObtenerPacienteSiguiente();
                }
                if (existe == false) {
                    Nodo* nuevoNodo = new Nodo(d);
                    if (cabeza == nullptr) {
                        cabeza = nuevoNodo;
                        actual = nuevoNodo;
                    }
                    else {
                        actual->SetNodoSiguiente(nuevoNodo);
                        actual = nuevoNodo;
                    }
                }
            }
        }
        archivo.close();
        return cabeza;
    }
    Nodo* cargar() {
        ifstream archivo("pacientes.txt");
        if (archivo.fail()) {
            cerr << "No se pudo abrir el archivo." << endl;
            exit(1);
        }
        Nodo* cabeza = nullptr;
        Nodo* actual = nullptr;

        string token0, token1, token2, token3;

        while (getline(archivo, token0, ';') &&
            getline(archivo, token1, ';') &&
            getline(archivo, token2, ';') &&
            getline(archivo, token3, '\n')) {

            int entero = stoi(token2);
            if (token3 == "Cardiologia" || token3 == "Urgencias" || token3 == "Cirugia" || token3 == "Pediatria" || token3 == "Traumatologia" || token3 == "Neurologia" || token3 == "Medicina General" || token3 == "Hospitalizacion") {
                Paciente p(token0, token1, entero, token3);
                Nodo* nuevoNodo = new Nodo(p);

                if (cabeza == nullptr) {
                    cabeza = nuevoNodo;
                    actual = nuevoNodo;
                }
                else {
                    actual->SetNodoSiguiente(nuevoNodo);
                    actual = nuevoNodo;
                }
            }
        }
        archivo.close();
        Nodo* p1 = cabeza;
        while (p1 != nullptr && p1->ObtenerPacienteSiguiente() != nullptr) {
            Nodo* p2 = p1;
            while (p2->ObtenerPacienteSiguiente() != nullptr) {
                if (p1->verPaciente().getID() == p2->ObtenerPacienteSiguiente()->verPaciente().getID() && p1->verPaciente().getNombre() == p2->ObtenerPacienteSiguiente()->verPaciente().getNombre() && p1->verPaciente().getEdad() == p2->ObtenerPacienteSiguiente()->verPaciente().getEdad() && p1->verPaciente().getServicio() == p2->ObtenerPacienteSiguiente()->verPaciente().getServicio()) {
                    Nodo* nodoAEliminar = p2->ObtenerPacienteSiguiente();
                    p2->SetNodoSiguiente(nodoAEliminar->ObtenerPacienteSiguiente());
                    delete nodoAEliminar;
                }
                else {
                    p2 = p2->ObtenerPacienteSiguiente();
                }
            }
            p1 = p1->ObtenerPacienteSiguiente();
        }
        return cabeza;
    }
    Nodo* eliminarPaciente(string nombre, Nodo* n, Paciente p) {
        while (n != nullptr) {
            if (n->verPaciente().getNombre() == nombre) {
				n->ObtenerPacienteSiguiente()->SetNodoSiguiente(nullptr);
            }
            n = n->ObtenerPacienteSiguiente();
        }
        return n;
    }
    int contar(int numero) {
        return numero;
    }
    Paciente cargarSUBDATOS(Paciente p) {
        string NombrePaciente = p.getNombre();
        string NombreArchivo = p.getNombre() + ".txt";
        ifstream archivo(NombreArchivo);
        Nodo* cabeza = nullptr;
        Nodo* actual = nullptr;
        Paciente vacio;
        string Tipo1, Tipo2, Tipo3, Tipo4, Tipo5, Tipo6, Tipo7, Tipo8, Tipo9, Tipo10, Tipo11;
        while (getline(archivo, Tipo1, ';') &&
            getline(archivo, Tipo2, ';') &&
            getline(archivo, Tipo3, ';') &&
            getline(archivo, Tipo4, ';') &&
            getline(archivo, Tipo5, ';') &&
            getline(archivo, Tipo6, ';') &&
            getline(archivo, Tipo7, ';') &&
            getline(archivo, Tipo8, ';') &&
            getline(archivo, Tipo9, ';') &&
            getline(archivo, Tipo10, ';') &&
            getline(archivo, Tipo11, '\n')) {

            int Edad = stoi(Tipo3);
            int Presion = stoi(Tipo4);
            float Temperatura = stof(Tipo5);
            int Dolor = stoi(Tipo6);
            bool Trauma = Tipo8 == "1";
            bool neurologico = Tipo9 == "1";
            bool cirugia = Tipo10 == "1";
            int Hospitalacion = stoi(Tipo11);
            if (Edad > 0 && Dolor >= 0 && Hospitalacion >= 0 && Tipo2 == NombrePaciente && p.getEdad() == Edad && p.getID() == Tipo1) {
                Paciente pr(Tipo1, Tipo2, Edad, Presion, Temperatura, Dolor, Tipo7, Trauma, neurologico, cirugia, Hospitalacion);
                return pr;
            }
            else {
                if (Tipo2 != NombrePaciente) {
                    cout << "Suplantacion de Nombre: " << NombrePaciente << endl;
                }
                if (p.getEdad() != Edad) {
                    cout << "Suplantación de Edad: " << p.getEdad() << endl;
                }
                if (p.getID() != Tipo1) {
                    cout << "Suplantación de ID: " << p.getID() << endl;
                }
                return vacio;
            }
        }
        archivo.close();
        return vacio;
    }
    string cargarDatosPaciente(Paciente p) {
        if (p.getEdad() < 14) {
            p = cargarSUBDATOS(p);
            p.setServicio("Pediatria");
            return "Pediatria";
        }
        else {
            if (p.getTrauma() == true) {
                if (p.getrequiereCirugía() == true) {
                    p = cargarSUBDATOS(p);
                    p.setServicio("Cirugia");
                    return "Cirugia";
                }
                else {
                    p = cargarSUBDATOS(p);
                    p.setServicio("Traumatologia");
                    return "Traumatologia";
                }
            }
            else {
                if (p.getsintomasNeurologicos() == true) {
                    p = cargarSUBDATOS(p);
                    p.setServicio("Neurologia");
                    return "Neurologia";
                }
                else {
                    if (p.getTipoDolor() == "pecho") {
                        p = cargarSUBDATOS(p);
                        p.setServicio("Cardiologia");
                        return "Cardiologia";
                    }
                    else {
                        if (p.getTemperatura() >= 38.5 || p.getDolor() >= 8) {
                            p = cargarSUBDATOS(p);
                            p.setServicio("Urgencias");
                            return "Urgencias";
                        }
                        else {
                            if (p.getDiasHospitalizacion() >= 2) {
                                p = cargarSUBDATOS(p);
                                p.setServicio("Hospitalizacion");
                                return "Hospitalizacion";
                            }
                            else {
                                p = cargarSUBDATOS(p);
                                p.setServicio("Medicina General");
                                return "Medicina General";
                            }
                        }
                    }
                }
            }
        }
        return "Invalido";
    }
    bool buscarRecursivo(Nodo* actual, string caracter, Nodo* anterior) {
        if (actual == nullptr) return false;
        if (caracter == actual->verPaciente().getID() || caracter == actual->verPaciente().getNombre()) {
            std::cout << "Paciente Encontrado: " << actual->verPaciente().getNombre() << "\n";
            if (anterior != nullptr) {
                std::cout << "El nodo anterior (padre) es: " << anterior->verPaciente().getNombre() << "\n";
            }
            else {
                std::cout << "No tiene nodo anterior (es la raiz del arbol).\n";
            }
            return true;
        }

        if (buscarRecursivo(actual->tomarCaminoIzquierdo(), caracter, actual)) return true;

        if (buscarRecursivo(actual->tomarCaminoDerecho(), caracter, actual)) return true;

        return false;
    }

    void buscar(Nodo* raiz, string caracter) {
        if (!buscarRecursivo(raiz, caracter, nullptr)) {
            std::cout << "nullptr (No encontrado)\n";
        }
    }
};
