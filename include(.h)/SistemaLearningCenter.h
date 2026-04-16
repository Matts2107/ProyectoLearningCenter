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
    std::vector<std::shared_ptr<Persona>> usuarios; // Incluye Estudiantes y Tutores
    std::vector<std::shared_ptr<Materia>> materias;
    std::vector<std::shared_ptr<SesionTutoria>> historialSesiones;

    // Contador para generar IDs automáticos de las sesiones
    int proximoIdSesion;

public:
    SistemaLearningCenter();

    // --- MÉTODOS PARA PREPARAR DATOS (Necesarios para que el estudiante tenga qué elegir) ---
    void inicializarDatosPrueba(); // Para crear tutores y materias manualmente temporalmente antes de implementar el csv, parte de marcelo
    
    // --- MÓDULO 1: GESTIÓN DE RESERVAS (ESTUDIANTE) ---
    
    // CREATE: Agenda una nueva tutoría
    void agendarTutoria(std::string idEstudiante, std::string idTutor, std::string idMateria, std::string fechaHora);

    // READ: El estudiante ve solo sus tutorías
    void verMisTutorias(std::string idEstudiante);

    // UPDATE: El estudiante cambia solo la fecha/hora de una cita existente
    bool modificarFechaTutoria(int idSesion, std::string nuevaFechaHora);

    // DELETE: El estudiante cancela una tutoría
    bool cancelarTutoria(int idSesion);

    // --- MÉTODOS DE BÚSQUEDA (Auxiliares para que el CRUD funcione) ---
    std::shared_ptr<Persona> buscarUsuarioPorId(std::string id);
    std::shared_ptr<Materia> buscarMateriaPorId(std::string id);
};

#endif