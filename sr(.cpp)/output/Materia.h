#ifndef MATERIA_H
#define MATERIA_H

#include <iostream>
#include <string>

class Materia {
private:
    std::string nombreM;
    std::string codigoM; 
    int multiplicador;   

public:
    Materia(std::string n_, std::string cod_, int mult_) 
        : nombreM(n_), codigoM(cod_), multiplicador(mult_) {}
    
    void mostrarMateria() const {
        std::cout << "ID: " << codigoM 
                  << " | Nombre: " << nombreM 
                  << " | Multiplicador: " << multiplicador << "\n";
    }
    
    std::string getMateria() const { return nombreM; }
    std::string getCodigo() const { return codigoM; }
    int getMultiplicador() const { return multiplicador; } 

    void setMultiplicador(int nuevoMultiplicador) {
        multiplicador = nuevoMultiplicador;
    }
}; 

#endif 
