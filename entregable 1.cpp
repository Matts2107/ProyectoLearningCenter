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
// CLASE ESTUDIANTE (Hereda de Persona) - ¡RECUPERADA!
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
// CLASE TUTOR (Hereda de Persona)
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
// CLASE SESIÓN TUTORÍA - ¡RECUPERADA!
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

    void imprimirRecibo() const {
        cout << "\n--- RECIBO DE TUTORIA ---" << endl;
        cout << "Fecha: " << fechaHora << endl;
        cout << "Materia: " << materia->getMateria() << endl;
        cout << "Estudiante: " << estudiante->getNombre() << endl;
        cout << "Tutor: " << tutor->getNombre() << endl;
        cout << "-------------------------" << endl;
    }
};

// ==========================================
// CLASE SISTEMA (Gestor Central FUSIONADO)
// ==========================================
class SistemaLearningCenter {
private:
    vector<shared_ptr<Persona>> usuarios; 
    vector<shared_ptr<Materia>> materias;
    vector<shared_ptr<SesionTutoria>> historialSesiones;

public:
    // BUSCADORES CLAVE (Lo que le faltaba a tu amigo)
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

    // REGISTROS (CRUD)
    void registrarTutor(string n, string id, string c, double t) {
        usuarios.push_back(make_shared<Tutor>(n, id, c, t));
    }

    void registrarEstudiante(string n, string id, string c, string carr, int s) {
        usuarios.push_back(make_shared<Estudiante>(n, id, c, carr, s));
    }

    // MOTOR DE AGENDAMIENTO (El corazón de tu código)
    void agendarTutoria(string idEst, string idTut, string idMat, string fecha) {
        auto pEst = buscarUsuarioPorId(idEst);
        auto pTut = buscarUsuarioPorId(idTut);
        auto mat = buscarMateriaPorId(idMat);

        if (!pEst || !pTut || !mat) {
            cout << "[ERROR] Uno de los IDs ingresados no existe.\n";
            return;
        }

        // CASTEO DINÁMICO (Seguridad de POO)
        auto est = dynamic_pointer_cast<Estudiante>(pEst);
        auto tut = dynamic_pointer_cast<Tutor>(pTut);

        if (est && tut) {
            auto nueva = make_shared<SesionTutoria>(est, tut, mat, fecha);
            historialSesiones.push_back(nueva);
            cout << "[OK] Tutoria agendada exitosamente.\n";
            nueva->imprimirRecibo();
        } else {
            cout << "[ERROR] Asegurese de que los IDs correspondan a Estudiante y Tutor.\n";
        }
    }

    // LISTADOS
    void listarTutores() const {
        cout << "\n--- LISTA DE TUTORES ---\n";
        for (const auto& u : usuarios) u->mostrarPerfil();
    }

    void listarMaterias() const {
        cout << "\n--- LISTA DE MATERIAS ---\n";
        for (const auto& m : materias) m->mostrarMateria();
    }

    void listarHistorial() const {
        cout << "\n--- HISTORIAL DE SESIONES ---\n";
        if (historialSesiones.empty()) cout << "No hay sesiones agendadas.\n";
        for (const auto& s : historialSesiones) s->imprimirRecibo();
    }
    
    // ELIMINACIÓN (Lógica de tu amigo)
    void eliminarUsuario(string id) {
        auto it = remove_if(usuarios.begin(), usuarios.end(), [&](shared_ptr<Persona> u){
            return u->getIdBanner() == id;
        });
        if (it != usuarios.end()) {
            usuarios.erase(it, usuarios.end());
            cout << "[EXITO] Usuario eliminado.\n";
        } else cout << "[ERROR] No encontrado.\n";
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
    
    int opcion;
    do {
        cout << "\n--- MENU PRINCIPAL ---\n";
        cout << "1. Modulo Estudiante (Agendar)\n2. Modulo Administrador\n0. Salir\nOpcion: ";
        cin >> opcion;
        
        if (opcion == 1) menuEstudiante(sistema);
        else if (opcion == 2) menuAdministrador(sistema);
        
    } while (opcion != 0);
    
    return 0;
}

void menuEstudiante(SistemaLearningCenter& sistema) {
    int opt;
    cout << "\n1. Ver Materias\n2. Agendar Tutoria\n3. Ver mis sesiones\nOpcion: ";
    cin >> opt;
    if (opt == 1) sistema.listarMaterias();
    else if (opt == 2) {
        string e, t, m, f;
        cout << "Tu ID Estudiante: "; cin >> e;
        cout << "ID del Tutor: "; cin >> t;
        cout << "Codigo Materia: "; cin >> m;
        cout << "Fecha (dd/mm): "; cin >> f;
        sistema.agendarTutoria(e, t, m, f);
    }
    else if (opt == 3) sistema.listarHistorial();
}

void menuAdministrador(SistemaLearningCenter& sistema) {
    int opcion;
    cout << "\n1. Listar Tutores\n2. Registrar Tutor\n3. Registrar Estudiante\n4. Eliminar Usuario\nOpcion: ";
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
        string n, id, c, carr; int s;
        cout << "Nombre: "; cin.ignore(); getline(cin, n);
        cout << "ID: "; cin >> id;
        cout << "Correo: "; cin >> c;
        cout << "Carrera: "; cin >> carr;
        cout << "Semestre: "; cin >> s;
        sistema.registrarEstudiante(n, id, c, carr, s);
    }
    else if (opcion == 4) {
        string id; cout << "ID a eliminar: "; cin >> id;
        sistema.eliminarUsuario(id);
    }
}