#ifndef MATERIA_H
#define MATERIA_H

#include <string>
#include <iostream>

class Materia {
private:
    std::string nombre_materia;
    std::string codigo_materia;
    double multiplicador;

public:
    Materia(std::string _nombre, std::string _codigo, double _mult)
        : nombre_materia(_nombre), codigo_materia(_codigo), multiplicador(_mult) {}

    // Getters
    std::string getNombre() const { return nombre_materia; }
    std::string getCodigo() const { return codigo_materia; }
    double getMultiplicador() const { return multiplicador; }

    // El método que te faltaba
    void mostrarDatos() const {
        std::cout << "Codigo: " << codigo_materia 
                << " | Materia: " << nombre_materia 
                << " (Mult: " << multiplicador << ")" << std::endl;
    }
};

#endif