#include <HX711.h> // Biblioteca HX711
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// Definición de pines
#define DT 4  // Pin de datos del HX711
#define SCK 5 // Pin de reloj del HX711

// Crear una instancia del objeto HX711
HX711 balanza;

// Factor de calibración (ajústalo según tu configuración)
float factorCalibracion = 229.28; // Valor de ejemplo, ajusta según tu sensor

void setup() {
  Serial.begin(9600); // Inicializar comunicación serial
  Serial.println("Iniciando...");
  
  // Configurar pines y calibración inicial
  balanza.begin(DT, SCK); 
  balanza.set_scale(factorCalibracion); // Configurar factor de calibración
  balanza.tare(); // Establecer la tara inicial (0 peso)
  
  Serial.println("Sensor listo. Coloca peso para medir.");
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("BAM Technologies");  
  lcd.setCursor(2,2);
  lcd.print("Medidor de peso");
}

void loop() {
  if (balanza.is_ready()) { // Verificar si el sensor está listo
    float peso = balanza.get_units(10); // Leer 10 valores promedio
    if(peso < 0) {
      peso = peso*(-1);
    }
    if(peso >= 1000) {
      lcd.setCursor(0,3);
      lcd.print("Peso: ");
      lcd.print(peso/1000);
      lcd.print("  kg    ");  
    }
    else {
      lcd.setCursor(0,3);
      lcd.print("Peso: ");
      lcd.print(peso,0);
      lcd.print("  g    ");  
    }
    Serial.print("Peso: ");
    Serial.print(peso);
    Serial.println(" g"); // Mostrar el peso en gramos
    
  } else {
    Serial.println("Error: Sensor no conectado.");
  }
  
  delay(100); // Leer cada segundo
}
