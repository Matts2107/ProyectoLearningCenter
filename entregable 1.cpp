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
             << " | Mult: " << multiplicador << endl;
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
// CLASE Empleado (Base laboral)
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
// CLASE Estudiante
// ==========================================
class Estudiante : public Persona {
private:
    string carrera;
    int semestre;

public:
    Estudiante(string _nom, string _id, string _cor, string _carr, int _sem)
        : Persona(_nom, _id, _cor), carrera(_carr), semestre(_sem) {}

    void mostrarPerfil() const override {
        cout << "[Estudiante] ID: " << id_banner << " | Nombre: " << nombre 
             << " | Carrera: " << carrera << " (" << semestre << "mo)\n";
    }
};

// ==========================================
// CLASE Tutor (Hereda de Persona y Empleado)
// ==========================================
class Tutor : public Persona, public Empleado {
public:
    Tutor(string _nom, string _id, string _cor, double _tarifa)
        : Persona(_nom, _id, _cor), Empleado(_tarifa) {}

    void mostrarPerfil() const override {
        cout << "[Tutor]      ID: " << id_banner << " | Nombre: " << nombre 
             << " | Tarifa: $" << tarifaBase << "/h\n";
    }
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
    shared_ptr<Materia> getMateria() const { return materia; }

    void imprimirDetalles() const {
        cout << " >> [" << fechaHora << "] " << materia->getMateria() 
             << " | Tutor: " << tutor->getNombre() << " | Alumno: " << estudiante->getNombre() << endl;
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
    // BUSCADORES
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
        cout << "-> Datos de prueba cargados.\n";
    }

    // OPERACIONES DE SESIONES
    void agendarTutoria(string idEst, string idTut, string idMat, string fecha) {
        auto pEst = buscarUsuarioPorId(idEst);
        auto pTut = buscarUsuarioPorId(idTut);
        auto mat = buscarMateriaPorId(idMat);

        auto est = dynamic_pointer_cast<Estudiante>(pEst);
        auto tut = dynamic_pointer_cast<Tutor>(pTut);

        if (est && tut && mat) {
            sesiones.push_back(make_shared<SesionTutoria>(est, tut, mat, fecha));
            cout << "\n[OK] Tutoria agendada exitosamente.\n";
        } else cout << "\n[ERROR] Verifique los IDs y tipos de usuario.\n";
    }

    void listarHistorial() const {
        cout << "\n--- HISTORIAL DE SESIONES ---\n";
        if (sesiones.empty()) cout << "No hay tutorias agendadas.\n";
        for (const auto& s : sesiones) s->imprimirDetalles();
    }

    // MÉTODOS DEL ADMINISTRADOR (Imagen)
    void listarTutores() const {
        cout << "\n--- TUTORES REGISTRADOS ---\n";
        for (const auto& u : usuarios) if (dynamic_pointer_cast<Tutor>(u)) u->mostrarPerfil();
    }

    void registrarTutor(string n, string id, string c, double t) {
        usuarios.push_back(make_shared<Tutor>(n, id, c, t));
        cout << "\n[EXITO] Tutor registrado.\n";
    }

    void listarMaterias() const {
        cout << "\n--- MATERIAS REGISTRADAS ---\n";
        for (const auto& m : materias) m->mostrarMateria();
    }

    void registrarMateria(string n, string cod, int m) {
        materias.push_back(make_shared<Materia>(n, cod, m));
        cout << "\n[EXITO] Materia registrada.\n";
    }

    void eliminarTutor(string id) {
        auto it = remove_if(usuarios.begin(), usuarios.end(), [&](shared_ptr<Persona> u){
            return u->getIdBanner() == id && dynamic_pointer_cast<Tutor>(u);
        });
        if (it != usuarios.end()) { usuarios.erase(it, usuarios.end()); cout << "\n[EXITO] Tutor eliminado.\n"; }
        else cout << "\n[ERROR] No se encontro un tutor con ese ID.\n";
    }

    void eliminarMateria(string cod) {
        auto it = remove_if(materias.begin(), materias.end(), [&](shared_ptr<Materia> m){ return m->getCodigo() == cod; });
        if (it != materias.end()) { materias.erase(it, materias.end()); cout << "\n[EXITO] Materia eliminada.\n"; }
        else cout << "\n[ERROR] Codigo no encontrado.\n";
    }

    void modificarTarifa(string id, double t) {
        auto u = buscarUsuarioPorId(id);
        auto tut = dynamic_pointer_cast<Tutor>(u);
        if (tut) { tut->setTarifa(t); cout << "\n[EXITO] Tarifa actualizada.\n"; }
        else cout << "\n[ERROR] ID no corresponde a un tutor.\n";
    }

    void modificarCorreo(string id, string c) {
        auto u = buscarUsuarioPorId(id);
        if (u) { u->cambiarCorreo(c); cout << "\n[EXITO] Correo actualizado.\n"; }
        else cout << "\n[ERROR] Usuario no encontrado.\n";
    }

    void modificarMultiplicador(string cod, int m) {
        auto mat = buscarMateriaPorId(cod);
        if (mat) { mat->setMultiplicador(m); cout << "\n[EXITO] Multiplicador actualizado.\n"; }
        else cout << "\n[ERROR] Materia no encontrada.\n";
    }
};

// ==========================================
// MENÚS Y MAIN
// ==========================================
void menuAdministrador(SistemaLearningCenter& sistema);
void menuEstudiante(SistemaLearningCenter& sistema);

int main() {
    SistemaLearningCenter sistema;
    sistema.inicializarDatosPrueba();
    int opcionPrincipal;

    do {
        cout << "\n=== SISTEMA INTEGRADO LEARNING CENTER ===\n";
        cout << "1. Modulo de Estudiante\n2. Modulo Administrador\n0. Salir\nOpcion: ";
        cin >> opcionPrincipal;
        if (opcionPrincipal == 1) menuEstudiante(sistema);
        else if (opcionPrincipal == 2) menuAdministrador(sistema);
    } while (opcionPrincipal != 0);

    return 0;
}

void menuAdministrador(SistemaLearningCenter& sistema) {
    int opcion;
    do {
        cout << "\n=== PANEL DE ADMINISTRADOR ===\n";
        cout << "1. Ver tutores registrados\n2. Anadir nuevo tutor\n3. Ver materias registradas\n";
        cout << "4. Anadir nueva materia\n5. Eliminar tutor\n6. Eliminar materia\n";
        cout << "7. Modificar tarifa de un Tutor\n8. Modificar correo de un Usuario\n";
        cout << "9. Modificar multiplicador de Materia\n10. Regresar al Menu Principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) sistema.listarTutores();
        else if (opcion == 2) {
            string n, id, c; double t;
            cout << "ID: "; cin >> id; cin.ignore(); cout << "Nombre: "; getline(cin, n);
            cout << "Correo: "; cin >> c; cout << "Tarifa: "; cin >> t;
            sistema.registrarTutor(n, id, c, t);
        }
        else if (opcion == 3) sistema.listarMaterias();
        else if (opcion == 4) {
            string n, cod; int m;
            cout << "Codigo: "; cin >> cod; cin.ignore(); cout << "Nombre: "; getline(cin, n);
            cout << "Multiplicador: "; cin >> m;
            sistema.registrarMateria(n, cod, m);
        }
        else if (opcion == 5) { string id; cout << "ID a eliminar: "; cin >> id; sistema.eliminarTutor(id); }
        else if (opcion == 6) { string cod; cout << "Codigo a eliminar: "; cin >> cod; sistema.eliminarMateria(cod); }
        else if (opcion == 7) { string id; double t; cout << "ID Tutor: "; cin >> id; cout << "Nueva Tarifa: "; cin >> t; sistema.modificarTarifa(id, t); }
        else if (opcion == 8) { string id, c; cout << "ID Usuario: "; cin >> id; cout << "Nuevo Correo: "; cin >> c; sistema.modificarCorreo(id, c); }
        else if (opcion == 9) { string cod; int m; cout << "Cod Materia: "; cin >> cod; cout << "Nuevo Multiplicador: "; cin >> m; sistema.modificarMultiplicador(cod, m); }

    } while (opcion != 10);
}

void menuEstudiante(SistemaLearningCenter& sistema) {
    int opt;
    do {
        cout << "\n[MODULO ESTUDIANTE]\n1. Agendar Tutoria\n2. Ver Historial\n3. Regresar\nOpcion: ";
        cin >> opt;
        if (opt == 1) {
            string e, t, m, f;
            cout << "ID Estudiante: "; cin >> e; cout << "ID Tutor: "; cin >> t;
            cout << "Cod Materia: "; cin >> m; cout << "Fecha: "; cin >> f;
            sistema.agendarTutoria(e, t, m, f);
        }
        else if (opt == 2) sistema.listarHistorial();
    } while (opt != 3);
}