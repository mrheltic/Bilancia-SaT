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

  // scale.set_offset(-3.504788399999997e+05);
  // scale.set_scale(3.074913939393921e+02);

  // Tare reading
  scale.tare(); //Reset the scale to 0

  Serial.print("Setup done");
}

void loop() {
  if(Serial.available()){
    if(Serial.read() == '\n'){
      // Read the change in weight
      units = scale.read_average(1); //to estimate noise without calibration
      //units = scale.get_units(1); //to estimate noise after calibration
      Serial.println(units, 5);
    }
  }
}