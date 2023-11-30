// rover.cpp
#include "rover.h"

Rover::Rover(int pinMotorIzqDelantero, int pinMotorIzqTrasero, int pinMotorDerDelantero, int pinMotorDerTrasero,
             int pinIrDelantero, int pinIrTrasero, int pinUltrasonidoEcho, int pinUltrasonidoTrig,
             int pinSensorLuz)
    : pinMotorIzqDelantero(pinMotorIzqDelantero), pinMotorIzqTrasero(pinMotorIzqTrasero),
      pinMotorDerDelantero(pinMotorDerDelantero), pinMotorDerTrasero(pinMotorDerTrasero),
      pinIrDelantero(pinIrDelantero), pinIrTrasero(pinIrTrasero),
      pinUltrasonidoEcho(pinUltrasonidoEcho), pinUltrasonidoTrig(pinUltrasonidoTrig),
      pinSensorLuz(pinSensorLuz) {
    pinMode(pinMotorIzqDelantero, OUTPUT);
    pinMode(pinMotorIzqTrasero, OUTPUT);
    pinMode(pinMotorDerDelantero, OUTPUT);
    pinMode(pinMotorDerTrasero, OUTPUT);
    pinMode(pinIrDelantero, INPUT);
    pinMode(pinIrTrasero, INPUT);
    pinMode(pinUltrasonidoEcho, INPUT);
    pinMode(pinUltrasonidoTrig, OUTPUT);
    pinMode(pinSensorLuz, INPUT);

    receptorIR = new IRrecv(pinReceptorIR);
    receptorIR->enableIRIn();
}

void Rover::moverAdelante() {
    digitalWrite(pinMotorIzqDelantero, HIGH);
    digitalWrite(pinMotorIzqTrasero, LOW);
    digitalWrite(pinMotorDerDelantero, HIGH);
    digitalWrite(pinMotorDerTrasero, LOW);
}

void Rover::moverAtras() {
    digitalWrite(pinMotorIzqDelantero, LOW);
    digitalWrite(pinMotorIzqTrasero, HIGH);
    digitalWrite(pinMotorDerDelantero, LOW);
    digitalWrite(pinMotorDerTrasero, HIGH);
}

void Rover::girarIzquierda() {
    digitalWrite(pinMotorIzqDelantero, LOW);
    digitalWrite(pinMotorIzqTrasero, HIGH);
    digitalWrite(pinMotorDerDelantero, HIGH);
    digitalWrite(pinMotorDerTrasero, LOW);
}

void Rover::girarDerecha() {
    digitalWrite(pinMotorIzqDelantero, HIGH);
    digitalWrite(pinMotorIzqTrasero, LOW);
    digitalWrite(pinMotorDerDelantero, LOW);
    digitalWrite(pinMotorDerTrasero, HIGH);
}

void Rover::detener() {
    digitalWrite(pinMotorIzqDelantero, LOW);
    digitalWrite(pinMotorIzqTrasero, LOW);
    digitalWrite(pinMotorDerDelantero, LOW);
    digitalWrite(pinMotorDerTrasero, LOW);
}

bool Rover::detectarObstaculo() {
    // Devuelve true si se detecta un obstáculo, false de lo contrario
    int lecturaIrDelantero = digitalRead(pinIrDelantero);
    int lecturaIrTrasero = digitalRead(pinIrTrasero);

    return (lecturaIrDelantero == HIGH || lecturaIrTrasero == HIGH);
}

float Rover::obtenerDistancia() {
    digitalWrite(pinUltrasonidoTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(pinUltrasonidoTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(pinUltrasonidoTrig, LOW);

    duracion = pulseIn(pinUltrasonidoEcho, HIGH);
    distancia = (duracion * 0.0343) / 2;

    Serial.print("Distancia: ");
    Serial.println(distancia);

    delay(100);
    return distancia;
}

int Rover::obtenerIntensidadLuz() {
    // Lee la intensidad de luz utilizando el sensor de luz
    return analogRead(pinSensorLuz);
}

void Rover::manejarControlRemoto() {
    if (receptorIR->decode(&resultadosIR)) {
        switch (resultadosIR.value) {
            case 0xFF30CF:  // Tecla 1
                modoExplorador();
                break;
            case 0xFF18E7:  // Tecla 2
                modoInfrarrojo();
                break;
            case 0xFF7A85:  // Tecla 3
                modoSensorLuz();
                break;
        }

        receptorIR->resume();
    }
}