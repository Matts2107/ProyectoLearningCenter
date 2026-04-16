#include "Estudiante.h"
#include <iostream>

using namespace std;

// Constructor: Pasa el nombre, ID y correo a la clase base Persona
Estudiante::Estudiante(string _nom, string _id, string _cor, string _car, int _sem)
    : Persona(_nom, _id, _cor), carrera(_car), semestre(_sem) {}

// Implementación del Polimorfismo
void Estudiante::mostrarPerfil() {
    cout << "\n--- PERFIL DEL ESTUDIANTE ---" << endl;
    cout << "Nombre:   " << nombre << endl; // nombre es protected en Persona, así que podemos usarlo
    cout << "ID Banner: " << id_banner << endl;
    cout << "Carrera:  " << carrera << endl;
    cout << "Semestre: " << semestre << "to" << endl;
    cout << "Correo:   " << correo << endl;
    cout << "-----------------------------" << endl;
}