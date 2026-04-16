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
void menuModulo1(SistemaLearningCenter& sistema) {
    int opcion;
    string nom, id, cor, carr, idTut, idMat, fecha;
    int sem, idSesion;

    do {
        cout << "\n--- BIENVENIDO AL MODULO DE RESERVAS ---" << endl;
        cout << "1. Registrarse como Estudiante" << endl;
        cout << "2. Ver Catalogo de Materias" << endl;
        cout << "3. Agendar Tutoria (Create)" << endl;
        cout << "4. Ver Mis Tutorias (Read)" << endl;
        cout << "5. Modificar Fecha/Hora (Update)" << endl;
        cout << "6. Cancelar Tutoria (Delete)" << endl;
        cout << "7. Registrar Nueva Materia (Admin Temporal)" << endl;
        cout << "0. Volver al Menu Principal" << endl;
        cout << "Seleccione: ";
        
        if (!(cin >> opcion)) {
            cin.clear(); cin.ignore(1000, '\n'); continue;
        }
        cin.ignore();

        switch (opcion) {
            case 1: // Registrarse
                cout << "Nombre: "; getline(cin, nom);
                cout << "ID Banner: "; getline(cin, id);
                cout << "Correo: "; getline(cin, cor);
                cout << "Carrera: "; getline(cin, carr);
                cout << "Semestre: "; 
                while(!(cin >> sem)){ cin.clear(); cin.ignore(1000, '\n'); cout << "Dato invalido. Semestre: "; }
                
                sistema.getUsuarios().push_back(make_shared<Estudiante>(nom, id, cor, carr, sem));
                cout << "[OK] Estudiante registrado exitosamente." << endl;
                break;

            case 2: // Catálogo
                sistema.buscarMateriaPorId(""); // Esto es para refrescar si fuera necesario
                cout << "\n--- CATALOGO ACTUAL DE MATERIAS ---" << endl;
                for(auto& m : sistema.getMaterias()) m->mostrarDatos();
                break;

            case 3: // Create
                cout << "Tu ID Estudiante: "; getline(cin, id);
                cout << "ID Tutor (Prueba: T100): "; getline(cin, idTut);
                cout << "Codigo Materia (Prueba: MAT101): "; getline(cin, idMat);
                cout << "Fecha y Hora: "; getline(cin, fecha);
                sistema.agendarTutoria(id, idTut, idMat, fecha);
                break;

            case 4: // Read
                cout << "Ingrese su ID para ver sus citas: "; getline(cin, id);
                sistema.verMisTutorias(id);
                break;

            case 5: // Update
                cout << "Numero de cita a modificar: "; cin >> idSesion; cin.ignore();
                cout << "Nueva Fecha/Hora: "; getline(cin, fecha);
                sistema.modificarFechaTutoria(idSesion, fecha);
                break;

            case 6: // Delete
                cout << "Numero de cita a cancelar: "; cin >> idSesion;
                sistema.cancelarTutoria(idSesion);
                break;

            case 7: // Auxiliar para añadir materias rápido
                cout << "Nombre Materia: "; getline(cin, nom);
                cout << "Codigo (ID): "; getline(cin, id);
                sistema.getMaterias().push_back(make_shared<Materia>(nom, id, 1.0));
                cout << "[OK] Materia agregada." << endl;
                break;
        }
        
        if(opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(); // Pausa estética de ENTER
        }

    } while (opcion != 0);
}