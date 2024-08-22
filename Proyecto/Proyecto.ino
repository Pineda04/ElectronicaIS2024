#include <LiquidCrystal.h>

// Configuración del LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Definición de las letras en Morse
String alfabetoMorse[36] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", 
  "-.--", "--..", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

const char alfabeto[36] = "abcdefghijklmnopqrstuvwxyz0123456789";

// Pines para el LED RGB y el buzzer
int ledRojo = 14;
int ledVerde = 15;
int ledAzul = 16;
int buzzerPin = 9;

// Funciones para configurar pines
void setup() {
  lcd.begin(16, 2);           
  Serial.begin(9600);         
  
  pinMode(ledRojo, OUTPUT);    
  pinMode(ledVerde, OUTPUT);  
  pinMode(ledAzul, OUTPUT);   
  pinMode(buzzerPin, OUTPUT);
  
  randomSeed(analogRead(0));  // Inicializa la semilla para números aleatorios
  
  lcd.print("Opcion:"); 
  
  imprimirMenu();
}

void loop() {
  if (Serial.available() > 0) {
    String entrada = Serial.readStringUntil('\n');
    entrada.trim(); // Eliminar espacios en blanco al principio y al final

    if (entrada == "1") {
      mostrarMenu("TEXTO");
    } else if (entrada == "2") {
      mostrarMenu("MORSE");
    } else if (entrada == "3") {
      practicarMorse();
    } else if (entrada == "4") {
      mostrarMenu("BIN");
    } else if (entrada == "5") {
      mostrarMenu("OCT");
    } else if (entrada == "6") {
      mostrarMenu("HEX");
    } else {
      mostrarError("Opcion no valida");
      imprimirMenu();
    }
    
    delay(200);
  }
}

void mostrarMenu(String modo) {
  lcd.clear();
  lcd.print("Ingresa la info:");
  
  Serial.println("Por favor, ingresa la información:");

  // Esperar a que se ingrese la información
  while (!Serial.available()) {

  }

  String entrada = Serial.readStringUntil('\n');
  entrada.trim(); // Eliminar espacios en blanco al principio y al final

  if (modo == "TEXTO") {
    manejarTexto(entrada);
  } else if (modo == "MORSE") {
    manejarMorse(entrada);
  } else if (modo == "BIN") {
    manejarBinario(entrada);
  } else if (modo == "OCT") {
    manejarOctal(entrada);
  } else if (modo == "HEX") {
    manejarHex(entrada);
  }

  imprimirMenu();
}

// Manejar entrada de texto
void manejarTexto(String texto) {
  String codigoMorse = textoAMorse(texto);
  lcd.clear();
  lcd.print("Texto recibido");
  lcd.setCursor(0, 1);
  lcd.print(codigoMorse);

  Serial.println("Texto recibido:");
  Serial.println(texto);
  Serial.println("Código Morse:");
  Serial.println(codigoMorse);

  morseALedYBuzzer(codigoMorse);
}

// Manejar entrada de código Morse
void manejarMorse(String morse) {
  String textoTraducido = morseATexto(morse);
  lcd.clear();
  lcd.print("Morse recibido");
  lcd.setCursor(0, 1);
  lcd.print(textoTraducido);

  Serial.println("Código Morse recibido:");
  Serial.println(morse);
  Serial.println("Texto traducido:");
  Serial.println(textoTraducido);
}

// Convertir texto a binario
void manejarBinario(String texto) {
  String codigoBinario = textoABinario(texto);
  lcd.clear();
  lcd.print("Texto a Binario");
  lcd.setCursor(0, 1);
  lcd.print(codigoBinario);

  Serial.println("Texto recibido:");
  Serial.println(texto);
  Serial.println("Código Binario:");
  Serial.println(codigoBinario);
}

// Convertir texto a octal
void manejarOctal(String texto) {
  String codigoOctal = textoAOctal(texto);
  lcd.clear();
  lcd.print("Texto a Octal");
  lcd.setCursor(0, 1);
  lcd.print(codigoOctal);

  Serial.println("Texto recibido:");
  Serial.println(texto);
  Serial.println("Código Octal:");
  Serial.println(codigoOctal);
}

// Convertir texto a hexadecimal
void manejarHex(String texto) {
  String codigoHex = textoAHex(texto);
  lcd.clear();
  lcd.print("Texto a Hex");
  lcd.setCursor(0, 1);
  lcd.print(codigoHex);

  Serial.println("Texto recibido:");
  Serial.println(texto);
  Serial.println("Código Hexadecimal:");
  Serial.println(codigoHex);
}

// Convertir texto a Binario
String textoABinario(String texto) {
  String codigoBinario = "";
  
  for (int i = 0; i < texto.length(); i++) {
    char c = texto[i];
    String binario = "";
    for (int j = 7; j >= 0; j--) {
      binario += bitRead(c, j) ? '1' : '0';
    }
    codigoBinario += binario + " ";
  }
  
  return codigoBinario;
}

// Convertir texto a Octal
String textoAOctal(String texto) {
  String codigoOctal = "";
  
  for (int i = 0; i < texto.length(); i++) {
    char c = texto[i];
    codigoOctal += String(c, OCT) + " ";
  }
  
  return codigoOctal;
}

// Convertir texto a Hexadecimal
String textoAHex(String texto) {
  String codigoHex = "";
  
  for (int i = 0; i < texto.length(); i++) {
    char c = texto[i];
    codigoHex += String(c, HEX) + " ";
  }
  
  return codigoHex;
}

// Mostrar mensaje de error en el LCD
void mostrarError(String mensaje) {
  lcd.clear();
  lcd.print(mensaje);
}

// Convertir texto a Morse
String textoAMorse(String texto) {
  texto.toLowerCase();
  String codigoMorse = "";
  
  for (int i = 0; i < texto.length(); i++) {
    char c = texto[i];
    int indice = obtenerIndice(c);
    
    if (indice >= 0) {
      codigoMorse += alfabetoMorse[indice] + " ";
    } else if (c == ' ') {
      codigoMorse += "/ ";
    }
  }
  
  return codigoMorse;
}

// Convertir Morse a texto
String morseATexto(String morse) {
  String texto = "";
  morse += " ";
  
  int inicio = 0;
  int fin = morse.indexOf(' ', inicio);
  
  while (fin != -1) {
    String codigo = morse.substring(inicio, fin);
    int indice = obtenerIndiceMorse(codigo);
    
    if (codigo == "/") {
      texto += " ";
    } else if (indice >= 0) {
      texto += alfabeto[indice];
    }
    
    inicio = fin + 1;
    fin = morse.indexOf(' ', inicio);
  }
  
  return texto;
}

// Obtener el índice del alfabeto para una letra o dígito
int obtenerIndice(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a';
  } else if (c >= '0' && c <= '9') {
    return c - '0' + 26;
  }
  return -1;
}

// Obtener el índice del alfabeto para un código Morse
int obtenerIndiceMorse(String codigo) {
  for (int i = 0; i < 36; i++) {
    if (codigo == alfabetoMorse[i]) {
      return i;
    }
  }
  return -1;
}

// Convertir código Morse a LED y buzzer
void morseALedYBuzzer(String codigoMorse) {
  for (int i = 0; i < codigoMorse.length(); i++) {
    char c = codigoMorse[i];
    
    if (c == '.') {
      mostrarPunto();
    } else if (c == '-') {
      mostrarRaya();
    } else if (c == ' ') {
      delay(400);
    } else if (c == '/') {
      delay(600);
    }
  }
}

// Mostrar un punto en el LED y buzzer
void mostrarPunto() {
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledAzul, HIGH); 
  tone(buzzerPin, 1000);
  delay(200);
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledAzul, LOW);
  noTone(buzzerPin);
  delay(200);
}

// Mostrar una raya en el LED y buzzer
void mostrarRaya() {
  digitalWrite(ledRojo, HIGH);
  digitalWrite(ledAzul, HIGH);
  tone(buzzerPin, 1000);
  delay(600);
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledAzul, LOW);
  noTone(buzzerPin);
  delay(200);
}

// Generar una letra aleatoria para practicar
char generarLetraAleatoria() {
  int indice = random(36);
  return alfabeto[indice];
}

// Convertir una letra a código Morse
String letraAMorse(char letra) {
  int indice = strchr(alfabeto, letra) - alfabeto;
  return alfabetoMorse[indice];
}

// Mostrar una letra aleatoria en el LCD para practicar
void practicarMorse() {
  char letraAleatoria = generarLetraAleatoria();
  String morseAleatorio = letraAMorse(letraAleatoria);
  
  lcd.clear();
  lcd.print("Practica:");
  lcd.setCursor(0, 1);
  lcd.print(morseAleatorio);
  
  Serial.println("Letra en Morse generada: " + morseAleatorio);
  Serial.println("Ingrese un caracter:");
  
  unsigned long tiempoInicio = millis();
  bool correcto = false;
  
  while (millis() - tiempoInicio < 20000) {
    if (Serial.available() > 0) {
      String entradaUsuario = Serial.readStringUntil('\n');
      entradaUsuario.trim();

      if (entradaUsuario.equalsIgnoreCase(String(letraAleatoria))) {
        correcto = true;
        break;
      }
      // El usuario solo tiene una oportunidad para adivinar
      else {
        break;
      }
    }
    
    delay(100);
  }

  if (correcto) {
    mostrarResultado("¡Felicidades!", ledVerde);
  } else {
    String resultado = "Perdiste, era " + String(letraAleatoria);
    Serial.println(resultado);
    mostrarResultado(resultado, ledRojo);
  }

  imprimirMenu();
}

// Mostrar el resultado de la práctica y configurar el LED
void mostrarResultado(String mensaje, int colorLed) {
  lcd.clear();
  lcd.print(mensaje);
  
  // Configurar el LED correspondiente
  digitalWrite(ledRojo, colorLed == ledRojo ? HIGH : LOW);
  digitalWrite(ledVerde, colorLed == ledVerde ? HIGH : LOW);
  digitalWrite(ledAzul, colorLed == ledAzul ? HIGH : LOW);
  
  delay(4000);
  
  // Apagar todos los LEDs
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAzul, LOW);
  
  lcd.clear();
  lcd.print("Opcion:");
}

// Mostrar el menú en el monitor serial
void imprimirMenu() {
  Serial.println("\nSelecciona una opción:");
  Serial.println("1 - Convertir texto a Morse");
  Serial.println("2 - Convertir Morse a texto");
  Serial.println("3 - Practicar Morse");
  Serial.println("4 - Convertir texto a Binario");
  Serial.println("5 - Convertir texto a Octal");
  Serial.println("6 - Convertir texto a Hexadecimal");
}
