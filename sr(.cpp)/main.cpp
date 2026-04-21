#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "SistemaLearningCenter.h"
#include "Estudiante.h"
#include "Tutor.h"

using namespace std;

// --- PROTOTIPOS DE FUNCIONES ---
// Declaramos las funciones aquí para que el main sepa que existen.
void menuModulo1(SistemaLearningCenter& sistema);
void menuModulo2(SistemaLearningCenter& sistema); 
void menuModulo3(SistemaLearningCenter& sistema); 

int main() {
    // Instancia única del sistema. Todos los módulos trabajarán sobre esta misma variable.
    SistemaLearningCenter sistema;
    int opcionModulo;

    do {
        cout << "\n============================================" << endl;
        cout << "       SISTEMA INTEGRADO LEARNING CENTER" << endl;
        cout << "============================================" << endl;
        cout << "1. MODULO 1: Gestion de Reservas (Estudiante)" << endl;
        cout << "2. MODULO 2: Administracion (Proximamente)" << endl;
        cout << "3. MODULO 3: Reportes (Proximamente)" << endl;
        cout << "0. Salir del Sistema" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Seleccione un modulo para ingresar: ";
        
        // Validación para evitar que letras rompan el menú
        if (!(cin >> opcionModulo)) {
            cout << "\n[!] Error: Ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(); // Limpiar el buffer para los getlines siguientes

        switch (opcionModulo) {
            case 1:
                menuModulo1(sistema); 
                break;
            case 2:
                cout << "\n[!] Modulo en desarrollo por compañero A." << endl;
                break;
            case 3:
                cout << "\n[!] Modulo en desarrollo por compañero B." << endl;
                break;
            case 0:
                cout << "Cerrando sistema... ¡Exitos en la Politecnica!" << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcionModulo != 0);

    return 0;
}

// ==========================================================
//           IMPLEMENTACIÓN DEL MÓDULO 1 (ESTUDIANTE)
// ==========================================================
void menuEstudiante(SistemaLearningCenter& sistema) {
    int opcion;
    std::string nom, id, cor, carr, idTut, idMat, fecha;
    int sem, idSesion;

    do {
        std::cout << "\n--- BIENVENIDO AL MODULO DE RESERVAS ---" << std::endl;
        std::cout << "1. Registrarse como Estudiante" << std::endl;
        std::cout << "2. Ver Catalogo de Materias" << std::endl;
        std::cout << "3. Agendar Tutoria (Create)" << std::endl;
        std::cout << "4. Ver Mis Tutorias (Read)" << std::endl;
        std::cout << "5. Modificar Fecha/Hora (Update)" << std::endl;
        std::cout << "6. Cancelar Tutoria (Delete)" << std::endl;
        std::cout << "7. Registrar Nueva Materia (Admin Temporal)" << std::endl;
        std::cout << "0. Volver al Menu Principal" << std::endl;
        std::cout << "Seleccione: ";
        
        if (!(std::cin >> opcion)) {
            std::cin.clear(); std::cin.ignore(1000, '\n'); continue;
        }
        std::cin.ignore();

        switch (opcion) {
            case 1: // Registrarse
                std::cout << "Nombre: "; std::getline(std::cin, nom);
                std::cout << "ID Banner: "; std::getline(std::cin, id);
                std::cout << "Correo: "; std::getline(std::cin, cor);
                std::cout << "Carrera: "; std::getline(std::cin, carr);
                std::cout << "Semestre: "; 
                while(!(std::cin >> sem)){ std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Dato invalido. Semestre: "; }
                
                // --- MÉTODOS COMENTADOS HASTA QUE LOS IMPLEMENTES ---
                // sistema.getUsuarios().push_back(std::make_shared<Estudiante>(nom, id, cor, carr, sem));
                
                std::cout << "[OK] (SIMULADO) Estudiante registrado exitosamente." << std::endl;
                break;

            case 2: // Catálogo
                // --- MÉTODOS COMENTADOS HASTA QUE LOS IMPLEMENTES ---
                // sistema.buscarMateriaPorId(""); // Esto es para refrescar si fuera necesario
                std::cout << "\n--- CATALOGO ACTUAL DE MATERIAS ---" << std::endl;
                // for(auto& m : sistema.getMaterias()) m->mostrarDatos();
                
                std::cout << "(Mostrando catalogo simulado...)" << std::endl;
                break;

            case 3: // Create
                std::cout << "Tu ID Estudiante: "; std::getline(std::cin, id);
                std::cout << "ID Tutor (Prueba: T100): "; std::getline(std::cin, idTut);
                std::cout << "Codigo Materia (Prueba: MAT101): "; std::getline(std::cin, idMat);
                std::cout << "Fecha y Hora: "; std::getline(std::cin, fecha);
                
                // --- MÉTODOS COMENTADOS HASTA QUE LOS IMPLEMENTES ---
                // sistema.agendarTutoria(id, idTut, idMat, fecha);
                
                std::cout << "[OK] (SIMULADO) Tutoria agendada exitosamente." << std::endl;
                break;

            case 4: // Read
                std::cout << "Ingrese su ID para ver sus citas: "; std::getline(std::cin, id);
                
                // --- MÉTODOS COMENTADOS HASTA QUE LOS IMPLEMENTES ---
                // sistema.verMisTutorias(id);
                
                std::cout << "(Mostrando tutorias simuladas...)" << std::endl;
                break;

            case 5: // Update
                std::cout << "Numero de cita a modificar: "; std::cin >> idSesion; std::cin.ignore();
                std::cout << "Nueva Fecha/Hora: "; std::getline(std::cin, fecha);
                
                // --- MÉTODOS COMENTADOS HASTA QUE LOS IMPLEMENTES ---
                // sistema.modificarFechaTutoria(idSesion, fecha);
                
                std::cout << "[OK] (SIMULADO) Fecha de la tutoria actualizada." << std::endl;
                break;

            case 6: // Delete
                std::cout << "Numero de cita a cancelar: "; std::cin >> idSesion;
                
                // --- MÉTODOS COMENTADOS HASTA QUE LOS IMPLEMENTES ---
                // sistema.cancelarTutoria(idSesion);
                
                std::cout << "[OK] (SIMULADO) Tutoria cancelada." << std::endl;
                break;

            case 7: // Auxiliar para añadir materias rápido
                std::cout << "Nombre Materia: "; std::getline(std::cin, nom);
                std::cout << "Codigo (ID): "; std::getline(std::cin, id);
                
                // --- MÉTODOS COMENTADOS HASTA QUE LOS IMPLEMENTES ---
                // sistema.getMaterias().push_back(std::make_shared<Materia>(nom, id, 1.0));
                
                std::cout << "[OK] (SIMULADO) Materia agregada al catalogo." << std::endl;
                break;
        }
        
        if(opcion != 0) {
            std::cout << "\nPresione Enter para continuar...";
            std::cin.ignore(); // Pausa estética de ENTER
        }

    } while (opcion != 0);
}