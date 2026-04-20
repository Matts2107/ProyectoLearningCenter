#include <iostream>
#include <string>
#include <vector>
#include <memory>

// ==========================================
// CLASE MATERIA 
//===========================================

class Materia {
private:
    std::string nombreM;
    std::string codigoM; 
    int multiplicador;   

public:
    // Constructor corregido
    Materia(std::string n_, std::string cod_, int mult_) 
        : nombreM(n_), codigoM(cod_), multiplicador(mult_) {}
    
    // Función sin override, ya que no hay herencia aquí
    void mostrarMateria() const {
        std::cout << "ID: " << codigoM 
                  << " | Nombre: " << nombreM 
                  << " | Multiplicador: " << multiplicador << "\n";
    }
    
    // Getters
    std::string getMateria() const { return nombreM; }
    std::string getCodigo() const { return codigoM; }
    int getMultiplicador() const { return multiplicador; } 

    // --- SETTER AÑADIDO ---
    void setMultiplicador(int nuevoMultiplicador) {
        multiplicador = nuevoMultiplicador;
    }
}; 

// ==========================================
// CLASE ABSTRACTA BASE
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

    std::string getIdBanner() const { return id_banner; }
    std::string getNombre() const { return nombre; }

    virtual ~Persona() {} 
};

// ==========================================
// CLASE TUTOR (Hereda de Persona)
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
        std::cout << "-> Datos de prueba cargados exitosamente.\n";
    }

    // Método para el Administrador (Create)
    void registrarTutor(std::string _nombre, std::string _id, std::string _correo, double _tarifa) {
        usuarios.push_back(std::make_shared<Tutor>(_nombre, _id, _correo, _tarifa));
        std::cout << "\n Tutor '" << _nombre << "' registrado con exito.\n";
    }

    void registrarMateria(std::string _nombreM, std::string _codigoM, int _multiplicador) {
        materias.push_back(std::make_shared<Materia>(_nombreM, _codigoM, _multiplicador));
        std::cout << "\n Materia '" << _nombreM << "' registrada con exito.\n";
    }

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


    // Método para el Administrador (Read)
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
};

// ==========================================
// FUNCION PRINCIPAL
// ==========================================
int main() {
    SistemaLearningCenter sistema;
    
    std::cout << "Iniciando Sistema Learning Center...\n";
    sistema.inicializarDatosPrueba();

    int opcion;
    do {
        std::cout << "\n=== PANEL DE ADMINISTRADOR ===\n";
        std::cout << "1. Ver tutores registrados\n";
        std::cout << "2. Anadir nuevo tutor\n";
        std::cout << "3. Ver materias registradas\n";
        std::cout << "4. Anadir nueva materia\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            sistema.listarTutores();
        } 
        else if (opcion == 2) {
            std::string nombre, id, correo;
            double tarifa;

            std::cout << "\n--- REGISTRO DE NUEVO TUTOR ---\n";
            std::cout << "Ingrese el ID Banner: ";
            std::cin >> id;
            
            std::cin.ignore(); // Limpiar el buffer antes de leer con espacios
            std::cout << "Ingrese el Nombre completo: ";
            std::getline(std::cin, nombre);
            
            std::cout << "Ingrese el Correo: ";
            std::cin >> correo;
            
            std::cout << "Ingrese la Tarifa por hora: ";
            std::cin >> tarifa;

            sistema.registrarTutor(nombre, id, correo, tarifa);
        }
        else if (opcion == 3) {
            sistema.listarMaterias();
        }
        else if (opcion == 4) {
            std::string nombreM, codigoM;
            int multiplicador;

            std::cout << "\n--- REGISTRO DE NUEVA MATERIA ---\n";
            std::cout << "Ingrese el Codigo de la materia: ";
            std::cin >> codigoM;
            
            std::cin.ignore(); // Limpiar el buffer antes de leer con espacios
            std::cout << "Ingrese el Nombre de la materia: ";
            std::getline(std::cin, nombreM);
            
            std::cout << "Ingrese el Multiplicador de horas: ";
            std::cin >> multiplicador;

            sistema.registrarMateria(nombreM, codigoM, multiplicador);
        }

    } while (opcion != 5);

    std::cout << "\nSaliendo del sistema. ¡Hasta pronto!\n";
    return 0;
}
