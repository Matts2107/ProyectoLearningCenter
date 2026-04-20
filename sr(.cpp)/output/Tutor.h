#ifndef MATERIA_H
#define MATERIA_H

#include <iostream>
#include <string>

class Tutor : public Persona {
private:
    double tarifa_hora;

public:
    Tutor(std::string _nom, std::string _id, std::string _cor, double _tarifa)
        : Persona(_nom, _id, _cor), tarifa_hora(_tarifa) {}

    // Polimorfismo: Implementamos el método abstracto
    void mostrarPerfil() const override {
        std::cout << "ID: " << id_banner 
                  << " | Nombre: " << nombre 
                  << " | Correo: " << correo 
                  << " | Tarifa: $" << tarifa_hora << "/h\n";
    }
};


#endif 