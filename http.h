// file include Functions to request Server

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include "Sensor.h" // include lib datas

//Your Domain name with URL path or IP address with path
String local_Api = "http://192.168.0.220:4002";
String  host = "https://cherubin-restefull-api.onrender.com";  // Server URL

String MessageDatas;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5200;
unsigned long timebefore = 0; // time before read flow datas


void saveDatas(String value, int index) {

  switch (index) {
    case 0: {
        //        Serial.write("Status :");
        //        Serial.println(value);
        //MessageDatas += value;
        break;
      };

    case 1: {
        //        Serial.write("Counter datas : ");
        //        Serial.println(value);
        MessageDatas += value;
        break;
      };
    case 2: {
        //        Serial.write("Counter datas : ");
        //        Serial.println(value);
        MessageDatas += "#" + value;
        break;
      };

  }
}



void JsonCovertDatas(String ServerMsg) {
  // json datas Read
  JSONVar myObject = JSON.parse(ServerMsg);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    //Serial.println("Parsing input failed!");
    return;
  }

  // Keys Datas
  JSONVar keys = myObject.keys();
  //Read datas in Application
  for (int i = 0; i < keys.length(); i++) {
    JSONVar value = myObject[keys[i]];
    saveDatas(value, i);
  }

  // send datas and Reset it
    Serial.println(MessageDatas);
  
  //Reset
  MessageDatas = "";
}

void SecureRequest() {

  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    lastTime = millis();
    HTTPClient https;
    WiFiClientSecure client;
    client.setInsecure();  // Use certs, but do not check their authenticity

    // read datas
    readCounterDatas();// read sensor datas
    String url = "/Esp8266?water_01=" + String(Sensor_01.getVolume(),1) + "&water_02=" + String(Sensor_02.getVolume(),1);

    if (https.begin(client, host + url)) {

      int code = https.GET();
      if (code > 0) {
        resetCounterDatas(); // reset counter datas
        JsonCovertDatas(https.getString());
      }
      https.end();
    }
  }
}

void inSecureRequest() {

  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    lastTime = millis();
    HTTPClient http;
    WiFiClient client;

    // read datas
    readCounterDatas();// read sensor datas
    String url = "/Esp8266?water_01=" + String(Sensor_01.getVolume(),1) + "&water_02=" + String(Sensor_02.getVolume(),1);

    if (http.begin(client, local_Api + url)) {

      int code = http.GET();
      if (code > 0) {
        resetCounterDatas(); // reset counter datas
        JsonCovertDatas(http.getString());
      }
      http.end();
    }
  }
}
