// luces en el tablero
int switchestado = 0;

void setup(){
    pinMode (3, OUTPUT);// LED DE SALIDA ROJO 
    pinMode (4, OUTPUT);// LED DE SALIDA ROJO 
    pinMode (5, OUTPUT);// LED DE SALIDA VERDE
    pinMode (2, INPUT); // BOTON ENTRADA
}

void loop(){
 	switchestado = digitalRead(2);// Si  el  botón esta presionado
  
	if(switchestado == LOW) {   
      digitalWrite(3, HIGH);// LED DE SALIDA ROJO
      digitalWrite(4, LOW);// LED DE SALIDA ROJO 
      digitalWrite(5, LOW);// LED DE SALIDA VERDE
    }else {
      digitalWrite(3, LOW);// LED DE SALIDA ROJO
      digitalWrite(4, LOW);// LED DE SALIDA ROJO 
      digitalWrite(5, HIGH);// LED DE SALIDA VERDE
      delay(250);
      digitalWrite(3, HIGH);// LED DE SALIDA ROJO
      digitalWrite(4, HIGH);// LED DE SALIDA ROJO 
      digitalWrite(5, LOW);// LED DE SALIDA VERDE
      delay(250);
    }
}