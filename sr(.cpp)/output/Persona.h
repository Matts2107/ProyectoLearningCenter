#ifndef MATERIA_H
#define MATERIA_H

#include <iostream>
#include <string>

class Persona {
protected:
    std::string nombre;
    std::string id_banner;
    std::string correo;

public:
    Persona(std::string _nombre, std::string _id, std::string _correo) 
        : nombre(_nombre), id_banner(_id), correo(_correo) {}

    // Método virtual puro (hace que la clase sea abstracta)
    virtual void mostrarPerfil() const = 0;

    std::string getIdBanner() const { return id_banner; }
    std::string getNombre() const { return nombre; }

    virtual ~Persona() {} 
};

#endif 