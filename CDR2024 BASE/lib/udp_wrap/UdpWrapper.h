#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;
char packetBuffer[255];
unsigned int localPort = 9999;
const char *ssid = "MakerSpace - UniFi";
const char *password = "unimakers";


void SendInfo(int A);
void SendPolar();

void UDP_init(){

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(F("."));
  }
  udp.begin(localPort);
  Serial.printf("UDP Client : %s:%i \n", WiFi.localIP().toString().c_str(), localPort);


}

void UDPSendInfo(int A)
{
  udp.beginPacket("172.16.4.143", localPort);
  udp.printf("%i", A);
  udp.printf("\r\n");
  udp.endPacket();
}

void UDPSendPolar(float Y)
{ static long previousMillis = 0;

  if(millis() - previousMillis > 1000){
      Serial.println("Envoie");
      udp.beginPacket("172.16.4.143", localPort);
      udp.printf("Y : %.2f", Y);
      udp.endPacket(); 
      previousMillis = millis();
  }

}