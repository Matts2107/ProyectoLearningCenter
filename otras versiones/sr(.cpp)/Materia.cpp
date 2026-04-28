#include "Materia.h"

// Constructor
Materia::Materia(std::string _nombre, std::string _codigo, double _mult) 
    : nombre(_nombre), codigo(_codigo), multiplicador(_mult) {}

// Retorna el nombre de la materia
std::string Materia::getNombre() const {
    return nombre;
}

// Retorna el código (ID) de la materia
std::string Materia::getCodigo() const {
    return codigo;
}

// Imprime los datos en pantalla
void Materia::mostrarDatos() const {
    std::cout << "Materia: " << nombre 
            << " | ID: " << codigo 
            << " | Dificultad/Mult: " << multiplicador << std::endl;
}

// Destructor
Materia::~Materia() {}