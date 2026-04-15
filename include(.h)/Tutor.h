#ifndef TUTOR_H
#define TUTOR_H

#include "Persona.h"
#include "Empleado.h"
#include "Materia.h"
#include <vector>
#include <memory>

// Herencia Múltiple: Tutor es una Persona y también es un Empleado
class Tutor : public Persona, public Empleado {
private:
    double horasAcumuladasMes;
    std::vector<std::shared_ptr<Materia>> materiasHabilitadas;

public:
    Tutor(std::string _nom, std::string _id, std::string _cor, double _tarifa);

    // Polimorfismo: Sobrescribimos los métodos de las clases padre
    void mostrarPerfil() override;
    double calcularPago(double horas) override; // Aquí va la lógica de las 10 horas

    // Métodos específicos del Tutor
    void agregarMateria(std::shared_ptr<Materia> m);
    void registrarHoras(double h);
    double getHorasAcumuladas() const { return horasAcumuladasMes; }
};

#endif