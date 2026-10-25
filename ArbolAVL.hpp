#pragma once
#include "Paciente.hpp"
#include <string>
#include <iostream>

using namespace std;

class NodoAVL {
public:
    Paciente p;
    std::string idClave;
    int altura;
    NodoAVL* izq; 
    NodoAVL* der; 

    NodoAVL(Paciente pac) : p(pac), idClave(pac.getID()), altura(1), izq(nullptr), der(nullptr) {}
};

class ArbolAVL {
private:
    NodoAVL* raiz; 

    int obtenerAltura(NodoAVL* N) {
        if (N == nullptr) return 0;
        return N->altura;
    }

    int maximo(int a, int b) {
        return (a > b) ? a : b;
    }

    int obtenerBalance(NodoAVL* N) {
        if (N == nullptr) return 0;
        return obtenerAltura(N->izq) - obtenerAltura(N->der);
    }

    void documentarRecursivo(
        NodoAVL* nodo,
        const string& prefijo,
        const string& etiqueta
    ) {
        if (nodo == nullptr) {
            cout << prefijo << etiqueta << "(vacio)\n";
            return;
        }

        cout << prefijo << etiqueta
            << "ID: " << nodo->idClave
            << " | Nombre: " << nodo->p.getNombre()
            << " | Altura: " << nodo->altura
            << " | FB: " << obtenerBalance(nodo)
            << "\n";

        documentarRecursivo(
            nodo->izq, prefijo + "    ", "Izq: "
        );

        documentarRecursivo(
            nodo->der, prefijo + "    ", "Der: "
        );
    }

    NodoAVL* rotacionDerecha(NodoAVL* y) {
        NodoAVL* x = y->izq;
        NodoAVL* T2 = x->der;

        x->der = y;
        y->izq = T2;

        y->altura = maximo(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
        x->altura = maximo(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

        return x;
    }

    NodoAVL* rotacionIzquierda(NodoAVL* x) {
        NodoAVL* y = x->der;
        NodoAVL* T2 = y->izq;

        y->izq = x;
        x->der = T2;

        x->altura = maximo(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
        y->altura = maximo(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

        return y;
    }

    NodoAVL* insertarRecursivo(NodoAVL* nodo, Paciente pac) {
        if (nodo == nullptr) return new NodoAVL(pac);

        if (pac.getID() < nodo->idClave) {
            nodo->izq = insertarRecursivo(nodo->izq, pac);
        }
        else if (pac.getID() > nodo->idClave) {
            nodo->der = insertarRecursivo(nodo->der, pac);
        }
        else {
            return nodo; 
        }

        nodo->altura = 1 + maximo(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

        int balance = obtenerBalance(nodo);

        if (balance > 1 && pac.getID() < nodo->izq->idClave)
            return rotacionDerecha(nodo);

        if (balance < -1 && pac.getID() > nodo->der->idClave)
            return rotacionIzquierda(nodo);

        if (balance > 1 && pac.getID() > nodo->izq->idClave) {
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }

        if (balance < -1 && pac.getID() < nodo->der->idClave) {
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    bool buscarPorNombre(NodoAVL* nodo, string nombreBuscado, string rutaAcumulada) {
        if (nodo == nullptr) return false;

        if (nodo->p.getNombre() == nombreBuscado) {
            imprimirPacienteEncontrado(nodo, rutaAcumulada);
            return true;
        }

        if (buscarPorNombre(nodo->izq, nombreBuscado, rutaAcumulada + "0 ")) return true;
        if (buscarPorNombre(nodo->der, nombreBuscado, rutaAcumulada + "1 ")) return true;

        return false;
    }

    void mostrarBalanceRecursivo(NodoAVL* nodo) {
        if (nodo == nullptr) return;

        mostrarBalanceRecursivo(nodo->izq);

        cout << "ID: " << nodo->idClave
            << " | Nombre: " << nodo->p.getNombre()
            << " | Altura: " << nodo->altura
            << " | Factor de balance: "
            << obtenerBalance(nodo) << "\n";

        mostrarBalanceRecursivo(nodo->der);
    }

    void inordenRecursivo(NodoAVL* nodo) {
        if (nodo != nullptr) {
            inordenRecursivo(nodo->izq);
            cout << "Paciente: " << nodo->p.getNombre() << " (" << nodo->p.getID() << ")\n";
            inordenRecursivo(nodo->der);
        }
    }

    void preordenRecursivo(NodoAVL* nodo) {
        if (nodo != nullptr) {
            cout << "Paciente: " << nodo->p.getNombre() << " (" << nodo->p.getID() << ")\n";
            preordenRecursivo(nodo->izq);
            preordenRecursivo(nodo->der);
        }
    }

    void postordenRecursivo(NodoAVL* nodo) {
        if (nodo != nullptr) {
            postordenRecursivo(nodo->izq);
            postordenRecursivo(nodo->der);
            cout << "Paciente: " << nodo->p.getNombre() << " (" << nodo->p.getID() << ")\n";
        }
    }

    void imprimirPacienteEncontrado(NodoAVL* nodo, std::string ruta) {
        std::cout << "Paciente encontrado:\n";
        std::cout << "ID: " << nodo->p.getID() << "\n";
        std::cout << "Nombre: " << nodo->p.getNombre() << "\n";
        std::cout << "Edad: " << nodo->p.getEdad() << "\n";
        std::cout << "Departamento: " << nodo->p.getServicio() << "\n";
        std::cout << "Ruta de busqueda: " << (ruta.empty() ? "Raiz (Sin desplazamientos)" : ruta) << "\n\n";
    }

public:
    ArbolAVL() : raiz(nullptr) {}

    void insertar(Paciente pac) {
        raiz = insertarRecursivo(raiz, pac);
    }

    void documentarArbol() {
        if (raiz == nullptr) {
            cout << "El arbol AVL esta vacio\n";
            return;
        }

        cout << "=== ESTRUCTURA DEL ARBOL AVL ===\n";
        cout << "Altura total: " << obtenerAltura(raiz) << "\n\n";

        documentarRecursivo(raiz, "", "Raiz: ");
    }

    bool buscar(std::string criterio) {
        if (raiz == nullptr) return false;

        bool esID = true;
        for (char c : criterio) {
            if (!isdigit(c)) {
                esID = false;
                break;
            }
        }

        if (esID) {
            std::string ruta = "";
            NodoAVL* actual = raiz; 

            while (actual != nullptr) {
                if (actual->idClave == criterio) {
                    imprimirPacienteEncontrado(actual, ruta);
                    return true;
                }
                if (criterio < actual->idClave) {
                    ruta += "0 ";
                    actual = actual->izq;
                }
                else {
                    ruta += "1 ";
                    actual = actual->der;
                }
            }
            return false;
        }
        else {
            return buscarPorNombre(raiz, criterio, "");
        }
    }

    void mostrarInorden() {
        if (raiz == nullptr) {
            cout << "Sin pacientes\n";
        }
        else {
            inordenRecursivo(raiz);
        }
    }

    void mostrarAlturaArbol() {
        cout << "Altura del arbol AVL: "
            << obtenerAltura(raiz) << "\n";
    }

    void mostrarPreorden() {
        if (raiz == nullptr) {
            cout << "Sin pacientes\n";
        }
        else {
            preordenRecursivo(raiz);
        }
    }

    void mostrarPostorden() {
        if (raiz == nullptr) {
            cout << "Sin pacientes\n";
        }
        else {
            postordenRecursivo(raiz);
        }
    }

    void mostrarFactoresBalance() {
        if (raiz == nullptr) {
            cout << "Sin pacientes\n";
            return;
        }

        cout << "=== FACTORES DE BALANCE ===\n";
        cout << "FB = altura izquierda - altura derecha\n\n";

        mostrarBalanceRecursivo(raiz);
    }
};
