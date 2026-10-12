#pragma once
#include <string> 

using namespace std;

class Nodo;
class Paciente;

class Departamento {
private:
	string Tipo;
	Paciente* Personas;

public:
	Departamento() {
		this->Tipo = "";
		this->Personas = nullptr;
	}

	Departamento(string tipo, Paciente* personas) {
		this->Tipo = tipo;
		this->Personas = personas;
	}

	Departamento(string tipo) {
		this->Tipo = tipo;
		this->Personas = nullptr;
	}

	string getTipo() {
		return this->Tipo;
	}

	Paciente* getPersonas() {
		return this->Personas;
	}

	void setTipo(string Tipo) {
		this->Tipo = Tipo;
	}

	void setPersonas(Paciente* p) {
		this->Personas = p;
	}

	~Departamento() {}
};