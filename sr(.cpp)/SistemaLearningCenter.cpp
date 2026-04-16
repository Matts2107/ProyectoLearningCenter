#include "SistemaLearningCenter.h"
#include "Estudiante.h"
#include "Tutor.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Constructor: Inicializa el contador y precarga datos mínimos
SistemaLearningCenter::SistemaLearningCenter() : proximoIdSesion(1) {
    inicializarDatosPrueba();
}

void SistemaLearningCenter::inicializarDatosPrueba() {
    // 1. Materias de ejemplo (Precarga para Marcelo)
    materias.push_back(make_shared<Materia>("Calculo Diferencial", "MAT101", 1.5));
    materias.push_back(make_shared<Materia>("Programacion C++", "PROG102", 1.2));

    // 2. Un Tutor por defecto para poder agendar
    auto tut1 = make_shared<Tutor>("Juan Perez", "T100", "juan.perez@u.edu", 12.0);
    usuarios.push_back(tut1);

    // 3. Un Estudiante por defecto para pruebas rapidas
    auto est1 = make_shared<Estudiante>("Estudiante Base", "E001", "base@u.edu", "Sistemas", 3);
    usuarios.push_back(est1);

    cout << ">>> [SISTEMA] Datos de prueba cargados exitosamente." << endl;
}

// --- MÓDULO 1: GESTIÓN DE RESERVAS (ESTUDIANTE) ---

// CREATE: Agenda una nueva tutoría
void SistemaLearningCenter::agendarTutoria(string idEstudiante, string idTutor, string idMateria, string fechaHora) {
    auto est = buscarUsuarioPorId(idEstudiante);
    auto tut = buscarUsuarioPorId(idTutor);
    auto mat = buscarMateriaPorId(idMateria);

    if (est && tut && mat) {
        // Creamos la sesión. Duración estándar de 1 hora.
        auto nuevaSesion = make_shared<SesionTutoria>(tut, est, mat, fechaHora, 1.0);
        
        historialSesiones.push_back(nuevaSesion);
        
        cout << "\n[OK] Tutoria agendada para el estudiante " << est->getNombre() << endl;
        cout << "Con el tutor " << tut->getNombre() << " en la materia " << mat->getNombre() << endl;
    } else {
        cout << "\n[ERROR] Datos invalidos. Verifique que los IDs de Estudiante, Tutor y Materia existan." << endl;
    }
}

// READ: Ver mis tutorías
void SistemaLearningCenter::verMisTutorias(string idEstudiante) {
    cout << "\n--- LISTADO DE TUTORIAS (ID: " << idEstudiante << ") ---" << endl;
    bool tieneCitas = false;
    int contador = 1;

    for (auto& sesion : historialSesiones) {
        if (sesion->getEstudiante()->getIdBanner() == idEstudiante) {
            cout << "No. de Cita: " << contador;
            sesion->imprimirRecibo();
            tieneCitas = true;
        }
        contador++;
    }

    if (!tieneCitas) {
        cout << "No tienes tutorias agendadas actualmente." << endl;
    }
}
void SistemaLearningCenter::mostrarCatalogoMaterias() {
    cout << "\n--- CATALOGO DE MATERIAS DISPONIBLES ---" << endl;
    
    // Verificamos si el vector de materias está vacío
    if (materias.empty()) {
        cout << "[!] No hay materias registradas en el sistema." << endl;
    } else {
        // Recorremos el vector de punteros compartidos
        for (const auto& m : materias) {
            m->mostrarDatos(); // Llama al método de la clase Materia
            cout << "-----------------------" << endl;
        }
    }
}

// UPDATE: Cambiar fecha/hora
bool SistemaLearningCenter::modificarFechaTutoria(int idSesion, string nuevaFechaHora) {
    // Usamos el índice del vector (empezando en 1 para el usuario)
    if (idSesion > 0 && idSesion <= (int)historialSesiones.size()) {
        historialSesiones[idSesion - 1]->setFecha(nuevaFechaHora);
        cout << "\n[OK] La fecha/hora de la sesion " << idSesion << " ha sido actualizada." << endl;
        return true;
    }
    cout << "\n[ERROR] ID de sesion no encontrado." << endl;
    return false;
}

// DELETE: Cancelar tutoría
bool SistemaLearningCenter::cancelarTutoria(int idSesion) {
    if (idSesion > 0 && idSesion <= (int)historialSesiones.size()) {
        historialSesiones.erase(historialSesiones.begin() + (idSesion - 1));
        cout << "\n[OK] La tutoria ha sido cancelada satisfactoriamente." << endl;
        return true;
    }
    cout << "\n[ERROR] No se pudo cancelar. Verifique el numero de sesion." << endl;
    return false;
}

// --- MÉTODOS DE BÚSQUEDA ---

shared_ptr<Persona> SistemaLearningCenter::buscarUsuarioPorId(string id) {
    for (auto& u : usuarios) {
        if (u->getIdBanner() == id) return u;
    }
    return nullptr;
}

shared_ptr<Materia> SistemaLearningCenter::buscarMateriaPorId(string id) {
    for (auto& m : materias) {
        if (m->getCodigo() == id) return m;
    }
    return nullptr;
}