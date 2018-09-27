//Incluir librerias
#include "LowPower.h"
//Declaracion de los pines de arduino
#define puerta 2
#define bocina 6
#define led 3
#define pot A1
//Declaración de variables
int valorPot = 0;
volatile boolean encender = false;

void setup() {
  //Declaración de reed switch como pin de entrada
  pinMode(puerta, INPUT);
  //Declaración de led como pin de salida
  pinMode(led, OUTPUT);
  //Declaración de buzzer como pin de salida
  pinMode(bocina, OUTPUT);
}

void loop() {
  //Interrupción controlada por la puerta(Reed Switch)
  attachInterrupt(digitalPinToInterrupt(puerta), interrupcion, LOW);
  //Modo SLEEP para consumir el minimo de energia
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  //Salir del sleep
  detachInterrupt(0);

  //Si la interripcion esta activada, seguira entrando en este if
  if(encender){
    //Valor del potenciometro que sirve para controlar el volumen del buzzer
    valorPot = analogRead(pot)/50;
    //Suena el buzzer en base al valor del potenciometro de 10KOhms
    analogWrite(bocina, valorPot);
    //EL led se queda encendido en lo que dura la interrupcion
    digitalWrite(led, HIGH);
    delay(500);
    analogWrite(bocina,0);
    delay(50);   
  }
  //Después de que termine la interrupción la bocina y el led se apagan
  analogWrite(bocina, 0);
  digitalWrite(led, LOW);
}
/*Función para la interrupción, Si la variable esta en false cambia a true para
  realizar lo anterior*/
void interrupcion(){
  encender = !encender;
}
