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


EthernetClient ethClient;
PubSubClient mqttClient(ethClient);
ClosedCube_HDC1080 hdc1080; //temperature sensor


//Objects

//Variables

#define RESET_PIN       PA0  //Reset pin for W5500

#define MQTT_CLIENT_ID  "child3" //MQTT id client
#define MQTT_USER       "viktor"
#define MQTT_PASSWORD   "viktor"

#define INTERVAL        20*60000 // 15 min delay between publishing

//IPAddress ip(192, 168, 0, 195); //Foyer room
//IPAddress ip(192, 168, 0, 170); //Child1 room196
//IPAddress ip(192, 168, 0, 197); //Child2 room
//IPAddress ip(192, 168, 0, 198); //Bath room
//IPAddress ip(192, 168, 0, 199); //Technical room
//IPAddress ip(192, 168, 0, 200); //Hall room
IPAddress ip(192, 168, 0, 201); //Child3 room
//IPAddress ip(192, 168, 0, 202); //Bed room
//IPAddress ip(192, 168, 0, 158); //Office room
//IPAddress ip(192, 168, 0, 159); //Larder room
//IPAddress ip(192, 168, 0, 160); //Kitchen room
//IPAddress ip(192, 168, 0, 161); //Living room 


//uint8_t mac[6] = {0x02,0xA1,0x02,0x03,0x04,0x05}; //Foyer room
//uint8_t mac[6] = {0x02,0x63,0x02,0x03,0x04,0x05}; //Child1 room
//uint8_t mac[6] = {0x02,0xA1,0x03,0x03,0x04,0x05}; //Child2 room
//uint8_t mac[6] = {0x02,0xA1,0x04,0x03,0x04,0x05}; //Bath room
//uint8_t mac[6] = {0x02,0xA1,0x05,0x03,0x04,0x05}; //Technical room
//uint8_t mac[6] = {0x02,0xA1,0x06,0x03,0x04,0x05}; //Hall room
uint8_t mac[6] = {0x02,0xA1,0x07,0x03,0x04,0x05}; //Child3 room
//uint8_t mac[6] = {0x02,0xA1,0x08,0x03,0x04,0x05}; //Bed room
//uint8_t mac[6] = {0x02,0xA1,0x09,0x03,0x04,0x05}; //Office room
//uint8_t mac[6] = {0x02,0xA1,0x01,0x04,0x04,0x05}; //Larder room
//uint8_t mac[6] = {0x02,0xA1,0x02,0x04,0x04,0x05}; //Kitchen room
//uint8_t mac[6] = {0x02,0xA1,0x04,0x04,0x04,0x05}; //Living room

const char* mqtt_server = "192.168.0.107";

//Sensor varialbles
char temp[10];
char hum[10];

//MQTT topics
const char* tempTopic = "sensor/child3/temperature";
const char* humTopic = "sensor/child3/humidity";


void sendData();     
void resetEthernet();

//////////////////////// SETUP ///////////////////////
void setup() {
  // setup serial communication
  Serial.begin(57600);
  Serial.println("Starting...");

  //Initialize hdc1080
  hdc1080.begin(0x40);
}

//////////////////////// LOOP  ///////////////////////
void loop() {

  //Read temperature end humidity
  dtostrf(hdc1080.readTemperature(),5,1,temp);
  dtostrf(hdc1080.readHumidity(),5,1,hum);


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
      Serial.println("Attempting MQTT connection...");
      // Attempt to connect
      Serial.print("IP address: ");
      Serial.println(Ethernet.localIP());

      if (mqttClient.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD )) {
        //Publish MQTT
        Serial.println("connected");
        mqttClient.publish(tempTopic,temp);
        mqttClient.publish(humTopic,hum);
        
      } else {
        Serial.println("failed, rc=");
        Serial.println(mqttClient.state());
        Serial.println(" try again in 2 seconds");
        
        delay(2000);
        Serial.print("Connection atempt: "); 
        Serial.println(connectionAtempt);

        connectionAtempt ++;
      }
    }
  }
  //mqttClient.loop();
  delay(200);
  Serial.println("Connected to the mqtt");
  mqttClient.disconnect();
  delay(200);
  Serial.println("Client has stoped");
  delay(200);
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  Serial.println("Ethernet adapter has turned off");
}

void resetEthernet() {
  //Define reset pin for W5500
  Serial.println("Reseting ethernet adapter");
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
  delay(100);
  digitalWrite(RESET_PIN,HIGH);
  delay(100);
  pinMode(RESET_PIN, INPUT);
  delay(1500);
  Serial.println("Initialize ethernet");
  Ethernet.begin(mac,ip);

  //delay with ethernet maintain
  for (int i = 0; i <= 5; i++) {
    delay(200);
    Ethernet.maintain();
  }
  
  mqttClient.setServer(mqtt_server,1883);
  Serial.println(Ethernet.localIP());
}