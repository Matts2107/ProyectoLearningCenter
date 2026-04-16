#include "Tutor.h"
#include <iostream>

using namespace std;

// Constructor: Pasa datos a Persona y Empleado, e inicializa horas en 0
Tutor::Tutor(string _nom, string _id, string _cor, double _tarifa)
    : Persona(_id, _nom, _cor), Empleado(_tarifa), horasAcumuladasMes(0.0) {}

// Implementación de mostrarPerfil (Polimorfismo)
void Tutor::mostrarPerfil() {
    cout << "\n--- PERFIL DEL TUTOR ---" << endl;
    cout << "Nombre: " << getNombre() << endl;
    cout << "ID Banner: " << getIdBanner() << endl;
    cout << "Horas del mes: " << horasAcumuladasMes << " h" << endl;
    cout << "Materias que dicta: " << endl;
    
    if (materiasHabilitadas.empty()) {
        cout << "  (Aun no tiene materias asignadas)" << endl;
    } else {
        for (auto& m : materiasHabilitadas) {
            cout << "  - " << m->getNombre() << endl;
        }
    }
}

// Lógica de pago (Polimorfismo)
double Tutor::calcularPago(double horas) {
    // Aquí puedes aplicar la lógica de las 10 horas si es necesario
    return horas * tarifaBasePorHora; 
}

// Métodos específicos
void Tutor::agregarMateria(shared_ptr<Materia> m) {
    materiasHabilitadas.push_back(m);
}

void Tutor::registrarHoras(double h) {
    horasAcumuladasMes += h;
}