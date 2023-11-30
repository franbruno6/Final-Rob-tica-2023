// rover.h
#ifndef ROVER_H
#define ROVER_H

#include <Arduino.h>

class Rover {
public:
    Rover(int pinMotorIzqDelantero, int pinMotorIzqTrasero, int pinMotorDerDelantero, int pinMotorDerTrasero,
          int pinIrDelantero, int pinIrTrasero, int pinUltrasonidoEcho, int pinUltrasonidoTrig,
          int pinSensorLuz);

    void moverAdelante();
    void moverAtras();
    void girarIzquierda();
    void girarDerecha();
    void detener();

    // Funciones de los sensores
    bool detectarObstaculo();
    int obtenerIntensidadLuz();
    float obtenerDistancia();

    void manejarControlRemoto();

private:
    int pinMotorIzqDelantero, pinMotorIzqTrasero, pinMotorDerDelantero, pinMotorDerTrasero;
    int pinIrDelantero, pinIrTrasero, pinUltrasonidoEcho, pinUltrasonidoTrig;
    int pinSensorLuz;
};

#endif