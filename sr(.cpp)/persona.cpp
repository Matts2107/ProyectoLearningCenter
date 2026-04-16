#include "persona.h"
#include <iostream>
#include <string>

using namespace std;

// Implementación del constructor
// Nota: No implementamos mostrarPerfil() aquí porque es virtual pura (=0)
Persona::Persona(string _nombre, string _id, string _correo) 
    : nombre(_nombre), id_banner(_id), correo(_correo) {}

// Implementación de los getters
string Persona::getIdBanner() const { 
    return id_banner; 
}

string Persona::getNombre() const { 
    return nombre; 
}

// El destructor virtual puede quedarse vacío pero debe estar definido
Persona::~Persona() {}