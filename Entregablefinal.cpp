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

    // Metodo virtual puro (hace que la clase sea abstracta)
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
// CLASE Empleado (Base laboral para Tutor)
// ==========================================
class Empleado {
protected:
    double tarifaBase;

public:
    Empleado(double _tarifa) : tarifaBase(_tarifa) {}
    void setTarifa(double t) { tarifaBase = t; }
    double getTarifa() const { return tarifaBase; }
    
    // Metodo virtual para el polimorfismo de pago
    virtual double calcularPago(double horas) const {
        return tarifaBase * horas;
    }
    virtual ~Empleado() {}
};

// ==========================================
// CLASE TUTOR (Herencia Multiple: Persona + Empleado)
// ==========================================
class Tutor : public Persona, public Empleado {
private:
    std::vector<std::shared_ptr<Materia>> materiasHabilitadas;
    double horasAcumuladasMes;

public:
    Tutor(std::string _nom, std::string _id, std::string _cor, double _tarifa)
        : Persona(_nom, _id, _cor), Empleado(_tarifa), horasAcumuladasMes(0.0) {}

    // Polimorfismo: Implementamos el metodo abstracto de Persona
    void mostrarPerfil() const override {
        std::cout << "ID: " << id_banner 
                << " | Nombre: " << nombre 
                << " | Correo: " << correo 
                << " | Tarifa: $" << tarifaBase << "/h | Horas mes: " << horasAcumuladasMes << "\n";
        std::cout << "  Materias habilitadas: ";
        if (materiasHabilitadas.empty()) std::cout << "Ninguna";
        for (const auto& m : materiasHabilitadas) std::cout << "[" << m->getMateria() << "] ";
        std::cout << "\n";
    }

    // Polimorfismo: Sobrescribimos el calculo de pago (Regla del Learning Center)
    double calcularPago(double horas) const override {
        if (horas < 10.0) {
            std::cout << " -> [Alerta] El tutor " << nombre << " tiene menos de 10h. Su pago sera retenido.\n";
            return 0.0;
        }
        return tarifaBase * horas;
    }

    // Logica de negocio para limitar a 60 horas
    bool registrarHoras(double horas) {
        if (horasAcumuladasMes + horas > 60.0) {
            std::cout << "\n[ALERTA] No se pueden registrar " << horas << "h. Superaria el limite de 60h mensuales.\n";
            return false;
        }
        horasAcumuladasMes += horas;
        return true;
    }
    
    void agregarMateria(std::shared_ptr<Materia> m) {
        materiasHabilitadas.push_back(m);
    }
    
    double getHorasAcumuladas() const { return horasAcumuladasMes; }
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

    // Implementacion del Polimorfismo
    void mostrarPerfil() const override {
        std::cout << "\n--- PERFIL DEL ESTUDIANTE ---\n";
        std::cout << "Nombre:    " << nombre << std::endl; 
        std::cout << "ID Banner: " << id_banner << std::endl;
        std::cout << "Carrera:   " << carrera << std::endl;
        std::cout << "Semestre:  " << semestre << "to" << std::endl;
        std::cout << "Correo:    " << correo << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
    
    // Getters por si necesitas acceder a estos datos mas adelante
    std::string getCarrera() const { return carrera; }
    int getSemestre() const { return semestre; }
};

// ==========================================
// CLASE Sesion Tutoria
// ==========================================
class SesionTutoria {
private:
    std::shared_ptr<Estudiante> estudiante;
    std::shared_ptr<Tutor> tutor;
    std::shared_ptr<Materia> materia;
    std::string fechaHora;
    double duracionHoras;
    bool fueCompletada;

public:
    // Ahora el constructor pide la duracion de la sesion
    SesionTutoria(std::shared_ptr<Estudiante> e, std::shared_ptr<Tutor> t, std::shared_ptr<Materia> m, std::string fecha, double duracion)
        : estudiante(e), tutor(t), materia(m), fechaHora(fecha), duracionHoras(duracion), fueCompletada(false) {}

    void setFecha(std::string nuevaFecha) { fechaHora = nuevaFecha; }
    std::shared_ptr<Estudiante> getEstudiante() const { return estudiante; }
    std::shared_ptr<Materia> getMateria() const { return materia; }
    double getDuracion() const { return duracionHoras; }
    std::shared_ptr<Tutor> getTutor() const { return tutor; }
    
    void actualizarEstado(bool completada, double nuevaDuracion) {
        fueCompletada = completada;
        duracionHoras = nuevaDuracion;
    }

    void imprimirDetalles() const {
        std::cout << " >> [" << fechaHora << "] " << materia->getMateria() 
                << " | Tutor: " << tutor->getNombre() << " | Alumno: " << estudiante->getNombre() 
                << " | Duracion: " << duracionHoras << "h | Estado: " << (fueCompletada ? "Completada" : "Pendiente") << std::endl;
    }
};
// ==========================================
// CLASE SISTEMA (Gestor Central)
// ==========================================
class SistemaLearningCenter {
private:
    // Almacenamiento polimorfico de usuarios
    std::vector<std::shared_ptr<Persona>> usuarios;
    std::vector<std::shared_ptr<Materia>> materias;
    std::vector<std::unique_ptr<SesionTutoria>> sesiones; 

public:
    SistemaLearningCenter() {}

    // Metodos auxiliares de busqueda - NUEVOS
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
        // 1. Cargamos los usuarios base
        usuarios.push_back(std::make_shared<Tutor>("Marcelo Diaz", "00123", "marcelo@u.edu", 15.0));
        usuarios.push_back(std::make_shared<Tutor>("Ana Lopez", "00124", "ana@u.edu", 18.5));
        usuarios.push_back(std::make_shared<Estudiante>("Maria Lopez", "00332572", "maria@estudiante.edu", "Medicina", 5));
        usuarios.push_back(std::make_shared<Estudiante>("Carlos Ruiz", "00998877", "carlos@estudiante.edu", "Arquitectura", 2));
        
        // 2. Cargamos las materias
        materias.push_back(std::make_shared<Materia>("Calculo Diferencial", "MATH", 2));
        materias.push_back(std::make_shared<Materia>("Fisica", "PHYS101", 3));
        
        // 3. AGREGAMOS SESIONES PARA MARCELO DIAZ (ID: 00123)
        // AgendarTutoria pide: (ID_Estudiante, ID_Tutor, Cod_Materia, Fecha, Duracion)
        
        std::cout << "\n--- Cargando sesiones de prueba ---" << std::endl;
        
        // Sesion 1: Marcelo da Calculo a Maria (2 horas)
        agendarTutoria("00332572", "00123", "MATH", "2024-05-10 09:00", 2.0);
        
        // Sesion 2: Marcelo da Fisica a Carlos (1.5 horas)
        agendarTutoria("00998877", "00123", "PHYS101", "2024-05-12 15:00", 1.5);
        
        // Sesion 3: Marcelo da Calculo a Carlos (1 hora)
        agendarTutoria("00998877", "00123", "MATH", "2024-05-15 11:00", 1.0);

        std::cout << "-> Datos de prueba y sesiones cargados exitosamente.\n";
    }

    // Metodo para el Administrador (Create Tutor)
    void registrarTutor(std::string _nombre, std::string _id, std::string _correo, double _tarifa) {
        usuarios.push_back(std::make_shared<Tutor>(_nombre, _id, _correo, _tarifa));
        std::cout << "\n Tutor '" << _nombre << "' registrado con exito.\n";
    }
    
    // Metodo para el Administrador (Create Materia)
    void registrarMateria(std::string _nombreM, std::string _codigoM, int _multiplicador) {
        materias.push_back(std::make_shared<Materia>(_nombreM, _codigoM, _multiplicador));
        std::cout << "\n Materia '" << _nombreM << "' registrada con exito.\n";
    }

    // Metodo para el Administrador (Read Materias)
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

    // Metodo para el Administrador (Read Tutores)
    void listarTutores() const {
        std::cout << "\n--- LISTA DE TUTORES REGISTRADOS ---\n";
        
        bool hayTutores = false; // Bandera para saber si encontramos al menos uno
        
        for (const auto& u : usuarios) {
            // Intentamos convertir (castear) la Persona a un Tutor
            auto tutorPtr = std::dynamic_pointer_cast<Tutor>(u);
            
            // Si el resultado NO es nullptr, significa que si era un Tutor
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
    // MeTODOS DELETE (Eliminacion)
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
    // METODOS UPDATE (Modificacio con y sin casteo)
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
    // METODOS PARA SESIONES 
    // ========================================================

    void agendarTutoria(std::string idEst, std::string idTut, std::string idMat, std::string fecha, double duracion) {
        auto pEst = buscarUsuarioPorId(idEst);
        auto pTut = buscarUsuarioPorId(idTut);
        auto mat = buscarMateriaPorId(idMat);

        auto est = std::dynamic_pointer_cast<Estudiante>(pEst);
        auto tut = std::dynamic_pointer_cast<Tutor>(pTut);

        if (est && tut && mat) {
            // Verificamos que el tutor no se pase de las 60 horas mensuales
            if (tut->registrarHoras(duracion)) {
                // Usamos make_unique en lugar de make_shared
                sesiones.push_back(std::make_unique<SesionTutoria>(est, tut, mat, fecha, duracion));
                std::cout << "\n[EXITO] Tutoria agendada correctamente.\n";
            }
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
        auto it = std::remove_if(sesiones.begin(), sesiones.end(), [&](const std::unique_ptr<SesionTutoria>& s) {
            return s->getEstudiante()->getIdBanner() == idEst && s->getMateria()->getCodigo() == codMat;
        });
        
        if (it != sesiones.end()) {
            sesiones.erase(it, sesiones.end());
            std::cout << "\n[EXITO] Tutoria cancelada y eliminada del sistema.\n";
        } else {
            std::cout << "\n[ERROR] No se encontro la tutoria especificada.\n";
        }
    }

    void verHistorialSesiones() const {
        std::cout << "\n--- HISTORIAL GLOBAL DE SESIONES ---\n";
        if (sesiones.empty()) std::cout << "No hay sesiones registradas.\n";
        for (const auto& s : sesiones) {
            s->imprimirDetalles();
        }
    }

    void procesarNominaMensual() {
        std::cout << "\n========== REPORTE DE NOMINA MENSUAL ==========\n";
        for (auto& u : usuarios) {
            // Intentamos convertir el usuario a Tutor usando dynamic_pointer_cast
            auto tut = std::dynamic_pointer_cast<Tutor>(u);
            if (tut) {
                double horas = tut->getHorasAcumuladas();
                double pago = tut->calcularPago(horas); 
                
                std::cout << "Tutor: " << tut->getNombre() 
                        << " | Horas: " << horas 
                        << " | Pago Total: $" << pago << "\n";
            }
        }
        std::cout << "===============================================\n";
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
 // ========================================================
    // METODOS PARA EL MODULO TUTOR
    // ========================================================

    void tutorAgregarMateria(std::string idTut, std::string codMat) {
        auto tut = std::dynamic_pointer_cast<Tutor>(buscarUsuarioPorId(idTut));
        auto mat = buscarMateriaPorId(codMat);
        if (tut && mat) {
            tut->agregarMateria(mat);
            std::cout << "[EXITO] Ahora estas habilitado para dar " << mat->getMateria() << ".\n";
        } else {
            std::cout << "[ERROR] Materia o Tutor no encontrados.\n";
        }
    }

    void verTutoriasDeTutor(std::string idTut) const {
        std::cout << "\n--- MIS TUTORIAS ASIGNADAS ---\n";
        bool encontro = false;
        // Usamos const auto& para observar los unique_ptr de forma segura
        for (const auto& s : sesiones) {
            if (s->getTutor()->getIdBanner() == idTut) {
                s->imprimirDetalles();
                encontro = true;
            }
        }
        if (!encontro) std::cout << "No tienes tutorias agendadas actualmente.\n";
    }

    void completarSesionTutor(std::string idTut, std::string idEst, std::string codMat, double duracionReal) {
        for (auto& s : sesiones) {
            if (s->getTutor()->getIdBanner() == idTut && 
                s->getEstudiante()->getIdBanner() == idEst && 
                s->getMateria()->getCodigo() == codMat) {
                
                // Actualizamos el estado a Completada (true) y ajustamos la duraci�n
                s->actualizarEstado(true, duracionReal);
                std::cout << "\n[EXITO] Sesion marcada como completada con " << duracionReal << " horas.\n";
                return;
            }
        }
        std::cout << "\n[ERROR] No se encontro la tutoria especificada.\n";
    }
};
// ==========================================
// DECLARACION FUNCIoN MENU ADMINISTRADOR
// ==========================================

void menuAdministrador(SistemaLearningCenter& sistema);
void menuEstudiante(SistemaLearningCenter& sistema);
void menuTutor(SistemaLearningCenter& sistema);

// ==========================================
// FUNCION PRINCIPAL
// ==========================================
int main() {
    SistemaLearningCenter sistema;
    std::cout << "Iniciando Sistema Learning Center...\n";
    sistema.inicializarDatosPrueba();
    
    int opcionPrincipal;
    
    // 2. Menu Principal
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


            menuEstudiante(sistema);
        } 
        else if (opcionPrincipal == 2) {
            std::cout << "\n[Entrando al Modulo de Tutor...]\n";
			
			menuTutor(sistema);
        } 
        else if (opcionPrincipal == 3) {
        	
            menuAdministrador(sistema); 
        } 
        else if (opcionPrincipal != 0) {
            std::cout << "\nOpcion no valida. Intente nuevamente.\n";
        }
        
    } while (opcionPrincipal != 0);
    
    std::cout << "\nSaliendo del sistema. Hasta pronto!\n";
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
            int g;
            std::cout << "Tu ID Estudiante: ";
            std::cin >> e;
            std::cout << "ID Tutor: ";
            std::cin >> t;
            std::cout << "Cod Materia: ";
            std::cin >> m;
            std::cout << "Fecha: ";
            std::cin >> f;
            std::cout<< "duracion: ";
            std::cin>>g;
            sistema.agendarTutoria(e, t, m, f, g);
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

        else{
            std:: cout << ">> [ERROR] Opcion no valida. Ingrese un numero entre 1 y 6.\n";
        }

        

    } while (opt != 6); 
}

void menuTutor(SistemaLearningCenter& sistema) {
    std::string miId;
    std::cout << "\n=== INGRESO AL PORTAL DE TUTORES ===\n";
    std::cout << "Ingrese su ID Banner para continuar: ";
    std::cin >> miId;

    // Validamos que el usuario exista y sea de tipo Tutor
    auto usuario = sistema.buscarUsuarioPorId(miId);
    auto tutor = std::dynamic_pointer_cast<Tutor>(usuario);

    if (!tutor) {
        std::cout << "[ERROR] Acceso denegado. ID incorrecto o no pertenece a un Tutor.\n";
        return;
    }

    int opcion;
    do {
        std::cout << "\n========== PANEL DEL TUTOR: " << tutor->getNombre() << " ==========\n";
        std::cout << "1. Ver mi perfil y horas acumuladas en el mes\n";
        std::cout << "2. Agregar nueva materia a mi catalogo de ensenanza\n";
        std::cout << "3. Ver mi lista de tutorias agendadas\n";
        std::cout << "4. Marcar tutoria como Completada y registrar duracion\n";
        std::cout << "0. Cerrar Sesion (Regresar al Menu Principal)\n";
        std::cout << "========================================================\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::cout << "\n--- MI PERFIL PROFESIONAL ---\n";
            tutor->mostrarPerfil();
        } 
        else if (opcion == 2) {
            std::string codMat;
            std::cout << "\n--- AGREGAR MATERIA ---\n";
            std::cout << "Ingrese el codigo de la Materia que desea ensenar: ";
            std::cin >> codMat;
            sistema.tutorAgregarMateria(miId, codMat);
        } 
        else if (opcion == 3) {
            sistema.verTutoriasDeTutor(miId);
        } 
        else if (opcion == 4) {
            std::string idEst, codMat;
            double duracionReal;
            std::cout << "\n--- REGISTRAR CUMPLIMIENTO DE TUTORIA ---\n";
            std::cout << "ID del Estudiante que asistio: ";
            std::cin >> idEst;
            std::cout << "Codigo de la materia dada: ";
            std::cin >> codMat;
            std::cout << "Duracion real impartida (ej. 1.5): ";
            std::cin >> duracionReal;
            
            sistema.completarSesionTutor(miId, idEst, codMat, duracionReal);
        }
        else{
            std:: cout << ">> [ERROR] Opcion no valida. Ingrese un numero entre 1 y 4.\n";
        }
    } while (opcion != 0);
}