#ifndef SISTEMALEARNINGCENTER_H
#define SISTEMALEARNINGCENTER_H

#include <vector>
#include <string>
#include <memory>

// Incluimos las clases que el sistema va a gestionar
#include "Persona.h"
#include "Materia.h"
#include "SesionTutoria.h"

class SistemaLearningCenter {
private:
    // Contenedores principales (Base de datos en memoria)
    std::vector<std::shared_ptr<Persona>> usuarios;
    std::vector<std::shared_ptr<Materia>> materias;
    std::vector<std::shared_ptr<SesionTutoria>> historialSesiones;

    // Métodos privados auxiliares
    void inicializarDatosPrueba();

public:
    // Constructor y Destructor
    SistemaLearningCenter();
    ~SistemaLearningCenter();

    // --- GETTERS POR REFERENCIA ---
    // Permiten al main.cpp usar push_back directamente en los vectores
    std::vector<std::shared_ptr<Persona>>& getUsuarios();
    std::vector<std::shared_ptr<Materia>>& getMaterias();
    std::vector<std::shared_ptr<SesionTutoria>>& getHistorialSesiones();

    // --- MÓDULO 1: MÉTODOS DE GESTIÓN (CRUD) ---
    
    // Create: Agendar
    void agendarTutoria(std::string idEstudiante, std::string idTutor, std::string idMateria, std::string fechaHora);
    
    // Read: Visualización
    void verMisTutorias(std::string idEstudiante);
    void mostrarCatalogoMaterias();
    
    // Update: Modificación
    bool modificarFechaTutoria(int idSesion, std::string nuevaFechaHora);
    
    // Delete: Cancelación
    bool cancelarTutoria(int idSesion);

    // --- MÉTODOS DE BÚSQUEDA ---
    std::shared_ptr<Persona> buscarUsuarioPorId(std::string id);
    std::shared_ptr<Materia> buscarMateriaPorId(std::string id);
};

#endif