#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

// ==========================================
// CLASE Materia
// ==========================================
class Materia {
private:
    string nombreM;
    string codigoM; 
    int multiplicador;   

public:
    Materia(string n_, string cod_, int mult_) 
        : nombreM(n_), codigoM(cod_), multiplicador(mult_) {}
    
    void mostrarMateria() const {
        cout << "ID: " << codigoM 
             << " | Nombre: " << nombreM 
             << " | Multiplicador: " << multiplicador << "\n";
    }
    
    string getMateria() const { return nombreM; }
    string getCodigo() const { return codigoM; }
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
    string nombre;
    string id_banner;
    string correo;

public:
    Persona(string _nombre, string _id, string _correo) 
        : nombre(_nombre), id_banner(_id), correo(_correo) {}

    virtual void mostrarPerfil() const = 0;
    
    void cambiarCorreo(string nuevoCorreo) {
        correo = nuevoCorreo;
    }

    string getIdBanner() const { return id_banner; }
    string getNombre() const { return nombre; }
    string getCorreo() const { return correo; }

    virtual ~Persona() {} 
};

// ==========================================
// CLASE Empleado
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
// CLASE TUTOR
// ==========================================
class Tutor : public Persona, public Empleado {
public:
    Tutor(string _nom, string _id, string _cor, double _tarifa)
        : Persona(_nom, _id, _cor), Empleado(_tarifa) {}

    void mostrarPerfil() const override {
        cout << "ID: " << id_banner 
             << " | Nombre: " << nombre 
             << " | Correo: " << correo 
             << " | Tarifa: $" << tarifaBase << "/h\n";
    }
};

// ==========================================
// CLASE ESTUDIANTE
// ==========================================
class Estudiante : public Persona {
private:
    string carrera;
    int semestre;

public:
    Estudiante(string _nom, string _id, string _cor, string _car, int _sem)
        : Persona(_nom, _id, _cor), carrera(_car), semestre(_sem) {}

    void mostrarPerfil() const override {
        cout << "\n--- PERFIL DEL ESTUDIANTE ---\n";
        cout << "Nombre:    " << nombre << endl; 
        cout << "ID Banner: " << id_banner << endl;
        cout << "Carrera:   " << carrera << endl;
        cout << "Semestre:  " << semestre << "to" << endl;
        cout << "Correo:    " << correo << endl;
        cout << "-----------------------------" << endl;
    }
    
    string getCarrera() const { return carrera; }
    int getSemestre() const { return semestre; }
};

// ==========================================
// CLASE Sesión Tutoría
// ==========================================
class SesionTutoria {
private:
    shared_ptr<Estudiante> estudiante;
    shared_ptr<Tutor> tutor;
    shared_ptr<Materia> materia;
    string fechaHora;

public:
    SesionTutoria(shared_ptr<Estudiante> e, shared_ptr<Tutor> t, shared_ptr<Materia> m, string fecha)
        : estudiante(e), tutor(t), materia(m), fechaHora(fecha) {}

    void setFecha(string nuevaFecha) { fechaHora = nuevaFecha; }
    shared_ptr<Estudiante> getEstudiante() const { return estudiante; }
    shared_ptr<Tutor> getTutor() const { return tutor; }
    shared_ptr<Materia> getMateria() const { return materia; }

    void imprimirDetalles() const {
        cout << " >> [" << fechaHora << "] " << materia->getMateria() 
             << " | Tutor: " << tutor->getNombre() << " | Alumno: " << estudiante->getNombre() << endl;
    }
};

// ==========================================
// CLASE SISTEMA (Gestor Central)
// ==========================================
class SistemaLearningCenter {
private:
    vector<shared_ptr<Persona>> usuarios;
    vector<shared_ptr<Materia>> materias;
    vector<shared_ptr<SesionTutoria>> sesiones;

public:
    SistemaLearningCenter() {}

    shared_ptr<Persona> buscarUsuarioPorId(string id) {
        for (auto& u : usuarios) if (u->getIdBanner() == id) return u;
        return nullptr;
    }

    shared_ptr<Materia> buscarMateriaPorId(string id) {
        for (auto& m : materias) if (m->getCodigo() == id) return m;
        return nullptr;
    }

    void inicializarDatosPrueba() {
        usuarios.push_back(make_shared<Tutor>("Marcelo Diaz", "00123", "marcelo@u.edu", 15.0));
        usuarios.push_back(make_shared<Tutor>("Ana Lopez", "00124", "ana@u.edu", 18.5));
        usuarios.push_back(make_shared<Estudiante>("Maria Lopez", "00332572", "maria@estudiante.edu", "Medicina", 5));
        usuarios.push_back(make_shared<Estudiante>("Carlos Ruiz", "00998877", "carlos@estudiante.edu", "Arquitectura", 2));
        materias.push_back(make_shared<Materia>("Calculo Diferencial", "MATH", 2));
        materias.push_back(make_shared<Materia>("Fisica", "PHYS101", 3));
        cout << "-> Datos de prueba cargados exitosamente.\n";
    }

    void registrarTutor(string _nombre, string _id, string _correo, double _tarifa) {
        usuarios.push_back(make_shared<Tutor>(_nombre, _id, _correo, _tarifa));
        cout << "\n Tutor '" << _nombre << "' registrado con exito.\n";
    }
    
    void registrarMateria(string _nombreM, string _codigoM, int _multiplicador) {
        materias.push_back(make_shared<Materia>(_nombreM, _codigoM, _multiplicador));
        cout << "\n Materia '" << _nombreM << "' registrada con exito.\n";
    }

    void listarMaterias() const {
        cout << "\n--- LISTA DE MATERIAS REGISTRADAS ---\n";
        if (materias.empty()) {
            cout << "No hay materias en el sistema.\n";
            return;
        }
        for (const auto& m : materias) m->mostrarMateria();
        cout << "------------------------------------\n";
    }

    void listarTutores() const {
        cout << "\n--- LISTA DE TUTORES REGISTRADOS ---\n";
        bool hayTutores = false;
        for (const auto& u : usuarios) {
            auto tutorPtr = dynamic_pointer_cast<Tutor>(u);
            if (tutorPtr != nullptr) {
                tutorPtr->mostrarPerfil(); 
                hayTutores = true;
            }
        }
        if (!hayTutores) cout << "No hay tutores registrados.\n";
        cout << "------------------------------------\n";
    }

    void eliminarTutor(string idBorrar) {
        for (auto it = usuarios.begin(); it != usuarios.end(); ) {
            if ((*it)->getIdBanner() == idBorrar) {
                it = usuarios.erase(it);
                cout << "\n[EXITO] El usuario con ID " << idBorrar << " ha sido eliminado.\n";
                return;
            } else ++it;
        }
        cout << "\n[ERROR] No se encontro usuario con ID " << idBorrar << ".\n";
    }

    void eliminarMateria(string codigoBorrar) {
        for (auto it = materias.begin(); it != materias.end(); ) {
            if ((*it)->getCodigo() == codigoBorrar) {
                it = materias.erase(it);
                cout << "\n[EXITO] Materia con codigo " << codigoBorrar << " eliminada.\n";
                return;
            } else ++it;
        }
        cout << "\n[ERROR] Materia no encontrada.\n";
    }

    void modificarTarifaTutor(string idBuscar, double nuevaTarifa) {
        for (auto& usuario : usuarios) {
            if (usuario->getIdBanner() == idBuscar) {
                auto tutorPtr = dynamic_pointer_cast<Tutor>(usuario);
                if (tutorPtr != nullptr) {
                    tutorPtr->setTarifa(nuevaTarifa);
                    cout << "\n[EXITO] Tarifa actualizada a $" << nuevaTarifa << "/h.\n";
                } else cout << "\n[ERROR] No es un Tutor.\n";
                return;
            }
        }
    }

    void modificarCorreoUsuario(string idBuscar, string nuevoCorreo) {
        for (auto& usuario : usuarios) {
            if (usuario->getIdBanner() == idBuscar) {
                usuario->cambiarCorreo(nuevoCorreo);
                cout << "\n[EXITO] Correo actualizado.\n";
                return;
            }
        }
    }

    void modificarMultiplicadorMateria(string codigoBuscar, int nuevoMultiplicador) {
        for (auto& m : materias) {
            if (m->getCodigo() == codigoBuscar) {
                m->setMultiplicador(nuevoMultiplicador);
                cout << "\n[EXITO] Multiplicador actualizado.\n";
                return;
            }
        }
    }

    void agendarTutoria(string idEst, string idTut, string idMat, string fecha) {
        auto pEst = buscarUsuarioPorId(idEst);
        auto pTut = buscarUsuarioPorId(idTut);
        auto mat = buscarMateriaPorId(idMat);
        auto est = dynamic_pointer_cast<Estudiante>(pEst);
        auto tut = dynamic_pointer_cast<Tutor>(pTut);

        if (est && tut && mat) {
            sesiones.push_back(make_shared<SesionTutoria>(est, tut, mat, fecha));
            cout << "\n[EXITO] Tutoria agendada correctamente.\n";
        } else cout << "\n[ERROR] Verifique los IDs.\n";
    }

    void modificarFechaSesion(string idEst, string codMat, string nuevaFecha) {
        for (auto& s : sesiones) {
            if (s->getEstudiante()->getIdBanner() == idEst && s->getMateria()->getCodigo() == codMat) {
                s->setFecha(nuevaFecha);
                cout << "\n[EXITO] Fecha actualizada.\n";
                return;
            }
        }
    }

    void cancelarSesion(string idEst, string codMat) {
        auto it = remove_if(sesiones.begin(), sesiones.end(), [&](shared_ptr<SesionTutoria> s) {
            return s->getEstudiante()->getIdBanner() == idEst && s->getMateria()->getCodigo() == codMat;
        });
        if (it != sesiones.end()) {
            sesiones.erase(it, sesiones.end());
            cout << "\n[EXITO] Tutoria cancelada.\n";
        }
    }

    void verTutoriasDeTutor(string idTut) {
        auto usuario = buscarUsuarioPorId(idTut);
        auto tut = dynamic_pointer_cast<Tutor>(usuario);
        if (!tut) {
            cout << "\n[ERROR] No se encontro un tutor con el ID " << idTut << ".\n";
            return;
        }
        cout << "\n--- SESIONES AGENDADAS PARA EL TUTOR: " << tut->getNombre() << " ---\n";
        bool encontro = false;
        for (const auto& s : sesiones) {
            if (s->getTutor()->getIdBanner() == idTut) {
                s->imprimirDetalles();
                encontro = true;
            }
        }
        if (!encontro) cout << "No tiene sesiones agendadas actualmente.\n";
    }

    void verTutoriasDeEstudiante(string idEst) {
        auto usuario = buscarUsuarioPorId(idEst);
        auto est = dynamic_pointer_cast<Estudiante>(usuario);
        if (!est) {
            cout << "\n[ERROR] No se encontro estudiante con ID " << idEst << ".\n";
            return;
        }
        cout << "\n--- TUTORIAS DE " << est->getNombre() << " ---\n";
        bool encontro = false;
        for (const auto& s : sesiones) {
            if (s->getEstudiante()->getIdBanner() == idEst) {
                s->imprimirDetalles();
                encontro = true;
            }
        }
        if (!encontro) cout << "No tiene tutorias agendadas.\n";
    }
    
    void listarEstudiantes() const {
        cout << "\n--- ESTUDIANTES REGISTRADOS ---\n";
        bool hayEstudiantes = false;
        for (const auto& u : usuarios) {
            auto est = dynamic_pointer_cast<Estudiante>(u);
            if (est) {
                est->mostrarPerfil();
                hayEstudiantes = true;
            }
        }
        if (!hayEstudiantes) cout << "No hay estudiantes registrados.\n";
    }
};

// ==========================================
// MENÚS
// ==========================================
void menuAdministrador(SistemaLearningCenter& sistema);
void menuEstudiante(SistemaLearningCenter& sistema);
void menuTutor(SistemaLearningCenter& sistema);

int main() {
    SistemaLearningCenter sistema;
    cout << "Iniciando Sistema Learning Center...\n";
    sistema.inicializarDatosPrueba();
    int opcionPrincipal;
    do {
        cout << "\n============================================\n";
        cout << "       SISTEMA INTEGRADO LEARNING CENTER      \n";
        cout << "============================================\n";
        cout << "1. Modulo de Estudiante\n2. Modulo de Tutor\n3. Modulo Administrador\n0. Salir del Sistema\nOpcion: ";
        cin >> opcionPrincipal;
        if (opcionPrincipal == 1) menuEstudiante(sistema);
        else if (opcionPrincipal == 2) menuTutor(sistema);
        else if (opcionPrincipal == 3) menuAdministrador(sistema);
    } while (opcionPrincipal != 0);
    return 0;
}

void menuTutor(SistemaLearningCenter& sistema) {
    int opt;
    do {
        cout << "\n--- MODULO TUTOR ---\n";
        cout << "1. Ver mis sesiones agendadas\n2. Regresar al Menu Principal\nOpcion: ";
        cin >> opt;
        if (opt == 1) {
            string id;
            cout << "Ingrese su ID de Tutor: ";
            cin >> id;
            sistema.verTutoriasDeTutor(id);
        }
    } while (opt != 2);
}

void menuAdministrador(SistemaLearningCenter& sistema) {
    int opcion;
    do {
        cout << "\n=== PANEL DE ADMINISTRADOR ===\n";
        cout << "1. Ver tutores registrados\n2. Anadir nuevo tutor\n3. Ver materias registradas\n";
        cout << "4. Anadir nueva materia\n5. Eliminar tutor\n6. Eliminar materia\n";
        cout << "7. Modificar tarifa de un Tutor\n8. Modificar correo de un Usuario\n";
        cout << "9. Modificar multiplicador de Materia\n10. Ver estudiantes registrados\n11. Regresar\nOpcion: ";
        cin >> opcion;
        if (opcion == 1) sistema.listarTutores();
        else if (opcion == 2) {
            string n, id, c; double t;
            cout << "\nID Banner: "; cin >> id; cin.ignore();
            cout << "Nombre: "; getline(cin, n);
            cout << "Correo: "; cin >> c; cout << "Tarifa: "; cin >> t;
            sistema.registrarTutor(n, id, c, t);
        }
        else if (opcion == 3) sistema.listarMaterias();
        else if (opcion == 4) {
            string n, cod; int m;
            cout << "\nCodigo materia: "; cin >> cod; cin.ignore();
            cout << "Nombre materia: "; getline(cin, n);
            cout << "Multiplicador: "; cin >> m;
            sistema.registrarMateria(n, cod, m);
        }
        else if (opcion == 5) { string id; cout << "ID a eliminar: "; cin >> id; sistema.eliminarTutor(id); }
        else if (opcion == 6) { string c; cout << "Codigo a eliminar: "; cin >> c; sistema.eliminarMateria(c); }
        else if (opcion == 7) { string id; double t; cout << "ID Tutor: "; cin >> id; cout << "Nueva Tarifa: "; cin >> t; sistema.modificarTarifaTutor(id, t); }
        else if (opcion == 8) { string id, c; cout << "ID Usuario: "; cin >> id; cout << "Nuevo Correo: "; cin >> c; sistema.modificarCorreoUsuario(id, c); }
        else if (opcion == 9) { string id; int m; cout << "Cod Materia: "; cin >> id; cout << "Nuevo Mult: "; cin >> m; sistema.modificarMultiplicadorMateria(id, m); }
        else if (opcion == 10) sistema.listarEstudiantes();
    } while (opcion != 11);
}

void menuEstudiante(SistemaLearningCenter& sistema) {
    int opt;
    do {
        cout << "\n--- MODULO ESTUDIANTE ---\n";
        cout << "1. Ver Materias\n2. Agendar Tutoria\n3. Modificar Fecha\n4. Cancelar Tutoria\n5. Ver mis Sesiones\n6. Regresar\nOpcion: ";
        cin >> opt;
        if (opt == 1) sistema.listarMaterias();
        else if (opt == 2) {
            string e, t, m, f;
            cout << "Tu ID: "; cin >> e; cout << "ID Tutor: "; cin >> t;
            cout << "Cod Materia: "; cin >> m; cout << "Fecha: "; cin >> f;
            sistema.agendarTutoria(e, t, m, f);
        }
        else if (opt == 3) {
            string e, m, f;
            cout << "Tu ID: "; cin >> e; cout << "Cod Materia: "; cin >> m;
            cout << "Nueva Fecha: "; cin >> f;
            sistema.modificarFechaSesion(e, m, f);
        }
        else if (opt == 4) {
            string e, m;
            cout << "Tu ID: "; cin >> e; cout << "Cod Materia: "; cin >> m;
            sistema.cancelarSesion(e, m);
        }
        else if (opt == 5) {
            string id; cout << "Tu ID: "; cin >> id;
            sistema.verTutoriasDeEstudiante(id);
        }
    } while (opt != 6);
}