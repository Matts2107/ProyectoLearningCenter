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
        cout << "ID: " << codigoM << " | Nombre: " << nombreM 
            << " | Multiplicador: " << multiplicador << "\n";
    }
    
    string getMateria() const { return nombreM; }
    string getCodigo() const { return codigoM; }
    void setMultiplicador(int m) { multiplicador = m; }
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
    void cambiarCorreo(string nuevoCorreo) { correo = nuevoCorreo; }
    string getIdBanner() const { return id_banner; }
    string getNombre() const { return nombre; }
    virtual ~Persona() {} 
};

// ==========================================
// CLASE ESTUDIANTE
// ==========================================
class Estudiante : public Persona {
private:
    string carrera;
    int semestre;

public:
    Estudiante(string _nom, string _id, string _cor, string _carr, int _sem)
        : Persona(_nom, _id, _cor), carrera(_carr), semestre(_sem) {}

    void mostrarPerfil() const override {
        cout << "[Estudiante] ID: " << id_banner 
             << " | Nombre: " << nombre 
             << " | Carrera: " << carrera << " (" << semestre << "mo)\n";
    }
};

// ==========================================
// CLASE TUTOR
// ==========================================
class Tutor : public Persona {
private:
    double tarifa_hora;

public:
    Tutor(string _nom, string _id, string _cor, double _tarifa)
        : Persona(_nom, _id, _cor), tarifa_hora(_tarifa) {}

    void mostrarPerfil() const override {
        cout << "[Tutor]      ID: " << id_banner 
             << " | Nombre: " << nombre 
             << " | Tarifa: $" << tarifa_hora << "/h\n";
    }
    void setTarifa(double t) { tarifa_hora = t; }
};

// ==========================================
// CLASE SESIÓN TUTORÍA
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
    shared_ptr<Materia> getMateria() const { return materia; }

    void imprimirDetalles() const {
        cout << " >> [" << fechaHora << "] MATERIA: " << materia->getMateria() 
             << " | TUTOR: " << tutor->getNombre() 
             << " | ALUMNO: " << estudiante->getNombre() << endl;
    }
};

// ==========================================
// CLASE SISTEMA (Gestor Central Completo)
// ==========================================
class SistemaLearningCenter {
private:
    vector<shared_ptr<Persona>> usuarios; 
    vector<shared_ptr<Materia>> materias;
    vector<shared_ptr<SesionTutoria>> sesiones;

public:
    shared_ptr<Persona> buscarUsuarioPorId(string id) {
        for (auto& u : usuarios) if (u->getIdBanner() == id) return u;
        return nullptr;
    }

    shared_ptr<Materia> buscarMateriaPorId(string id) {
        for (auto& m : materias) if (m->getCodigo() == id) return m;
        return nullptr;
    }

    void inicializarDatosPrueba() {
        usuarios.push_back(make_shared<Tutor>("Marcelo Diaz", "T001", "marcelo@u.edu", 15.0));
        usuarios.push_back(make_shared<Estudiante>("Mattias", "E001", "matt@u.edu", "Computacion", 4));
        materias.push_back(make_shared<Materia>("Calculo Diferencial", "MATH101", 2));
        materias.push_back(make_shared<Materia>("Fisica", "PHYS101", 3));
        cout << "-> Datos de prueba cargados con exito.\n";
    }

    // --- OPERACIONES DE AGENDAMIENTO ---
    void agendarTutoria(string idEst, string idTut, string idMat, string fecha) {
        auto pEst = buscarUsuarioPorId(idEst);
        auto pTut = buscarUsuarioPorId(idTut);
        auto mat = buscarMateriaPorId(idMat);

        auto est = dynamic_pointer_cast<Estudiante>(pEst);
        auto tut = dynamic_pointer_cast<Tutor>(pTut);

        if (est && tut && mat) {
            sesiones.push_back(make_shared<SesionTutoria>(est, tut, mat, fecha));
            cout << "\n[EXITO] Tutoria agendada correctamente.\n";
        } else {
            cout << "\n[ERROR] Verifique que los IDs existan y los roles sean correctos.\n";
        }
    }

    void modificarFechaTutoria(string idEst, string codMat, string nuevaFecha) {
        for (auto& s : sesiones) {
            if (s->getEstudiante()->getIdBanner() == idEst && s->getMateria()->getCodigo() == codMat) {
                s->setFecha(nuevaFecha);
                cout << "\n[EXITO] Fecha actualizada a: " << nuevaFecha << endl;
                return;
            }
        }
        cout << "\n[ERROR] No se encontro ninguna tutoria activa con esos datos.\n";
    }

    void cancelarTutoria(string idEst, string codMat) {
        auto it = remove_if(sesiones.begin(), sesiones.end(), [&](shared_ptr<SesionTutoria> s){
            return s->getEstudiante()->getIdBanner() == idEst && s->getMateria()->getCodigo() == codMat;
        });

        if (it != sesiones.end()) {
            sesiones.erase(it, sesiones.end());
            cout << "\n[EXITO] Tutoria cancelada y eliminada del sistema.\n";
        } else {
            cout << "\n[ERROR] No se encontro la tutoria para cancelar.\n";
        }
    }

    // --- LISTADOS ---
    void listarTutores() const {
        cout << "\n--- TUTORES REGISTRADOS ---\n";
        for (const auto& u : usuarios) {
            if (dynamic_pointer_cast<Tutor>(u)) u->mostrarPerfil();
        }
    }

    void listarMaterias() const {
        cout << "\n--- MATERIAS DISPONIBLES ---\n";
        for (const auto& m : materias) m->mostrarMateria();
    }

    void listarHistorial() const {
        cout << "\n--- CRONOGRAMA DE TUTORIAS ---\n";
        if (sesiones.empty()) cout << "No hay sesiones registradas.\n";
        for (const auto& s : sesiones) s->imprimirDetalles();
    }

    // --- ADMIN CRUD ---
    void registrarTutor(string n, string id, string c, double t) {
        usuarios.push_back(make_shared<Tutor>(n, id, c, t));
        cout << "\nTutor registrado.\n";
    }

    void registrarMateria(string n, string cod, int m) {
        materias.push_back(make_shared<Materia>(n, cod, m));
        cout << "\nMateria registrada.\n";
    }

    void eliminarUsuario(string id) {
        auto it = remove_if(usuarios.begin(), usuarios.end(), [&](shared_ptr<Persona> u){
            return u->getIdBanner() == id;
        });
        if (it != usuarios.end()) {
            usuarios.erase(it, usuarios.end());
            cout << "\n[EXITO] Usuario eliminado.\n";
        } else cout << "\n[ERROR] ID no encontrado.\n";
    }
};

// ==========================================
// FUNCIONES DE MENÚ
// ==========================================
void menuAdministrador(SistemaLearningCenter& sistema);
void menuEstudiante(SistemaLearningCenter& sistema);

int main() {
    SistemaLearningCenter sistema;
    sistema.inicializarDatosPrueba();
    
    int opcionPrincipal;
    do {
        cout << "\n============================================\n";
        cout << "       SISTEMA INTEGRADO LEARNING CENTER      \n";
        cout << "============================================\n";
        cout << "1. Modulo de Estudiante\n2. Modulo Administrador\n0. Salir\nOpcion: ";
        cin >> opcionPrincipal;
        
        if (opcionPrincipal == 1) menuEstudiante(sistema);
        else if (opcionPrincipal == 2) menuAdministrador(sistema);
        
    } while (opcionPrincipal != 0);
    
    return 0;
}

void menuEstudiante(SistemaLearningCenter& sistema) {
    int opcion;
    do {
        cout << "\n--- MODULO ESTUDIANTE ---\n";
        cout << "1. Ver Materias\n2. Agendar Tutoria\n3. Modificar Fecha de Tutoria\n4. Cancelar Tutoria\n5. Ver mis Sesiones\n6. Regresar\nOpcion: ";
        cin >> opcion;

        if (opcion == 1) sistema.listarMaterias();
        else if (opcion == 2) {
            string e, t, m, f;
            cout << "Tu ID Estudiante: "; cin >> e;
            cout << "ID del Tutor: "; cin >> t;
            cout << "Codigo Materia: "; cin >> m;
            cout << "Fecha (ej: 25/04-10am): "; cin >> f;
            sistema.agendarTutoria(e, t, m, f);
        }
        else if (opcion == 3) {
            string e, m, f;
            cout << "Tu ID Estudiante: "; cin >> e;
            cout << "Codigo Materia de la tutoria: "; cin >> m;
            cout << "Nueva Fecha/Hora: "; cin >> f;
            sistema.modificarFechaTutoria(e, m, f);
        }
        else if (opcion == 4) {
            string e, m;
            cout << "Tu ID Estudiante: "; cin >> e;
            cout << "Codigo Materia a cancelar: "; cin >> m;
            sistema.cancelarTutoria(e, m);
        }
        else if (opcion == 5) sistema.listarHistorial();

    } while (opcion != 6);
}

void menuAdministrador(SistemaLearningCenter& sistema) {
    int opcion;
    do {
        cout << "\n--- PANEL ADMINISTRADOR ---\n";
        cout << "1. Listar Tutores\n2. Registrar Nuevo Tutor\n3. Registrar Materia\n4. Eliminar Usuario\n5. Regresar\nOpcion: ";
        cin >> opcion;

        if (opcion == 1) sistema.listarTutores();
        else if (opcion == 2) {
            string n, id, c; double t;
            cout << "Nombre: "; cin.ignore(); getline(cin, n);
            cout << "ID: "; cin >> id;
            cout << "Correo: "; cin >> c;
            cout << "Tarifa: "; cin >> t;
            sistema.registrarTutor(n, id, c, t);
        }
        else if (opcion == 3) {
            string n, cod; int m;
            cout << "Nombre Materia: "; cin.ignore(); getline(cin, n);
            cout << "Codigo: "; cin >> cod;
            cout << "Multiplicador: "; cin >> m;
            sistema.registrarMateria(n, cod, m);
        }
        else if (opcion == 4) {
            string id; cout << "ID a borrar: "; cin >> id;
            sistema.eliminarUsuario(id);
        }
    } while (opcion != 5);
}