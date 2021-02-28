#include <Arduino.h>

void setup(){
}

void loop(){
    int led = LED_BUILTIN;
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);    
}