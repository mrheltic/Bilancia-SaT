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

  scale.set_offset(-349933);
  scale.set_scale(395);

  // Tare reading
  scale.tare(); //Reset the scale to 0

  Serial.print("Setup done");
}

void loop() {
  if(Serial.available()){
    if(Serial.read() == '\n'){
      units = scale.get_units(100);
      Serial.println(units, 0);
    }else if(Serial.read() == 't'){
      scale.tare();
    }
  }
}