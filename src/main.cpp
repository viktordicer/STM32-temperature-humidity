/********************************
  W5500 TO STM32 TYPICAL WIRING
    VCC ----> 5V
    GND ----> GND
    CS  ----> PA4
    SCK ----> PA5
    SO  ----> PA6
    SI  ----> PA7
    RST ----> PA0

  # TEMPERATURE AND HUMIDITY => HDC1080 - I2C
    GND ---> GND
    SCL ---> PB6
    SDA ---> PB7
    VCC ---> 3.3V

  # CO2 AND TVOC => CJMCU-811 CCS811
    VCC ---> 3.3V
    GND ---> GND
    SCL ---> PB6
    SDA ---> PB7
    WAK ---> GND

*********************************/


#include <Arduino.h>
#include <Ethernet.h>  //ETHERNET LIBRARY
#include "PubSubClient.h" //MQTT LIBRARY
#include "ClosedCube_HDC1080.h" // HDC1080
#include "configuration.h"

// DEBUG MODE DEFINE - in debug mode serial print is on
//#define DEBUG

EthernetClient ethClient;
IPAddress ip(IP_ADDRESS[0], IP_ADDRESS[1], IP_ADDRESS[2], IP_ADDRESS[3]);    
PubSubClient mqttClient(ethClient);
ClosedCube_HDC1080 hdc1080; //temperature sensor

//Sensor varialbles
char temp[10];
char hum[10];

// Methodes
void sendData();     
void resetEthernet();
void serialPrint(String message);

void setup() {
  #ifdef DEBUG
    Serial.begin(57600);
    delay(4000);
    Serial.println("STM32 starting...");
    Serial.println("Debug mode");
  #endif 

  //Initialize hdc1080
  hdc1080.begin(0x40);
}

void loop() {

  //Read temperature end humidity
  dtostrf(hdc1080.readTemperature(),5,1,temp);
  dtostrf(hdc1080.readHumidity(),3,0,hum);


  sendData();
  delay(INTERVAL);
}

void sendData() {
  resetEthernet();
// setup mqtt client
  int connectionAtempt = 1;
  if(!mqttClient.connected()){
    while (!mqttClient.connected()) {
      //after 3 atempts reset W5500
      if(connectionAtempt > 3){
        resetEthernet();
        connectionAtempt = 1;
      }
      Ethernet.maintain();
      serialPrint("Attempting MQTT connection...");

      if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD )) {
        //Publish MQTT
        serialPrint("connected");
        mqttClient.publish(tempTopic,temp);
        mqttClient.publish(humTopic,hum);
        
      } else {
        serialPrint("failed, rc=");
        serialPrint(" try again in 2 seconds");
        
        delay(2000);
        connectionAtempt ++;
      }
    }
  }
  //mqttClient.loop();
  delay(200);
  mqttClient.disconnect();
  //turn off W5500
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
}

void resetEthernet() {
  //Define reset pin for W5500
  serialPrint("Reseting ethernet adapter");
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN,HIGH);
  delay(100);
  pinMode(RESET_PIN, INPUT);
  delay(1500);
  serialPrint("Initialize ethernet");
  Ethernet.begin(MAC,ip);

  //delay with ethernet maintain
  for (int i = 0; i <= 5; i++) {
    delay(200);
    Ethernet.maintain();
  }
  
  mqttClient.setServer(mqtt_server,1883);
}

// Serial print if debug mode is on
void serialPrint(String message){
  #ifdef DEBUG
    Serial.println(message);
  #endif
}