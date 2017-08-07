#include <ESP8266WiFi.h>
#include <WiFiManager.h>   // v0.12.0  https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>  // v2.6.0   https://github.com/knolleary/PubSubClient

//include BME280---------------------------------
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

//common define
#define BAUDRATE 115200

//define BME280-----------------------------------
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1001.10) 

Adafruit_BME280 bme; // I2C
float bme_t, bme_h, bme_a, bme_p;

//WIFI
const char* ssid = "*******";            // your ssid
const char* password = "********";       // your password of ssid

//define common
unsigned long delayTime = 15000;

//WIFI Client
WiFiClient wClient;

//function area -------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  initWifi();
  setBme280();
}

void loop() {
  // put your main code here, to run repeatedly:
  getBme280();
  delay(delayTime);
}

//SET function -------------------------------------------------
void setBme280(){
  bool status;

  // default settings
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

//Exec Function --------------------------------------------------
void initWifi() {
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //wifiManager.resetSettings();
  wifiManager.setConfigPortalTimeout(240); // seconds
  //wifiManager.startConfigPortal(WIFI_CONFIG_AP_NAME, WIFI_CONFIG_AP_PW); //start the config portal, without trying to connect first
  wifiManager.autoConnect(ssid, password);
  Serial.println("wifi initialized");
}

void getBme280(){
  //humedity
  bme_h = bme.readHumidity();
  //temperature
  bme_t = bme.readTemperature();
  //altitude
  bme_a = bme.readAltitude(SEALEVELPRESSURE_HPA);
  //pressure
  bme_p = bme.readPressure() / 100.0F;
  
  Serial.print("BME Temperature = ");
  Serial.print(bme_t);
  Serial.print(" *C");
  Serial.print(", BME Humidity = ");
  Serial.print(bme_h);
  Serial.print(" %");
  Serial.print(", BME Pressure = ");
  Serial.print(bme_p);
  Serial.print(" hPa");
  Serial.print(", Approx. Altitude = ");
  Serial.print(bme_a);
  Serial.println(" m");
}

