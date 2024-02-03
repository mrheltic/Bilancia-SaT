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
  lcd.print("Post");

  // Initialize library with data output pin, clock input pin and gain factor.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_offset(-37080.35186363634); 
  scale.set_scale(450.9137756192465432);
  scale.tare(20);
  Serial.print("Setup done");
}

void loop() {
  units = scale.get_units(10);
  if(Serial.available()){
    if(Serial.read() == 'a'){
      Serial.println(units);
    }
  }
}