#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ==========================================
// CLASE Materia
// ==========================================
class Materia {
private:
    std::string nombreM;
    std::string codigoM; 
    int multiplicador;   

public:
    Materia(std::string n_, std::string cod_, int mult_) 
        : nombreM(n_), codigoM(cod_), multiplicador(mult_) {}
    
    void mostrarMateria() const {
        std::cout << "ID: " << codigoM 
                << " | Nombre: " << nombreM 
                << " | Multiplicador: " << multiplicador << "\n";
    }
    
    std::string getMateria() const { return nombreM; }
    std::string getCodigo() const { return codigoM; }
    int getMultiplicador() const { return multiplicador; } 

    void setMultiplicador(int nuevoMultiplicador) {
        multiplicador = nuevoMultiplicador;
    }
}; 
// ==========================================
// CLASE Persona (Abstracta)
// ==========================================
class Persona {
protected:
    std::string nombre;
    std::string id_banner;
    std::string correo;

public:
    Persona(std::string _nombre, std::string _id, std::string _correo) 
        : nombre(_nombre), id_banner(_id), correo(_correo) {}

    // Método virtual puro (hace que la clase sea abstracta)
    virtual void mostrarPerfil() const = 0;
    
    void cambiarCorreo(std::string nuevoCorreo) {
    	correo = nuevoCorreo;
	}

    std::string getIdBanner() const { return id_banner; }
    std::string getNombre() const { return nombre; }
    std::string getCorreo() const { return correo; }

    virtual ~Persona() {} 
};
// ==========================================
// CLASE TUTOR (Hereda Persona)
// ==========================================
class Tutor : public Persona {
private:
    double tarifa_hora;

public:
    Tutor(std::string _nom, std::string _id, std::string _cor, double _tarifa)
        : Persona(_nom, _id, _cor), tarifa_hora(_tarifa) {}

    // Polimorfismo: Implementamos el método abstracto
    void mostrarPerfil() const override {
        std::cout << "ID: " << id_banner 
                << " | Nombre: " << nombre 
                << " | Correo: " << correo 
                << " | Tarifa: $" << tarifa_hora << "/h\n";
    }
    double getTarifa() const { 
        return tarifa_hora; 
    }
    
    void setTarifa(double nuevaTarifa) { 
        tarifa_hora = nuevaTarifa; 
    }
};
// ==========================================
// CLASE SISTEMA (Gestor Central)
// ==========================================
class SistemaLearningCenter {
private:
    // Almacenamiento polimórfico de usuarios
    std::vector<std::shared_ptr<Persona>> usuarios; 
    std::vector<std::shared_ptr<Materia>> materias;
public:
    SistemaLearningCenter() {}

    // Carga inicial de tutores como pediste
    void inicializarDatosPrueba() {
        usuarios.push_back(std::make_shared<Tutor>("Marcelo Diaz", "00123", "marcelo@u.edu", 15.0));
        usuarios.push_back(std::make_shared<Tutor>("Ana Lopez", "00124", "ana@u.edu", 18.5));
        materias.push_back(std::make_shared<Materia>("Calculo Diferencial", "MATH101", 2));
        materias.push_back(std::make_shared<Materia>("Fisica", "PHYS101", 3));
        std::cout << "-> Datos de prueba cargados  exitosamente.\n";
    }

    // Método para el Administrador (Create Tutor)
    void registrarTutor(std::string _nombre, std::string _id, std::string _correo, double _tarifa) {
        usuarios.push_back(std::make_shared<Tutor>(_nombre, _id, _correo, _tarifa));
        std::cout << "\n Tutor '" << _nombre << "' registrado con exito.\n";
    }
    
    // Método para el Administrador (Create Materia)
    void registrarMateria(std::string _nombreM, std::string _codigoM, int _multiplicador) {
        materias.push_back(std::make_shared<Materia>(_nombreM, _codigoM, _multiplicador));
        std::cout << "\n Materia '" << _nombreM << "' registrada con exito.\n";
    }

    // Método para el Administrador (Read Materias)
    void listarMaterias() const {
        std::cout << "\n--- LISTA DE MATERIAS REGISTRADAS ---\n";
        if (materias.empty()) {
            std::cout << "No hay materias en el sistema.\n";
            return;
        }
        for (const auto& m : materias) {
            m->mostrarMateria();
        }
        std::cout << "------------------------------------\n";
    }

    // Método para el Administrador (Read Tutores)
    void listarTutores() const {
        std::cout << "\n--- LISTA DE TUTORES REGISTRADOS ---\n";
        if (usuarios.empty()) {
            std::cout << "No hay tutores en el sistema.\n";
            return;
        }
        for (const auto& u : usuarios) {
            u->mostrarPerfil(); // Llamada polimórfica
        }
        std::cout << "------------------------------------\n";
    }

    // ========================================================
    // NUEVOS MÉTODOS DELETE (Eliminación)
    // ========================================================

    void eliminarTutor(std::string idBorrar) {
        // Recorremos el vector "usuarios"
        for (auto it = usuarios.begin(); it != usuarios.end(); ) {
            
            if ((*it)->getIdBanner() == idBorrar) {
                // Al usar erase, C++ y shared_ptr liberan la memoria automáticamente
                it = usuarios.erase(it);
                std::cout << "\n[EXITO] El usuario con ID " << idBorrar << " ha sido eliminado.\n";
                return; // Salimos de la función al encontrarlo
            } else {
                ++it; // Avanzamos al siguiente elemento
            }
        }
        // Si el bucle termina y no retornó, no existía ese ID
        std::cout << "\n[ERROR] No se encontro ningun usuario con el ID " << idBorrar << ".\n";
    }

    void eliminarMateria(std::string codigoBorrar) {
        // Recorremos el vector "materias"
        for (auto it = materias.begin(); it != materias.end(); ) {
            
            if ((*it)->getCodigo() == codigoBorrar) {
                it = materias.erase(it);
                std::cout << "\n[EXITO] La materia con codigo " << codigoBorrar << " ha sido eliminada.\n";
                return;
            } else {
                ++it;
            }
        }
        std::cout << "\n[ERROR] No se encontro ninguna materia con el codigo " << codigoBorrar << ".\n";
    }
    // ========================================================
    // NUEVOS MÉTODOS UPDATE (Modificación con y sin casteo)
    // ========================================================

    void modificarTarifaTutor(std::string idBuscar, double nuevaTarifa) {
        for (auto& usuario : usuarios) {
            if (usuario->getIdBanner() == idBuscar) {
                // AQUÍ USAMOS EL CASTEO INTELIGENTE
                auto tutorPtr = std::dynamic_pointer_cast<Tutor>(usuario);
                
                if (tutorPtr != nullptr) {
                    tutorPtr->setTarifa(nuevaTarifa);
                    std::cout << "\n[EXITO] Tarifa actualizada a $" << nuevaTarifa << " por hora.\n";
                } else {
                    std::cout << "\n[ERROR] El usuario encontrado no es un Tutor.\n";
                }
                return;
            }
        }
        std::cout << "\n[ERROR] Usuario no encontrado.\n";
    }

    void modificarCorreoUsuario(std::string idBuscar, std::string nuevoCorreo) {
        for (auto& usuario : usuarios) {
            if (usuario->getIdBanner() == idBuscar) {
                // No necesita casteo, el método cambiarCorreo está en la clase base (Persona)
                usuario->cambiarCorreo(nuevoCorreo);
                std::cout << "\n[EXITO] Correo actualizado a " << nuevoCorreo << ".\n";
                return;
            }
        }
        std::cout << "\n[ERROR] Usuario no encontrado.\n";
    }

    void modificarMultiplicadorMateria(std::string codigoBuscar, int nuevoMultiplicador) {
        for (auto& m : materias) {
            if (m->getCodigo() == codigoBuscar) {
                m->setMultiplicador(nuevoMultiplicador);
                std::cout << "\n[EXITO] El multiplicador de la materia " << m->getMateria() 
                        << " se actualizo a " << nuevoMultiplicador << ".\n";
                return;
            }
        }
        std::cout << "\n[ERROR] Materia no encontrada.\n";
    }
    
    
};

// ==========================================
// DECLARACIÓN FUNCIÓN MENU ADMINISTRADOR
// ==========================================

void menuAdministrador(SistemaLearningCenter& sistema);
void menuEstudiante(SistemaLearningCenter& sistema);
// ==========================================
// FUNCION PRINCIPAL
// ==========================================
int main() {
    SistemaLearningCenter sistema;
    std::cout << "Iniciando Sistema Learning Center...\n";
    sistema.inicializarDatosPrueba();
    
    int opcionPrincipal;
    
    // 2. Menú Principal
    do {
        std::cout << "\n============================================\n";
        std::cout << "       SISTEMA INTEGRADO LEARNING CENTER      \n";
        std::cout << "============================================\n";
        std::cout << "1. Modulo de Estudiante\n";
        std::cout << "2. Modulo de Tutor\n";
        std::cout << "3. Modulo Administrador\n";
        std::cout << "0. Salir del Sistema\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcionPrincipal;
        
        if (opcionPrincipal == 1) {
            std::cout << "\n[Entrando al Modulo de Estudiante... (Proximamente)]\n";
            
            menuEstudiante(sistema);
        } 
        else if (opcionPrincipal == 2) {
            std::cout << "\n[Entrando al Modulo de Tutor... (Proximamente)]\n";
            // Cuando lo programes, llamarás a algo como: menuTutor(sistema);
        } 
        else if (opcionPrincipal == 3) {
        	
            menuAdministrador(sistema); 
        } 
        else if (opcionPrincipal != 0) {
            std::cout << "\nOpcion no valida. Intente nuevamente.\n";
        }
        
    } while (opcionPrincipal != 0);
    
    std::cout << "\nSaliendo del sistema. ¡Hasta pronto!\n";
    return 0;
}



void menuAdministrador(SistemaLearningCenter& sistema) {
    int opcion;
    do {
        std::cout << "\n=== PANEL DE ADMINISTRADOR ===\n";
        std::cout << "1. Ver tutores registrados\n";
        std::cout << "2. Anadir nuevo tutor\n";
        std::cout << "3. Ver materias registradas\n";
        std::cout << "4. Anadir nueva materia\n";
        std::cout << "5. Eliminar tutor\n";
        std::cout << "6. Eliminar materia\n";
        std::cout << "7. Modificar tarifa de un Tutor\n";       
        std::cout << "8. Modificar correo de un Usuario\n";     
        std::cout << "9. Modificar multiplicador de Materia\n"; 
        std::cout << "10. Regresar al Menu Principal\n"; // Cambié el texto para que tenga sentido
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        
        if (opcion == 1) {
            sistema.listarTutores();
        } 
        else if (opcion == 2) {
            std::string nombre, id, correo;
            double tarifa;
            std::cout << "\nIngrese ID Banner: "; std::cin >> id;
            std::cin.ignore(); 
            std::cout << "Ingrese Nombre completo: "; std::getline(std::cin, nombre);
            std::cout << "Ingrese Correo: "; std::cin >> correo;
            std::cout << "Ingrese Tarifa por hora: "; std::cin >> tarifa;
            sistema.registrarTutor(nombre, id, correo, tarifa);
        }
        else if (opcion == 3) {
            sistema.listarMaterias();
        }
        else if (opcion == 4) {
            std::string nombreM, codigoM;
            int multiplicador;
            std::cout << "\nIngrese Codigo de materia: "; std::cin >> codigoM;
            std::cin.ignore(); 
            std::cout << "Ingrese Nombre de materia: "; std::getline(std::cin, nombreM);
            std::cout << "Ingrese Multiplicador: "; std::cin >> multiplicador;
            sistema.registrarMateria(nombreM, codigoM, multiplicador);
        }
        else if (opcion == 5) {
            std::string idBorrar;
            std::cout << "\nIngrese ID Banner del tutor a eliminar: "; std::cin >> idBorrar;
            sistema.eliminarTutor(idBorrar); 
        }
        else if (opcion == 6) {
            std::string codigoBorrar;
            std::cout << "\nIngrese Codigo de la materia a eliminar: "; std::cin >> codigoBorrar;
            sistema.eliminarMateria(codigoBorrar); 
        }
        else if (opcion == 7) {
            std::string idBuscar;
            double nuevaTarifa;
            std::cout << "\nIngrese el ID Banner del tutor: "; std::cin >> idBuscar;
            std::cout << "Ingrese la nueva tarifa: "; std::cin >> nuevaTarifa;
            sistema.modificarTarifaTutor(idBuscar, nuevaTarifa);
        }
        else if (opcion == 8) {
            std::string idBuscar, nuevoCorreo;
            std::cout << "\nIngrese el ID Banner del usuario: "; std::cin >> idBuscar;
            std::cout << "Ingrese el nuevo correo: "; std::cin >> nuevoCorreo;
            sistema.modificarCorreoUsuario(idBuscar, nuevoCorreo);
        }
        else if (opcion == 9) {
            std::string codigoBuscar;
            int nuevoMultiplicador;
            std::cout << "\nIngrese el Codigo de la materia: "; std::cin >> codigoBuscar;
            std::cout << "Ingrese el nuevo multiplicador: "; std::cin >> nuevoMultiplicador;
            sistema.modificarMultiplicadorMateria(codigoBuscar, nuevoMultiplicador);
        }
        else if (opcion != 10) {
            std::cout << "\nOpcion no valida. Intente nuevamente.\n";
        }
    } while (opcion != 10);
}


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