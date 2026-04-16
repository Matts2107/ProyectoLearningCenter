#include <iostream>
#include <string>
#include <memory>
#include "SistemaLearningCenter.h"
#include "Estudiante.h"
#include "Tutor.h"

using namespace std;

// --- PROTOTIPOS DE FUNCIONES ---
// Esto permite que el main sea limpio y las funciones estén abajo
void menuModulo1(SistemaLearningCenter& sistema);
void menuModulo2(SistemaLearningCenter& sistema); // Espacio para tu compañero
void menuModulo3(SistemaLearningCenter& sistema); // Espacio para tu compañero

int main() {
    // El objeto 'sistema' es el CORAZÓN del programa. 
    // Se crea una sola vez para que todos los módulos compartan los mismos datos.
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
        
        if (!(cin >> opcionModulo)) {
            cout << "Entrada no valida. Intente de nuevo." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (opcionModulo) {
            case 1:
                menuModulo1(sistema); // Llamamos a tu parte
                break;
            case 2:
                cout << "\n[!] Este modulo aun esta en desarrollo por tu compañero." << endl;
                break;
            case 3:
                cout << "\n[!] Este modulo aun esta en desarrollo por tu compañero." << endl;
                break;
            case 0:
                cout << "Cerrando sistema integral..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcionModulo != 0);

    return 0;
}

// ==========================================================
//           IMPLEMENTACIÓN DEL MÓDULO 1 (TU PARTE)
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
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Nombre: "; getline(cin, nom);
                cout << "ID Banner: "; getline(cin, id);
                cout << "Correo: "; getline(cin, cor);
                cout << "Carrera: "; getline(cin, carr);
                cout << "Semestre: "; cin >> sem;
                sistema.getUsuarios().push_back(make_shared<Estudiante>(nom, id, cor, carr, sem));
                cout << "[OK] Registrado exitosamente." << endl;
                break;
            case 2:
                cout << "\n--- CATALOGO ACTUAL ---" << endl;
                for(auto& m : sistema.getMaterias()) m->mostrarDatos();
                break;
            case 3:
                cout << "ID Estudiante: "; getline(cin, id);
                cout << "ID Tutor (Prueba: T100): "; getline(cin, idTut);
                cout << "ID Materia (Prueba: MAT101): "; getline(cin, idMat);
                cout << "Fecha: "; getline(cin, fecha);
                sistema.agendarTutoria(id, idTut, idMat, fecha);
                break;
            case 4:
                cout << "ID Estudiante: "; getline(cin, id);
                sistema.verMisTutorias(id);
                break;
            case 5:
                cout << "Numero de sesion: "; cin >> idSesion; cin.ignore();
                cout << "Nueva Fecha: "; getline(cin, fecha);
                sistema.modificarFechaTutoria(idSesion, fecha);
                break;
            case 6:
                cout << "Numero de sesion a cancelar: "; cin >> idSesion;
                sistema.cancelarTutoria(idSesion);
                break;
            case 7:
                cout << "Nombre Materia: "; getline(cin, nom);
                cout << "Codigo: "; getline(cin, id);
                sistema.getMaterias().push_back(make_shared<Materia>(nom, id, 1.0));
                break;
        }
    } while (opcion != 0);
}