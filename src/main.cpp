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
float ounces;

// Declaring button for tare
int buttonPin = 4;


void setup() {

  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  Serial.println("LCD initialized");

  // Initialize button
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println("Button initialized");

  // Initialize library with data output pin, clock input pin and gain factor.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("Scale initialized");

  // Raw data reading
  Serial.print("Read: ");
  Serial.print(scale.read());
  Serial.print("  ");
  Serial.print(scale.read_average(20));
  Serial.print("  ");

  // Calibration factor reading
  scale.set_scale(-495);
  Serial.print("Calibration factor: ");
  Serial.print(scale.get_scale());

  // Tare reading
  scale.tare(); //Reset the scale to 0
  Serial.println("Tare initialized");
  Serial.println("Readings:");

}

void loop() {

  // Read the change in weight
  units = scale.get_units(10);
  ounces = units * 0.035274;

  // Print the change in weight
  Serial.print("Weight: ");
  Serial.print(units,5);
  Serial.println(" grams");
  
  

  lcd.setCursor(0, 0);
  lcd.print("Weight: ");
  lcd.print(units);
  lcd.print(" g");


  // Tare the scale
  if (digitalRead(buttonPin) == HIGH) {
    scale.tare();
    Serial.println("Tare");
  }

  // Wait 1 second before reading again
  delay(100);

}