#include "SistemaLearningCenter.h"
#include "Estudiante.h"
#include "Tutor.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Constructor
SistemaLearningCenter::SistemaLearningCenter() {
    inicializarDatosPrueba();
}

// Destructor (Añadido para completar el ciclo de vida de la clase)
SistemaLearningCenter::~SistemaLearningCenter() {}

void SistemaLearningCenter::inicializarDatosPrueba() {
    materias.push_back(make_shared<Materia>("Calculo Diferencial", "MAT101", 1.5));
    materias.push_back(make_shared<Materia>("Programacion C++", "PROG102", 1.2));

    auto tut1 = make_shared<Tutor>("Juan Perez", "T100", "juan.perez@u.edu", 12.0);
    usuarios.push_back(tut1);

    auto est1 = make_shared<Estudiante>("Estudiante Base", "E001", "base@u.edu", "Sistemas", 3);
    usuarios.push_back(est1);

    cout << ">>> [SISTEMA] Datos de prueba cargados exitosamente." << endl;
}

// --- GETTERS (Añadidos para que el main pueda registrar usuarios/materias directamente) ---
vector<shared_ptr<Persona>>& SistemaLearningCenter::getUsuarios() {
    return usuarios;
}

vector<shared_ptr<Materia>>& SistemaLearningCenter::getMaterias() {
    return materias;
}

// --- MÓDULO 1: GESTIÓN DE RESERVAS ---

void SistemaLearningCenter::agendarTutoria(string idEstudiante, string idTutor, string idMateria, string fechaHora) {
    auto est = dynamic_pointer_cast<Estudiante>(buscarUsuarioPorId(idEstudiante));
    auto tut = dynamic_pointer_cast<Tutor>(buscarUsuarioPorId(idTutor));
    auto mat = buscarMateriaPorId(idMateria);

    if (est && tut && mat) {
        auto nuevaSesion = make_shared<SesionTutoria>(tut, est, mat, fechaHora, 1.0);
        historialSesiones.push_back(nuevaSesion);
        
        cout << "\n[OK] Tutoria agendada exitosamente." << endl;
        cout << "Estudiante: " << est->getNombre() << " | Tutor: " << tut->getNombre() << endl;
    } else {
        cout << "\n[ERROR] Verifique que los IDs existan y que los roles sean correctos." << endl;
    }
}

void SistemaLearningCenter::verMisTutorias(string idEstudiante) {
    cout << "\n--- LISTADO DE TUTORIAS (ID: " << idEstudiante << ") ---" << endl;
    bool tieneCitas = false;
    int contador = 1;

    for (auto& sesion : historialSesiones) {
        // Verificamos si la sesión pertenece al estudiante
        if (sesion->getEstudiante() && sesion->getEstudiante()->getIdBanner() == idEstudiante) {
            cout << "No. de Cita: " << contador << endl;
            sesion->imprimirRecibo();
            cout << "-----------------------" << endl;
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
    if (materias.empty()) {
        cout << "[!] No hay materias registradas." << endl;
    } else {
        for (const auto& m : materias) {
            m->mostrarDatos();
            cout << "-----------------------" << endl;
        }
    }
}

bool SistemaLearningCenter::modificarFechaTutoria(int idSesion, string nuevaFechaHora) {
    if (idSesion > 0 && idSesion <= (int)historialSesiones.size()) {
        historialSesiones[idSesion - 1]->setFecha(nuevaFechaHora);
        cout << "\n[OK] Fecha actualizada correctamente." << endl;
        return true;
    }
    cout << "\n[ERROR] Numero de cita no encontrado." << endl;
    return false;
}

bool SistemaLearningCenter::cancelarTutoria(int idSesion) {
    if (idSesion > 0 && idSesion <= (int)historialSesiones.size()) {
        historialSesiones.erase(historialSesiones.begin() + (idSesion - 1));
        cout << "\n[OK] La tutoria ha sido eliminada." << endl;
        return true;
    }
    cout << "\n[ERROR] No se pudo cancelar." << endl;
    return false;
}

// --- BÚSQUEDA ---

shared_ptr<Persona> SistemaLearningCenter::buscarUsuarioPorId(string id) {
    for (auto& u : usuarios) {
        if (u->getIdBanner() == id) return u;
    }
    return nullptr;
}

shared_ptr<Materia> SistemaLearningCenter::buscarMateriaPorId(string id) {
    for (auto& m : materias) {
        // Cambié getCodigo() por getId() para que coincida con tu clase Materia
        if (m->getCodigo() == id) return m; 
    }
    return nullptr;
}