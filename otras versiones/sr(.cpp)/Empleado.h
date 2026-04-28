#ifndef EMPLEADO_H
#define EMPLEADO_H

class Empleado {
protected:
    double tarifaBasePorHora;

public:
    Empleado(double _tarifa) : tarifaBasePorHora(_tarifa) {}

    // Función virtual para calcular el pago, se puede sobrescribir
    virtual double calcularPago(double horas) {
        return horas * tarifaBasePorHora;
    }

    virtual ~Empleado() {}
};

#endif