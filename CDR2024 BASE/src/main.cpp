#include <Arduino.h>
#include <UniBoardDef.h>
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
// put function declarations here:

SSD1306Wire display(0x3c); 

void setup() {
  Serial.begin(9600);
  pinMode(TIR, INPUT_PULLUP);
  Wire.begin(SDA,SCL);
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);


  Serial.println("Waiting for button press");
  while(digitalRead(TIR)==1){

  }
  Serial.println("Start");
}

void loop() {

  if(digitalRead(TIR)==0){
    display.clear();
    display.drawString(0, 0, "Pressed");
    display.display();
  }else{
    display.clear();
    display.drawString(0, 0, "N.pressed");
    display.display();
  }
  delay(1000);

}

