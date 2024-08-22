#include <IRremote.h>

// Codigos de los botones
#define Boton_1 0xCF30FF00
#define Boton_2 0xE718FF00
#define Boton_3 0xA15EFF00
#define Boton_4 0xF708FF00
#define Boton_5 0xE31CFF00
#define Boton_6 0xA55AFF00
#define Boton_7 0xBD42FF00

const int RECV_PIN = 7; 

int led = 3;

const int relayPin = 2;

void setup() {
  Serial.begin(9600);   
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  pinMode(led, OUTPUT);

  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, LOW);
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Código recibido: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    // Encender y apagar el relay
    if (IrReceiver.decodedIRData.decodedRawData == Boton_1) {
      digitalWrite(relayPin, !digitalRead(relayPin));
      delay(1000);
    }
    // Encender y apagar el led
    if (IrReceiver.decodedIRData.decodedRawData == Boton_2) {
      digitalWrite(led, !digitalRead(led));
    }
    //para encender ambos a la misma vez
    if(IrReceiver.decodedIRData.decodedRawData == Boton_3){
      digitalWrite(relayPin, HIGH);
      digitalWrite(led, HIGH); 
    }
    // para apagar ambos a la misma vez
    if(IrReceiver.decodedIRData.decodedRawData == Boton_4){
      digitalWrite(relayPin, LOW);
      digitalWrite(led, LOW); 
    }
    // para encender led y apagar relay
    if(IrReceiver.decodedIRData.decodedRawData == Boton_5){
      digitalWrite(relayPin, LOW);
      digitalWrite(led, HIGH); 
    }
    // Para apagar led y encender el relay
    if(IrReceiver.decodedIRData.decodedRawData == Boton_6){
      digitalWrite(relayPin, HIGH);
      digitalWrite(led, LOW); 
    }
    // encender ambos y apagar la luz un minuto después de encendida y el ventilador dos minutos después de ser encendido.
    if (IrReceiver.decodedIRData.decodedRawData == Boton_7) {
      digitalWrite(relayPin, HIGH);
      digitalWrite(led, HIGH);

      // Apagar el led despues de 5 segundos
      delay(5000);
      digitalWrite(led, LOW);

      // Apagar el relay despues de 10 segundos
      delay(5000);
      digitalWrite(relayPin, LOW);
    }
    
    IrReceiver.resume();
  }
}
