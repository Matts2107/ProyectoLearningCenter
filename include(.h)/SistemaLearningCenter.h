#ifndef SISTEMA_LEARNING_CENTER_H
#define SISTEMA_LEARNING_CENTER_H

#include <vector>
#include <memory>
#include <string>
#include "Persona.h"
#include "Materia.h"
#include "SesionTutoria.h"

class SistemaLearningCenter {
private:
    // COMPOSICIÓN: El sistema es dueño de estas colecciones
    std::vector<std::shared_ptr<Persona>> usuarios; 
    std::vector<std::shared_ptr<Materia>> materias;
    std::vector<std::shared_ptr<SesionTutoria>> historialSesiones;

    int proximoIdSesion;

public:
    SistemaLearningCenter();

    // --- GETTERS PARA EL MENÚ INTERACTIVO ---
    // Estas funciones devuelven una REFERENCIA (&) para que el main pueda hacer push_back
    std::vector<std::shared_ptr<Persona>>& getUsuarios() { return usuarios; }
    std::vector<std::shared_ptr<Materia>>& getMaterias() { return materias; }
    std::vector<std::shared_ptr<SesionTutoria>>& getHistorial() { return historialSesiones; }

    // --- MÉTODOS DE DATOS ---
    void inicializarDatosPrueba(); 
    
    // --- MÓDULO 1: GESTIÓN DE RESERVAS (ESTUDIANTE) ---
    void agendarTutoria(std::string idEstudiante, std::string idTutor, std::string idMateria, std::string fechaHora);
    void verMisTutorias(std::string idEstudiante);
    bool modificarFechaTutoria(int idSesion, std::string nuevaFechaHora);
    bool cancelarTutoria(int idSesion);

    // --- MÉTODOS DE BÚSQUEDA ---
    std::shared_ptr<Persona> buscarUsuarioPorId(std::string id);
    std::shared_ptr<Materia> buscarMateriaPorId(std::string id);
};

#endif