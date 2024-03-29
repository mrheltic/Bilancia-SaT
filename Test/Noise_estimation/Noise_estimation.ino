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
float units;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Noise");

  // Initialize library with data output pin, clock input pin and gain factor.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_offset(4294929923); 
  scale.set_scale(450.622436);
  scale.tare(20);

  Serial.print("Setup done");
}

void loop() {
  units = scale.get_units(10); //to estimate noise after calibration
  // units = scale.read_average(1); //to estimate noise without calibration
  if(Serial.available()){
    if(Serial.read() == 'a'){
      lcd.clear();
      Serial.println(units);
      lcd.setCursor(0, 0);
      lcd.print(units);
    }
  }
}