#include <Arduino.h>
#include "pluviometer.hpp"

#define PLUVIOMETER_PIN (gpio_num_t) 35

Pluviometer *pluviometer;

void setup() {
    Serial.begin(115200); 
    Serial.println("Starting Pluviometer test...");
    
    pluviometer = new Pluviometer(PLUVIOMETER_PIN);
}

void loop() {
    PluviometerInfo reading = pluviometer->read();
    
    Serial.print("Reed Count: ");
    Serial.print(reading.reed_count);
    Serial.print(" | Collected Rain (mm): ");
    Serial.println(reading.collected_rain_mm);

    float collected_volume_ml = reading.collected_rain_mm * (M_PI * (pluviometer->diameter_mm * pluviometer->diameter_mm) / 4.0) / 1000.0;
    Serial.print(" | Collected Volume (ml): "); // V(ml) = A(cm^2) * h(mm) / 10 = A(mm^2) * h(mm) / 1000
    Serial.println(collected_volume_ml);

    delay(1000); // wait 1 second before the next reading
}