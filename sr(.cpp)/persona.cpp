#include "Persona.h"

// Constructor: Asigna los valores iniciales
Persona::Persona(std::string _nombre, std::string _id, std::string _correo) 
    : nombre(_nombre), id_banner(_id), correo(_correo) {}

// Retorna el ID (Banner)
std::string Persona::getIdBanner() const {
    return id_banner;
}

// Retorna el nombre completo
std::string Persona::getNombre() const {
    return nombre;
}

// Destructor virtual: Necesario para que las clases hijas se borren bien
Persona::~Persona() {}