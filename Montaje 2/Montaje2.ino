// Encender codigo

int estado = 0;
int salida = 0; // Si salida vale 1 enciende, si vale 0 se apaga
int anterior = 0;

void setup(){
    pinMode(9, INPUT); // Boton de entrada
    pinMode(4, OUTPUT);// Led de salida
}

void loop(){
	estado = digitalRead(9); // Leer el estado del boton
  
  	if((estado == HIGH) && anterior == LOW){
  		salida = 1 - salida;
    }
  
 	anterior = estado;
  
  	if(salida == 1){
    	digitalWrite(4, HIGH); // Encender el led
    }else{
    	digitalWrite(4, LOW);  // Apagar el led
    }
}
