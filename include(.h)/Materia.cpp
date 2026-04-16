#include "Materia.h"
#include <iostream>
#include <iomanip>

using namespace std;

Materia::Materia(string _nombre, string _codigo, double _mult)
    : nombre_materia(_nombre), codigo_materia(_codigo), multiplicador(_mult) {}

void Materia::mostrarDatos() const {
    cout << "  > [" << codigo_materia << "] " 
        << left << setw(20) << nombre_materia 
        << " | Mult: " << multiplicador << endl;
}