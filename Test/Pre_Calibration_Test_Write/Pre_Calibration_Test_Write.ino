#include <HX711.h>

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 3;

// HX711 constructor
HX711 scale;

// Weight setup
float units;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize library with data output pin, clock input pin and gain factor.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Tare reading
  scale.tare(); //Reset the scale to 0

  scale.set_offset(0); //1st test
  scale.set_scale(1);

  Serial.print("Setup done");
}

void loop() {
  if(Serial.available()){
    if(Serial.read() == '\n'){
      // Read the change in weight
      units = scale.get_units(50); //average of 50 raw measures
      Serial.println(units);
    }
  }
}