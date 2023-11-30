//main.cpp
#include "rover.h"
#include <IRremote.h> 

const int PIN_MOTOR_IZQ_DELANTERO = 5;
const int PIN_MOTOR_IZQ_TRASERO = 4;
const int PIN_MOTOR_DER_DELANTERO = 6;
const int PIN_MOTOR_DER_TRASERO = 7;
const int PIN_IR_DELANTERO = 8;
const int PIN_IR_TRASERO = 9;
const int PIN_ULTRASONIDO_ECHO = 11;
const int PIN_ULTRASONIDO_TRIG = 12;
const int PIN_SENSOR_LUZ = A0;
const int PIN_RECEPTOR_IR = 10;

// Crea una instancia de Rover
Rover miRover(PIN_MOTOR_IZQ_DELANTERO, PIN_MOTOR_IZQ_TRASERO, PIN_MOTOR_DER_DELANTERO, PIN_MOTOR_DER_TRASERO,
              PIN_IR_DELANTERO, PIN_IR_TRASERO, PIN_ULTRASONIDO_ECHO, PIN_ULTRASONIDO_TRIG, PIN_SENSOR_LUZ);

IRrecv receptorIR(PIN_RECEPTOR_IR);  
decode_results resultadosIR;

void setup() {
    // Inicializa la comunicación serie
    Serial.begin(9600);

    // Inicializa el receptor IR
    receptorIR.enableIRIn();
}

void loop() {
    miRover.manejarControlRemoto();
    delay(100);
}

void modoExplorador() {
    Serial.println("Modo Explorador activado");

    miRover.obtenerDistancia();
    if (miRover.obtenerDistancia() > 50) {
        miRover.moverAdelante();
    } else {
        miRover.detener();
        delay(2000);
        miRover.moverAtras();
        delay(500);
        miRover.girarIzquierda();
        delay(2000);
    }
}

void modoInfrarrojo() {
    Serial.println("Modo Infrarrojo activado");

    if (miRover.detectarObstaculo()) {
        // Si hay un obstáculo, detener el rover
        miRover.detener();
        Serial.println("Obstáculo detectado. Deteniendo el rover.");
    } else {
        // Si no hay obstáculos, mover el rover hacia adelante
        miRover.moverAdelante();
        Serial.println("No hay obstáculos. Moviendo el rover hacia adelante.");
    }
    delay(100);
}

void modoSensorLuz() {
    Serial.println("Modo Sensor de Luz activado");
    
    void modoSensorLuz() {
    int intensidadLuz = miRover.obtenerIntensidadLuz();
    if (intensidadLuz < 300) {
        // Si la intensidad de luz es baja, detener el rover
        miRover.detener();
        Serial.println("Niveles bajos de luz. Deteniendo el rover.");
    } else {
        // Si la intensidad de luz es suficiente, mover el rover hacia adelante
        miRover.moverAdelante();
        Serial.println("Suficiente luz. Moviendo el rover hacia adelante.");
    }
    delay(100);
}
}
