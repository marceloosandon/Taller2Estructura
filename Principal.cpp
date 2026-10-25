#include <iostream>
#include <fstream>
#include <string>
#include "Paciente.hpp"
#include "Cola.hpp"
#include "ArbolDecision.hpp"
#include "ArbolAVL.hpp"

using namespace std;

ArbolAVL avl_Pediatria, avl_Cirugia, avl_Traumatologia, avl_Neurologia,
avl_Cardiologia, avl_Urgencias, avl_Hospitalizacion, avl_General;

void procesarPacientes() {
    Cola filaPacientes;
    ifstream archivo("pacientes.txt");

    if (!archivo.is_open()) {
        cout << "Error: No se encontro pacientes.txt\n";
        return;
    }

    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }
        if (linea.empty()) continue;

        int contadorPuntoComa = 0;
        for (char c : linea) {
            if (c == ';') contadorPuntoComa++;
        }

        if (contadorPuntoComa < 3) {
            continue;
        }

        string datos[4];
        size_t pos = 0, next_pos = 0;
        int i = 0;

        while ((next_pos = linea.find(';', pos)) != string::npos && i < 3) {
            datos[i] = linea.substr(pos, next_pos - pos);
            pos = next_pos + 1;
            i++;
        }
        datos[3] = linea.substr(pos);

        try {
            Paciente p(datos[0], datos[1], stoi(datos[2]), 0.0f, 0, 0, "", 0, 0, 0, 0);

            p.setServicio(datos[3]);
            string nombreArchivo = p.getNombre() + ".txt";
            ifstream archivoPaciente(nombreArchivo);

            if (archivoPaciente.is_open()) {
                string datoLinea;

                if (getline(archivoPaciente, datoLinea)) {
                    if (!datoLinea.empty() && datoLinea.back() == '\r') {
                        datoLinea.pop_back();
                    }

                    string atributos[11];
                    size_t pos_pac = 0, next_pos_pac = 0;
                    int j = 0;

                    while ((next_pos_pac = datoLinea.find(';', pos_pac)) != string::npos && j < 10) {
                        atributos[j] = datoLinea.substr(pos_pac, next_pos_pac - pos_pac);
                        pos_pac = next_pos_pac + 1;
                        j++;
                    }
                    atributos[10] = datoLinea.substr(pos_pac);

                    p.setTemperatura(stof(atributos[3]));
                    p.setDolor(stoi(atributos[5]));
                    p.setTipoDolor(atributos[6]);
                    p.setTrauma(stoi(atributos[7]));
                    p.setsintomasNeurologicos(stoi(atributos[8]));
                    p.setrequiereCirugia(stoi(atributos[9]));
                    p.setDiasHospitalizacion(stoi(atributos[10]));
                }
                archivoPaciente.close();
            }
            else {
                cout << "Aviso: No se encontro el archivo de historial: " << nombreArchivo << "\n";
            }
            filaPacientes.encolar(p);
        }
        catch (const std::exception& e) {
            cout << "Omitiendo paciente con formato invalido (ID: " << datos[0] << ")\n";
        }
    }
    archivo.close();

    cout << "=== ATENDIENDO PACIENTES ===\n\n";

    while (!filaPacientes.estaVacia()) {
        Paciente actual = filaPacientes.desencolar();

        string servicioAsignado = actual.getServicio();

        if (servicioAsignado == "Medicina General") avl_General.insertar(actual);
        else if (servicioAsignado == "Pediatria") avl_Pediatria.insertar(actual);
        else if (servicioAsignado == "Traumatologia") avl_Traumatologia.insertar(actual);
        else if (servicioAsignado == "Neurologia") avl_Neurologia.insertar(actual);
        else if (servicioAsignado == "Cardiologia") avl_Cardiologia.insertar(actual);
        else if (servicioAsignado == "Urgencias") avl_Urgencias.insertar(actual);
        else if (servicioAsignado == "Hospitalizacion") avl_Hospitalizacion.insertar(actual);
        else if (servicioAsignado == "Cirugia") avl_Cirugia.insertar(actual);

        cout << "ID: " << actual.getID() << "\n";
        cout << "Nombre: " << actual.getNombre() << "\n";
        cout << "Edad: " << actual.getEdad() << "\n";
        cout << "Temperatura: " << actual.getTemperatura() << "\n";
        cout << "Dolor: " << actual.getDolor() << "\n";
        cout << "TipoDolor: " << actual.getTipoDolor() << "\n";
        cout << "Trauma: " << actual.getTrauma() << "\n";
        cout << "SintomasNeurologicos: " << actual.getsintomasNeurologicos() << "\n";
        cout << "RequiereCirugia: " << actual.getrequiereCirugía() << "\n";
        cout << "DiasHospitalizacion: " << actual.getDiasHospitalizacion() << "\n\n";

        cout << "Ruta: " << actual.ValidarDatos(actual) << "\n\n";

        cout << "Servicio asignado: " << servicioAsignado << "\n";
        cout << "Paciente insertado en el AVL de " << servicioAsignado << ".\n\n";
    }
}

void mostrarOperacionAVL(ArbolAVL& arbol, int metodo) {
    switch (metodo) {
    case 1:
        arbol.mostrarInorden();
        break;
    case 2:
        arbol.mostrarPreorden();
        break;
    case 3:
        arbol.mostrarPostorden();
        break;
    case 4:
        arbol.mostrarAlturaArbol();
        break;
    case 5:
        arbol.mostrarFactoresBalance();
        break;
    case 6:
        arbol.documentarArbol();
        break;
    }
}

void verDepartamentos() {
    cout << "=== VER DEPARTAMENTOS ===\n";
    cout << "Seleccione la operacion:\n";
    cout << "1. Inorden\n";
    cout << "2. Preorden\n";
    cout << "3. Postorden\n";
    cout << "4. Mostrar altura del arbol\n";
    cout << "5. Mostrar factores de balance\n";
    cout << "6. Documentar estructura del arbol\n";
    cout << "Opcion: ";

    int metodo;
    cin >> metodo;

    if (metodo < 1 || metodo > 6) {
        cout << "Opcion invalida\n";
        return;
    }

    cout << "\n=== ESTADO DE LOS DEPARTAMENTOS ===\n\n";

    cout << "Urgencias\n";
    mostrarOperacionAVL(avl_Urgencias, metodo);

    cout << "\nMedicina General\n";
    mostrarOperacionAVL(avl_General, metodo);

    cout << "\nPediatria\n";
    mostrarOperacionAVL(avl_Pediatria, metodo);

    cout << "\nTraumatologia\n";
    mostrarOperacionAVL(avl_Traumatologia, metodo);

    cout << "\nNeurologia\n";
    mostrarOperacionAVL(avl_Neurologia, metodo);

    cout << "\nCardiologia\n";
    mostrarOperacionAVL(avl_Cardiologia, metodo);

    cout << "\nHospitalizacion\n";
    mostrarOperacionAVL(avl_Hospitalizacion, metodo);

    cout << "\nCirugia\n";
    mostrarOperacionAVL(avl_Cirugia, metodo);
}

void buscarPacienteMenu() {
    cout << "=== BUSCAR PACIENTE ===\n\n";
    cout << "Indique el ID o Nombre del paciente: ";
    string criterioBuscado;
    cin >> ws;
    getline(cin, criterioBuscado);
    cout << "\nBuscando en AVL...\n\n";
    bool encontrado = false;

    if (avl_General.buscar(criterioBuscado)) encontrado = true;
    else if (avl_Cirugia.buscar(criterioBuscado)) encontrado = true;
    else if (avl_Traumatologia.buscar(criterioBuscado)) encontrado = true;
    else if (avl_Neurologia.buscar(criterioBuscado)) encontrado = true;
    else if (avl_Cardiologia.buscar(criterioBuscado)) encontrado = true;
    else if (avl_Urgencias.buscar(criterioBuscado)) encontrado = true;
    else if (avl_Hospitalizacion.buscar(criterioBuscado)) encontrado = true;
    else if (avl_Pediatria.buscar(criterioBuscado)) encontrado = true;

    if (!encontrado) cout << "Paciente no encontrado en el hospital.\n";
}

int main() {
    int opcion = 0;
    do {
        cout << "=== HOSPITAL MARMAJA ===\n";
        cout << "1. Atender pacientes\n";
        cout << "2. Ver departamentos\n";
        cout << "3. Buscar paciente\n";
        cout << "4. Salir\n\n";
        cout << "Seleccionar opcion: ";
        cin >> opcion;
        cout << "\n";

        switch (opcion) {
        case 1:
            procesarPacientes();
            break;
        case 2:
            verDepartamentos();
            break;
        case 3:
            buscarPacienteMenu();
            break;
        case 4:
            cout << "Hasta Luego :).\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
        cout << "\n";
    } while (opcion != 4);

    return 0;
}
