#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

// HX711 constructor
HX711 scale;

// LCD constructor
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Weight setup
float calibration_factor = -450;
float units;

// Declaring button for tare
int buttonPin = 4;

void setup() {

  // Initialize Serial Monitor
  Serial.begin(115200);

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
  Serial.println("Readings:");
  Serial.println("");

}

void loop() {

  // Read the change in weight
  units = scale.get_units(10);

  // Print the change in weight
  Serial.print("Weight: ");
  Serial.print(units,5);
  Serial.println(" grams");
  
  // Print the change in weight on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.print(units);
  lcd.print(" g");


  // Tare the scale
  if (digitalRead(buttonPin) == LOW) {
    scale.tare();
    Serial.println("Tare");
  }

  // Wait 100ms before reading again
  delay(100);

}