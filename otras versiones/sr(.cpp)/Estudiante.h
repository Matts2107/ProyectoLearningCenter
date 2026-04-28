#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "Persona.h"
#include <string>

// Herencia Simple: Estudiante hereda únicamente de Persona
class Estudiante : public Persona {
private:
    std::string carrera;
    int semestre;

public:
    Estudiante(std::string _nom, std::string _id, std::string _cor, std::string _car, int _sem);

    // Polimorfismo: Implementamos el método que era virtual puro en Persona
    void mostrarPerfil() override;

    // Getters específicos
    std::string getCarrera() const { return carrera; }
    int getSemestre() const { return semestre; }
};

#endif