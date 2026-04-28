#ifndef MATERIA_H
#define MATERIA_H
#include <string>
#include <iostream>

class Materia {
private:
    std::string nombre;
    std::string codigo;
    double multiplicador;

public:
    // Solo prototipos
    Materia(std::string _nombre, std::string _codigo, double _mult);
    
    std::string getNombre() const;
    std::string getCodigo() const; // Asegúrate de que se llame getId si así lo usas en el sistema
    void mostrarDatos() const;
    
    virtual ~Materia();
};
#endif