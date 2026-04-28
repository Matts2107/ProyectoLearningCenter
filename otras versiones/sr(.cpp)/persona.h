#ifndef PERSONA_H
#define PERSONA_H
#include <string>

class Persona {
protected:
    std::string nombre;
    std::string id_banner;
    std::string correo;

public:
    // Solo el prototipo, termina en ";"
    Persona(std::string _nombre, std::string _id, std::string _correo);
    
    virtual std::string getIdBanner() const;
    virtual std::string getNombre() const;
    // Dentro de class Persona { ... }
virtual void mostrarPerfil() = 0;
    virtual ~Persona(); // Sin las llaves {}
};
#endif