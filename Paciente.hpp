#pragma once
#include <string> 

using namespace std;

class Paciente {
private:
    string ID;
    string Nombre;
    int Edad;
    string Servicio;
    int PresionArterial;
    bool trauma;
    bool requiereCirugía;
    bool sintomasNeurologicos;
    string TipoDolor;
    float Temperatura;
    int Dolor;
    int DiasHospitalizacion;
public:
    Paciente() {
        this->ID = "";
        this->Nombre = "";
        this->Edad = 0;
        this->Servicio = "Invalido";
        this->PresionArterial = 0;
        this->trauma = false;
        this->sintomasNeurologicos = false;
        this->TipoDolor = "";
        this->Temperatura = 0.0;
        this->Dolor = 0;
        this->DiasHospitalizacion = 0;
    }

    Paciente(string ID, string Nombre, int Edad, string Servicio) {
        this->ID = ID;
        this->Nombre = Nombre;
        this->Edad = Edad;
        this->Servicio = Servicio;
    }

    Paciente(string ID, string Nombre, int Edad, float temperatura, int Presion, int dolor, string tipoDolor, bool trauma, bool neurologico, bool Cirugia, int hospitalizacion) {
        this->ID = ID;
        this->Nombre = Nombre;
        this->Edad = Edad;
        this->PresionArterial = Presion;
        this->trauma = trauma;
        this->sintomasNeurologicos = neurologico;
        this->TipoDolor = tipoDolor;
        this->requiereCirugía = Cirugia;
        this->Temperatura = temperatura;
        this->Dolor = dolor;
        this->DiasHospitalizacion = hospitalizacion;
    }

	string getID() {
		return this->ID;
	}

	string getNombre() {
		return this->Nombre;
	}

	int getEdad() {
		return this->Edad;
	}

    string getServicio() {
        return this->Servicio;
    }

    bool getTrauma() {
        return this->trauma;
    }

    bool getrequiereCirugía() {
        return this->requiereCirugía;
    }

    bool getsintomasNeurologicos() {
        return this->sintomasNeurologicos;
    }

    string getTipoDolor() {
        return this->TipoDolor;
    }

    float getTemperatura() {
        return this->Temperatura;
    }

    int getDolor() {
        return this->Dolor;
    }

    int getDiasHospitalizacion() {
        return this->DiasHospitalizacion;
    }

    void setServicio(string Servi) {
        if (Servi == "Cardiologia" || Servi == "Urgencias" || Servi == "Cirugia" || Servi == "Pediatria" || Servi == "Traumatologia" || Servi == "Neurologia" || Servi == "Medicina General" || Servi == "Hospitalizacion") {
            this->Servicio = Servi;
        }
        else {
            this->Servicio = "Invalido";
        }
    }

    string ValidarDatos(Paciente p) {
        string resultado;
        if (p.getEdad() > 14) {
            resultado = "Edad > 14 -> ";
        }
        else {
            resultado = "Edad <= 14 -> ";
        }
        if (p.getTrauma() == true) {
            resultado += "Trauma == 1 -> \n";
        }
        else {
            resultado += "Trauma == 0 -> \n";
        }
        if (p.getsintomasNeurologicos() == true) {
            resultado += "Sintomas Neurologicos == 1 -> ";
        }
        else {
            resultado += "Sintomas Neurologicos == 0 -> ";
        }
        if (p.getTipoDolor() == "pecho") {
            resultado += "TipoDolor == pecho -> \n";
        }
        else {
            resultado += "TipoDolor != pecho -> \n";
        }
        if (p.getTemperatura() >= 38.5 && p.getDolor() >= 8) {
            resultado += "Temperatura >= 38.5 y Dolor >= 8 -> ";
        }
        else {
            resultado += "Temperatura < 38.5 y Dolor < 8 -> ";
        }

        if (p.getDiasHospitalizacion() >= 2) {
            resultado += "DiasHospitalizacion >= 2 ";
        }
        else {
            resultado += "DiasHospitalizacion < 2 ";
        }
        return resultado;
    }

    ~Paciente() {}
};
