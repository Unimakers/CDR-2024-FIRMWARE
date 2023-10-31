#include <Arduino.h>
#include <UniBoardDef.h>

// put function declarations here:

void setup() {
  Serial.begin(9600);
  pinMode(TIR, INPUT_PULLUP);
}

void loop() {
  Serial.println("Bonjour Monde");  
  if(digitalRead(TIR)==0){
    Serial.println("Pressed");
  }else{
    Serial.println("Not pressed");
  }
  delay(1000);
}

