#include "SesionTutoria.h"
#include <iostream>

using namespace std;

// El constructor ya está implementado en el .h (inline), 
// así que aquí implementamos los métodos que faltan.

void SesionTutoria::imprimirRecibo() {
    cout << "\n========================================" << endl;
    cout << "       COMPROBANTE DE TUTORIA" << endl;
    cout << "========================================" << endl;
    
    // Accedemos a los datos de los objetos apuntados por los shared_ptr
    if (estudiante_ptr) {
        cout << "ESTUDIANTE: " << estudiante_ptr->getNombre() << endl;
    }
    
    if (tutor_ptr) {
        cout << "TUTOR:      " << tutor_ptr->getNombre() << endl;
    }
    
    if (materia_ptr) {
        cout << "MATERIA:    " << materia_ptr->getNombre() << " (" << materia_ptr->getCodigo() << ")" << endl;
    }
    
    cout << "FECHA/HORA: " << fecha << endl;
    cout << "DURACION:   " << duracion_horas << " hora(s)" << endl;
    cout << "ESTADO:     " << (esta_finalizada ? "FINALIZADA" : "PENDIENTE") << endl;
    cout << "----------------------------------------" << endl;
}