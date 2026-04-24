#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

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
// CLASE Empleado (Base laboral para Tutor) - NUEVA
// ==========================================
class Empleado {
protected:
    double tarifaBase;

public:
    Empleado(double _tarifa) : tarifaBase(_tarifa) {}
    void setTarifa(double t) { tarifaBase = t; }
    double getTarifa() const { return tarifaBase; }
    virtual ~Empleado() {}
};

// ==========================================
// CLASE TUTOR (Herencia Múltiple: Persona + Empleado)
// ==========================================
class Tutor : public Persona, public Empleado {
public:
    Tutor(std::string _nom, std::string _id, std::string _cor, double _tarifa)
        : Persona(_nom, _id, _cor), Empleado(_tarifa) {}

    // Polimorfismo: Implementamos el método abstracto
    void mostrarPerfil() const override {
        std::cout << "ID: " << id_banner 
                  << " | Nombre: " << nombre 
                  << " | Correo: " << correo 
                  << " | Tarifa: $" << tarifaBase << "/h\n";
    }
};

// ==========================================
// CLASE ESTUDIANTE (Hereda de Persona)
// ==========================================
class Estudiante : public Persona {
private:
    std::string carrera;
    int semestre;

public:
    // Constructor: Pasa el nombre, ID y correo a la clase base Persona
    Estudiante(std::string _nom, std::string _id, std::string _cor, std::string _car, int _sem)
        : Persona(_nom, _id, _cor), carrera(_car), semestre(_sem) {}

    // Implementación del Polimorfismo
    void mostrarPerfil() const override {
        std::cout << "\n--- PERFIL DEL ESTUDIANTE ---\n";
        std::cout << "Nombre:    " << nombre << std::endl; 
        std::cout << "ID Banner: " << id_banner << std::endl;
        std::cout << "Carrera:   " << carrera << std::endl;
        std::cout << "Semestre:  " << semestre << "to" << std::endl;
        std::cout << "Correo:    " << correo << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
    
    // Getters por si necesitas acceder a estos datos más adelante
    std::string getCarrera() const { return carrera; }
    int getSemestre() const { return semestre; }
};

// ==========================================
// CLASE Sesión Tutoría - NUEVA
// ==========================================
class SesionTutoria {
private:
    std::shared_ptr<Estudiante> estudiante;
    std::shared_ptr<Tutor> tutor;
    std::shared_ptr<Materia> materia;
    std::string fechaHora;

public:
    SesionTutoria(std::shared_ptr<Estudiante> e, std::shared_ptr<Tutor> t, std::shared_ptr<Materia> m, std::string fecha)
        : estudiante(e), tutor(t), materia(m), fechaHora(fecha) {}

    void setFecha(std::string nuevaFecha) { fechaHora = nuevaFecha; }
    std::shared_ptr<Estudiante> getEstudiante() const { return estudiante; }
    std::shared_ptr<Materia> getMateria() const { return materia; }

    void imprimirDetalles() const {
        std::cout << " >> [" << fechaHora << "] " << materia->getMateria() 
                  << " | Tutor: " << tutor->getNombre() << " | Alumno: " << estudiante->getNombre() << std::endl;
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
    std::vector<std::shared_ptr<SesionTutoria>> sesiones; // NUEVO

public:
    SistemaLearningCenter() {}

    // Métodos auxiliares de búsqueda - NUEVOS
    std::shared_ptr<Persona> buscarUsuarioPorId(std::string id) {
        for (auto& u : usuarios) if (u->getIdBanner() == id) return u;
        return nullptr;
    }

    std::shared_ptr<Materia> buscarMateriaPorId(std::string id) {
        for (auto& m : materias) if (m->getCodigo() == id) return m;
        return nullptr;
    }

    // Carga inicial de tutores como pediste
    void inicializarDatosPrueba() {
        usuarios.push_back(std::make_shared<Tutor>("Marcelo Diaz", "00123", "marcelo@u.edu", 15.0));
        usuarios.push_back(std::make_shared<Tutor>("Ana Lopez", "00124", "ana@u.edu", 18.5));
        usuarios.push_back(std::make_shared<Estudiante>("Maria Lopez", "00332572", "maria@estudiante.edu", "Medicina", 5));
        usuarios.push_back(std::make_shared<Estudiante>("Carlos Ruiz", "00998877", "carlos@estudiante.edu", "Arquitectura", 2));
        materias.push_back(std::make_shared<Materia>("Calculo Diferencial", "MATH", 2));
        materias.push_back(std::make_shared<Materia>("Fisica", "PHYS101", 3));
        
        std::cout << "-> Datos de prueba cargados exitosamente.\n";
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
        
        bool hayTutores = false; // Bandera para saber si encontramos al menos uno
        
        for (const auto& u : usuarios) {
            // Intentamos convertir (castear) la Persona a un Tutor
            auto tutorPtr = std::dynamic_pointer_cast<Tutor>(u);
            
            // Si el resultado NO es nullptr, significa que sí era un Tutor
            if (tutorPtr != nullptr) {
                tutorPtr->mostrarPerfil(); 
                hayTutores = true;
            }
        }

        if (!hayTutores) {
            std::cout << "No hay tutores registrados en el sistema.\n";
        }
        std::cout << "------------------------------------\n";
    }

    // ========================================================
    // MÉTODOS DELETE (Eliminación)
    // ========================================================

    void eliminarTutor(std::string idBorrar) {
        for (auto it = usuarios.begin(); it != usuarios.end(); ) {
            if ((*it)->getIdBanner() == idBorrar) {
                it = usuarios.erase(it);
                std::cout << "\n[EXITO] El usuario con ID " << idBorrar << " ha sido eliminado.\n";
                return;
            } else {
                ++it;
            }
        }
        std::cout << "\n[ERROR] No se encontro ningun usuario con el ID " << idBorrar << ".\n";
    }

    void eliminarMateria(std::string codigoBorrar) {
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
    // MÉTODOS UPDATE (Modificación con y sin casteo)
    // ========================================================

    void modificarTarifaTutor(std::string idBuscar, double nuevaTarifa) {
        for (auto& usuario : usuarios) {
            if (usuario->getIdBanner() == idBuscar) {
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

    // ========================================================
    // NUEVOS MÉTODOS PARA SESIONES (Módulo Estudiante)
    // ========================================================

    void agendarTutoria(std::string idEst, std::string idTut, std::string idMat, std::string fecha) {
        auto pEst = buscarUsuarioPorId(idEst);
        auto pTut = buscarUsuarioPorId(idTut);
        auto mat = buscarMateriaPorId(idMat);

        auto est = std::dynamic_pointer_cast<Estudiante>(pEst);
        auto tut = std::dynamic_pointer_cast<Tutor>(pTut);

        if (est && tut && mat) {
            sesiones.push_back(std::make_shared<SesionTutoria>(est, tut, mat, fecha));
            std::cout << "\n[EXITO] Tutoria agendada correctamente.\n";
        } else {
            std::cout << "\n[ERROR] Verifique los IDs y tipos de usuario.\n";
        }
    }

    void modificarFechaSesion(std::string idEst, std::string codMat, std::string nuevaFecha) {
        for (auto& s : sesiones) {
            if (s->getEstudiante()->getIdBanner() == idEst && s->getMateria()->getCodigo() == codMat) {
                s->setFecha(nuevaFecha);
                std::cout << "\n[EXITO] Fecha de tutoria actualizada.\n";
                return;
            }
        }
        std::cout << "\n[ERROR] No se encontro ninguna tutoria para ese Estudiante y Materia.\n";
    }

    void cancelarSesion(std::string idEst, std::string codMat) {
        auto it = std::remove_if(sesiones.begin(), sesiones.end(), [&](std::shared_ptr<SesionTutoria> s) {
            return s->getEstudiante()->getIdBanner() == idEst && s->getMateria()->getCodigo() == codMat;
        });
        if (it != sesiones.end()) {
            sesiones.erase(it, sesiones.end());
            std::cout << "\n[EXITO] Tutoria cancelada y eliminada del sistema.\n";
        } else {
            std::cout << "\n[ERROR] No se encontro la tutoria especificada.\n";
        }
    }

    void listarHistorial() const {
        std::cout << "\n--- HISTORIAL DE SESIONES ---\n";
        if (sesiones.empty()) {
            std::cout << "No hay sesiones registradas.\n";
        }
        for (const auto& s : sesiones) {
            s->imprimirDetalles();
        }
    }
    
    void verTutoriasDeEstudiante(std::string idEst) {
    auto usuario = buscarUsuarioPorId(idEst);
    auto est = std::dynamic_pointer_cast<Estudiante>(usuario);
    
    if (!est) {
        std::cout << "\n[ERROR] No se encontro un estudiante con el ID " << idEst << ".\n";
        return;
    }
    
    std::cout << "\n--- TUTORIAS DE " << est->getNombre() << " ---\n";
    bool encontro = false;
    for (const auto& s : sesiones) {
        if (s->getEstudiante()->getIdBanner() == idEst) {
            s->imprimirDetalles();
            encontro = true;
        }
    }
    if (!encontro) {
        std::cout << "No tiene tutorias agendadas.\n";
    }
	}
    
    void listarEstudiantes() const {
    std::cout << "\n--- ESTUDIANTES REGISTRADOS ---\n";
    bool hayEstudiantes = false;
    for (const auto& u : usuarios) {
        auto est = std::dynamic_pointer_cast<Estudiante>(u);
        if (est) {
            est->mostrarPerfil();
            hayEstudiantes = true;
        }
    }
    if (!hayEstudiantes) {
        std::cout << "No hay estudiantes registrados.\n";
    }
    std::cout << "--------------------------------\n";
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
        std::cout << "2. Modulo de Tutor(Proximamente)\n";
        std::cout << "3. Modulo Administrador\n";
        std::cout << "0. Salir del Sistema\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcionPrincipal;
        
        if (opcionPrincipal == 1) {


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
        std::cout << "10. Ver estudiantes registrados\n";
        std::cout << "11. Regresar al Menu Principal\n"; 
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
        else if (opcion == 10) {
            sistema.listarEstudiantes();
        }
        else if (opcion != 11) {
            std::cout << "\nOpcion no valida. Intente nuevamente.\n";
        }
    } while (opcion != 11);
}


void menuEstudiante(SistemaLearningCenter& sistema) {
    int opt;
    do {
        std::cout << "\n--- MODULO ESTUDIANTE ---\n";
        std::cout << "1. Ver Materias\n";
        std::cout << "2. Agendar Tutoria\n";
        std::cout << "3. Modificar Fecha de Tutoria\n";
        std::cout << "4. Cancelar Tutoria\n";
        std::cout << "5. Ver mis Sesiones\n";
        std::cout << "6. Regresar al Menu Principal\n";
        std::cout << "Opcion: ";
        std::cin >> opt;

        if (opt == 1) {
            std::cout << "\n--- MATERIAS DISPONIBLES ---\n";
            sistema.listarMaterias();
        }
        else if (opt == 2) {
            std::string e, t, m, f;
            std::cout << "Tu ID Estudiante: ";
            std::cin >> e;
            std::cout << "ID Tutor: ";
            std::cin >> t;
            std::cout << "Cod Materia: ";
            std::cin >> m;
            std::cout << "Fecha: ";
            std::cin >> f;
            sistema.agendarTutoria(e, t, m, f);
        }
        else if (opt == 3) {
            std::string e, m, f;
            std::cout << "Tu ID Estudiante: ";
            std::cin >> e;
            std::cout << "Cod Materia de la tutoria: ";
            std::cin >> m;
            std::cout << "Nueva Fecha/Hora: ";
            std::cin >> f;
            sistema.modificarFechaSesion(e, m, f);
        }
        else if (opt == 4) {
            std::string e, m;
            std::cout << "Tu ID Estudiante: ";
            std::cin >> e;
            std::cout << "Cod Materia a cancelar: ";
            std::cin >> m;
            sistema.cancelarSesion(e, m);
        }
        else if (opt == 5) {
	    std::string id;
	    std::cout << "Tu ID Estudiante: ";
	    std::cin >> id;
	    sistema.verTutoriasDeEstudiante(id);
		}

    } while (opt != 6);
}