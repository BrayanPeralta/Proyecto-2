#include <Arduino.h>

#define LED1 2 // definicion de pines para los LEDs
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6  

#define SWITCH1 7 // definicion de pines para los switchs
#define SWITCH2 8
#define SWITCH3 9
#define SWITCH4 10  

bool blinkMode = false; // Define el estado de los LEDs (parapadeo o modo estatico)

void setup() {
  Serial.begin(9600); // inicia la comunicacion serial 
  pinMode(LED1, OUTPUT);// Permite encender o apagar cada LEDs, cofigurando los LEDs como salida 
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  pinMode(SWITCH1, INPUT); // Permite leer el estado en que se encuentran los Switchs, configurando como la entrada 
  pinMode(SWITCH2, INPUT);
  pinMode(SWITCH3, INPUT);
  pinMode(SWITCH4, INPUT);  
}

void loop() {
  int state1 = digitalRead(SWITCH1);// Es un bucle indefinido que se encarga de leer el estado de los switchs, si estan en ON o OFF
  int state2 = digitalRead(SWITCH2);
  int state3 = digitalRead(SWITCH3);
  int state4 = digitalRead(SWITCH4); 

  Serial.print("SWITCH1: "); Serial.print(state1); // imprime cada estado o caso de los switchs 
  Serial.print(" | SWITCH2: "); Serial.print(state2);
  Serial.print(" | SWITCH3: "); Serial.print(state3);
  Serial.print(" | SWITCH4 (parpadeo): "); Serial.println(state4); 

  if (state4 == HIGH) {  // lee el estado del Switch 4, si está encendido, activa el parpadeo
    blinkMode = true; // activa el parpadeo 
    Serial.println("Modo Parpadeo ACTIVADO");
  } else {
    blinkMode = false; // esta apagado desactivando el parpadeo 
    Serial.println("Modo Parpadeo DESACTIVADO");
  }

  if (blinkMode) {
    Serial.println("Encendiendo TODOS los LEDs, para parpadear");
    digitalWrite(LED1, HIGH);// Si el el Switch4 esta activado se encienden los leds 
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    delay(700); // tiempo de espera 

    Serial.println("Apagando TODOS los LEDs");
    digitalWrite(LED1, LOW);// se apagan los leds 
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    digitalWrite(LED5, LOW);
    delay(700); // tiempo de espera 
  } else {
    // Control individual de los LEDs con los switches normales cuando el switch4 esta apagado 
    digitalWrite(LED1, state1);
    digitalWrite(LED2, state2);
    digitalWrite(LED3, state3);
    
    // LED4 ya no se controla con un switch, ahora parpadea con el modo
    // LED5 se enciende solo si todos los switches individuales están activados
    digitalWrite(LED5, (state1 && state2 && state3) ? HIGH : LOW);

    Serial.print("LED1: "); Serial.print(state1);
    Serial.print(" | LED2: "); Serial.print(state2);
    Serial.print(" | LED3: "); Serial.print(state3);
    
  }
  delay(4000);  // retardo para que el monitor serial no se sature 
}