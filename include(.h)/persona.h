#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include <iostream>

class Persona {
protected:
    std::string nombre;
    std::string id_banner;
    std::string correo;

public:
    // Constructor
    Persona(std::string _nombre, std::string _id, std::string _correo) 
        : nombre(_nombre), id_banner(_id), correo(_correo) {}

    // Método virtual puro (hace que la clase sea abstracta)
    virtual void mostrarPerfil() = 0;

    // Getters necesarios para las búsquedas
    std::string getIdBanner() const { return id_banner; }
    std::string getNombre() const { return nombre; }

    virtual ~Persona() {} // Destructor virtual
};

#endif