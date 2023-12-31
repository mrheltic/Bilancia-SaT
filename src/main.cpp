/***************************************************
 * Bilancia SaT - Weight Measurement
 *
 * Contributors:
 * - Vincenzo Pio Florio
 * - Francesco Stasi
 * - Simona Vatinno
 * - Davide Tonti
 * - Giovanni Zito
 *
 * This project utilizes an HX711 load cell
 * amplifier, an LCD display, and a tare button to
 * create a weighing system. The program continuously
 * reads the weight and displays it on both the Serial
 * Monitor and the LCD screen. The tare button allows
 * for resetting the scale to zero.
 ***************************************************/

#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 3;

// HX711 constructor
HX711 scale;

// LCD constructor
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Weight setup
float calibration_factor = -450; //Calculated based on known weight
float units;

// Declaring button for tare
int buttonPin = 5;

void setup() {

  // Initialize Serial Monitor
  Serial.begin(115200);

  // Print contributors
  Serial.println("-------------------------------");
  Serial.print("Bilancia SaT - Gruppo 4\n");
  Serial.println("-------------------------------");
  Serial.println("Contributors:");
  Serial.println("- Vincenzo Pio Florio");
  Serial.println("- Francesco Stasi");
  Serial.println("- Simona Vatinno");
  Serial.println("- Davide Tonti");
  Serial.println("- Giovanni Zito");
  Serial.println("-------------------------------");

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  Serial.println("LCD initialized");
  Serial.println("");

  // Initialize button
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("Button initialized");
  Serial.println("");

  // Initialize library with data output pin, clock input pin and gain factor.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("Scale initialized");
  Serial.println("");

  // Raw data reading
  Serial.print("Read: ");
  Serial.print(scale.read());
  Serial.print("  ");
  Serial.print(scale.read_average(20));
  Serial.println("  ");
  Serial.println("");

  // Calibration factor reading
  scale.set_scale(calibration_factor);
  Serial.print("Calibration factor: ");
  Serial.println(scale.get_scale());
  Serial.println("");

  // Tare reading
  scale.tare(); //Reset the scale to 0
  Serial.println("Tare initialized");
  Serial.println("");
  Serial.println("Readings:");
  Serial.println("");

}

void loop() {

  // Read the change in weight
  units = scale.get_units(10);

  // Print the change in weight
  Serial.print("Weight: ");
  Serial.print(units*(-1),5);
  Serial.println(" grams");
  
  // Print the change in weight on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.print(units*(-1),1);
  lcd.print(" g");
  lcd.setCursor(0, 1);
  lcd.print("      ");


  // Tare the scale
  if (digitalRead(buttonPin) == HIGH) {
    scale.tare();
    Serial.println("Tare");
    lcd.setCursor(0, 1);
    lcd.print("Tare");
  }

  // Wait 100ms before reading again
  delay(100);

}