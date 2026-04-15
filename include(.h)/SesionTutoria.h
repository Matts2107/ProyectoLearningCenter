#ifndef SESION_TUTORIA_H
#define SESION_TUTORIA_H

#include <string>
#include <memory>
#include "Tutor.h"      // Se creará después (ya creado)
#include "Estudiante.h" // Se creará después
#include "Materia.h"

class SesionTutoria {
private:
    // Usamos punteros inteligentes para referenciar a los involucrados
    std::shared_ptr<Persona> tutor_ptr;
    std::shared_ptr<Persona> estudiante_ptr;
    std::shared_ptr<Materia> materia_ptr;
    
    std::string fecha;
    double duracion_horas;
    bool esta_finalizada;

public:
    SesionTutoria(std::shared_ptr<Persona> _tutor, std::shared_ptr<Persona> _estudiante, 
                std::shared_ptr<Materia> _materia, std::string _fecha, double _duracion)
        : tutor_ptr(_tutor), estudiante_ptr(_estudiante), materia_ptr(_materia), 
        fecha(_fecha), duracion_horas(_duracion), esta_finalizada(false) {}

    void finalizarSesion() { esta_finalizada = true; }
    bool getEstado() const { return esta_finalizada; }
    double getDuracion() const { return duracion_horas; }
    
    void imprimirRecibo(); //*(read) Se implementará en el .cpp
    // --- GETTERS (Para el 'Read' del Estudiante) ---
// Necesitas saber quién es el estudiante para filtrar la lista
std::shared_ptr<Persona> getEstudiante() const { return estudiante_ptr; }
std::shared_ptr<Persona> getTutor() const { return tutor_ptr; }
std::shared_ptr<Materia> getMateria() const { return materia_ptr; }
std::string getFecha() const { return fecha; }

// --- SETTERS (Para el 'Update' del Estudiante) ---
// El estudiante debe poder cambiar la fecha/hora
void setFecha(std::string _nuevaFecha) { fecha = _nuevaFecha; }
};

#endif