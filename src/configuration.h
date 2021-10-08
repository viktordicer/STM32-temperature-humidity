
// #define	FOYER
// #define	CHILD1
// #define	CHILD2
// #define	BATH
// #define	TECHNICAL
// #define	HALL
// #define	CHILD3
// #define	BED
// #define	OFFICE
// #define	LARDER
#define	KITCHEN
// #define	LIVING

#define RESET_PIN       PA0  //Reset pin for W5500

#define MQTT_USER       "viktor"
#define MQTT_PASSWORD   "viktor"
const char* mqtt_server = "192.168.0.107";

#define INTERVAL        20*60000 // 15 min delay between publishing


#ifdef FOYER
  #define MQTT_CLIENT_ID  "foyer" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 195};//Foyer room
  uint8_t MAC[6] =          {0x02, 0xA1, 0xA5, 0x03, 0x04, 0x05};
  const char* tempTopic = "sensor/foyer/temperature";
  const char* humTopic = "sensor/foyer/humidity";
#endif

#ifdef CHILD1
  #define MQTT_CLIENT_ID  "child1" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 170};//Child1 room
  uint8_t MAC[6] =          {0x02, 0x63, 0x02, 0x03, 0x04, 0x05};
  const char* tempTopic = "sensor/child1/temperature";
  const char* humTopic = "sensor/child1/humidity";
#endif

#ifdef CHILD2
  #define MQTT_CLIENT_ID  "child2" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 197};//Child2 room
  uint8_t MAC[6] =          {0x02, 0xA1, 0x03, 0x03, 0x04, 0x05};
  const char* tempTopic = "sensor/child2/temperature";
  const char* humTopic = "sensor/child2/humidity";
#endif

#ifdef BATH
  #define MQTT_CLIENT_ID  "bath" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 198};//Bath room
  uint8_t MAC[6] =          {0x02,0xA1,0x04,0x03,0x04,0x05};
  const char* tempTopic = "sensor/bath/temperature";
  const char* humTopic = "sensor/bath/humidity";
#endif

#ifdef TECHNICAL
  #define MQTT_CLIENT_ID  "technical" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 199};//Technical room
  uint8_t MAC[6] =          {0x02,0xA1,0x05,0x03,0x04,0x05};
  const char* tempTopic = "sensor/technical/temperature";
  const char* humTopic = "sensor/technical/humidity";
#endif

#ifdef HALL
  #define MQTT_CLIENT_ID  "hall" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 200};//Hall room
  uint8_t MAC[6] =          {0x02,0xA1,0x06,0x03,0x04,0x05};
  const char* tempTopic = "sensor/hall/temperature";
  const char* humTopic = "sensor/hall/humidity";
#endif

#ifdef CHILD3
  #define MQTT_CLIENT_ID  "child3" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 201};//Child3 room
  uint8_t MAC[6] =          {0x02,0xA1,0x07,0x03,0x04,0x05};
  const char* tempTopic = "sensor/child3/temperature";
  const char* humTopic = "sensor/child3/humidity";
#endif

#ifdef BED
  #define MQTT_CLIENT_ID  "bed" //MQTT id client 
  int IP_ADDRESS[4] =        {192, 168, 0, 202};//Bed room
  uint8_t MAC[6] =          {0x02,0xA1,0x08,0x03,0x04,0x05};
  const char* tempTopic = "sensor/bed/temperature";
  const char* humTopic = "sensor/bed/humidity";
#endif

#ifdef OFFICE
  #define MQTT_CLIENT_ID  "office" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 158};//Office room
  uint8_t MAC[6] =          {0x02,0xA1,0x09,0x03,0x04,0x05};
  const char* tempTopic = "sensor/office/temperature";
  const char* humTopic = "sensor/office/humidity";
#endif

#ifdef LARDER
  #define MQTT_CLIENT_ID  "larder" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 159};//Larder room
  uint8_t MAC[6] =          {0x02,0xA1,0x01,0x04,0x04,0x05};
  const char* tempTopic = "sensor/larder/temperature";
  const char* humTopic = "sensor/larder/humidity";
#endif

#ifdef KITCHEN
  #define MQTT_CLIENT_ID  "kitchen" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 160};//Kitchen room
  uint8_t MAC[6] =          {0x02,0xA1,0x02,0x04,0x04,0x05};
  const char* tempTopic = "sensor/kitchen/temperature";
  const char* humTopic = "sensor/kitchen/humidity";
#endif

#ifdef LIVING
  #define MQTT_CLIENT_ID  "living" //MQTT id client
  int IP_ADDRESS[4] =        {192, 168, 0, 161};//Living room
  uint8_t MAC[6] =          {0x02,0xA1,0x04,0x04,0x04,0x05};
  const char* tempTopic = "sensor/living/temperature";
  const char* humTopic = "sensor/living/humidity";
#endif