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
float calibration_factor = 471.42068;
float offset = 429430202;
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
  Serial.println("LCD initialized\n");

  // Initialize button
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("Button initialized\n");

  // Initialize library with data output pin, clock input pin and gain factor.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("Scale initialized\n");

  // Raw data reading
  // Serial.print("Read: ");
  // Serial.print(scale.read());
  // Serial.print("  ");
  // Serial.print(scale.read_average(20));
  // Serial.println("  ");
  // Serial.println("");

  delay(300);

  // Calibration factor reading
  scale.set_scale(calibration_factor);
  Serial.print("Calibration factor: ");
  Serial.println(scale.get_scale());
  Serial.println("");

  scale.set_offset(offset);

  // Tare reading
  scale.tare(); //Reset the scale to 0
  Serial.println("Tare initialized\n");
  Serial.println("Readings:\n");
}

/**
 * The main loop function that runs repeatedly in the program.
 * It reads the change in weight from the scale, prints it to the Serial monitor and LCD,
 * and performs a tare operation if the button is pressed.
 */
void loop() {
  // Read the change in weight
  units = scale.get_units(10);

  if(abs(units) < 0.05){
    units = abs(units);
  }

  // Print the change in weight
  Serial.print("Weight: ");
  Serial.print(units,5);
  Serial.println(" grams");
  
  // Print the change in weight on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.print(units);
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
}
