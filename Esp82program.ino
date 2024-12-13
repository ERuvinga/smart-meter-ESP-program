/*
   Esp Client
*/
#include "http.h"

const char* ssid = "smart_M";
const char* password = "SM_1234@";

// define sensor datas
void IRAM_ATTR count_01()
{
     Sensor_01.count();
}
void IRAM_ATTR count_02()
{
    Sensor_02.count();
}

void setup() {
  // setup libs
  Sensor_01.begin(count_01);
  Sensor_02.begin(count_02);
  
  Serial.begin(57600);

  WiFi.begin(ssid, password);
  //Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
//  Serial.println("");
//  Serial.print("Connected to WiFi network with IP Address: ");
//  Serial.println(WiFi.localIP());

}

void loop() {
  SecureRequest();
}
