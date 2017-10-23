/* IoT Car
// Measures distance to car in front
// Led Indicator:
// Green - Safe
// Blue - Optimal
// Red - Too Close
 */
 /************************* Includes *********************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <NewPing.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

/************************* Constants *********************************/

// WiFi Access Point Config
#define WLAN_SSID       "YOUR_WIFI_NAME_HERE" //WLAN SSID
#define WLAN_PASS       "YOUR_WIFI_PASSWORD_HERE" //WLAN Password

// MQTT Connection Config
const char* mqtt_server = "MQTT_SERVER_IP_ADDRESS_HERE"; // MQTT Server IP Address
#define MQTT_PORT  1883 // MQTT Server port number, use 8883 for SSL

// HC-SR04 Ultrasonic Distance Measuring Module Config
#define TRIGGER_PIN 4 // Pin assignment for HC-SR04 sensor module Trigger
#define ECHO_PIN 5 // Pin assignment for HC-SR04 sensor module Echo
#define MAX_DISTANCE 500 // Max distance (cm) for the module to register
#define PING_DELAY 20 // Time delay befre (re)sending ping

// L298N Motor Driver Module Config
#define AUTO_DISTANCE true //determines if you use motor control or not
#define FWD_PIN 0 // Pin assignment for Forward motor direction
#define BWD_PIN 2 // Pin assignment for Backward motor direction
#define PWM_PIN 16 // Pin assignment for Motor Pulse

// LED Warning Lights Config
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE
#define RED_PIN 14 // Pin assignment for Red LED
#define GREEN_PIN 13 // Pin assignment for Green LED
#define BLUE_PIN 12 // Pin assignment for Blue LED


/************************* Runtime Parameters *********************************/
double optimalDist = 10; // optimal distance
double optimalFactor = 1; // optimal distance correction factor
double correctedOptimalDist;
int minSpeed = 500;
int maxSpeed = 750;
int slowdownPoint = 10;
int margin = 2; // margin for optimal distance
unsigned int distance = 0; //value for measured distance
String distState;
String sID;
char output[256];
String topicInput = "device/";
String topicOutput = "flogo/device/";
char pubTopic[256];

/************************* Initalizations *********************************/

// Instantiate WiFi Client
WiFiClient espClient;
//WiFiClientSecure client;
PubSubClient client(espClient);

// Instantiate Ultrasonic Distance Measuring Module
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


/************************* General Setup Routine *********************************/

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  sID = WiFi.macAddress();
  Serial.println("Mac address: "); Serial.println(sID);

  //Setup MQTT topics
  topicInput = topicInput + sID;
  topicOutput = topicOutput + sID + "/distance";
  Serial.print("Input Topic: "); Serial.println(topicInput);
  Serial.print("Output Topic: "); Serial.println(topicOutput);
  int str_len = topicOutput.length() + 1;
  topicOutput.toCharArray(pubTopic, str_len);
  client.setServer(mqtt_server, MQTT_PORT);
  client.setCallback(callback);

  //initialize LED settings
  pinMode(RED_PIN,OUTPUT);
  pinMode(GREEN_PIN,OUTPUT);
  pinMode(BLUE_PIN,OUTPUT);

  // initialize motor settings
  pinMode(PWM_PIN, OUTPUT); // declares motor pin as output
  pinMode(FWD_PIN, OUTPUT); // decrales motor forward pin as output
  pinMode(BWD_PIN, OUTPUT); // decrales motor backward pin as output
  digitalWrite(FWD_PIN, LOW);  // forward motor off
  digitalWrite(BWD_PIN, LOW);  // backward motor off
}

void loop() {
   if (!client.connected()) {
     reconnect();
   }
   client.loop();

   distance = sonar.ping_cm();
   Serial.print(distance);
   Serial.println(" cm");
   correctedOptimalDist = optimalDist * optimalFactor;
   if ((distance != 0) and (distance < correctedOptimalDist))
    {
     tooClose();
     if (AUTO_DISTANCE) {
       dropBackToOptimal(correctedOptimalDist);
     }
    } else
    {
      if ((distance >= correctedOptimalDist) and (distance <= correctedOptimalDist + margin))
       {
        optimalDistance();
       } else
       {
        if ((distance == 0) or (distance > correctedOptimalDist))
         {
          safeDistance();
          if (AUTO_DISTANCE) {
            catchUpToOptimal(correctedOptimalDist);
          }
         }
       }
    }
  // Construct JSON Data
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& flogoData = jsonBuffer.createObject();
  flogoData["deviceID"]=sID;
  flogoData["distance"]=distance;
  flogoData["distState"]=distState;
  flogoData.printTo(output, sizeof(output));
  // Publish Distance
  Serial.print(F("\nSending Data: "));
  Serial.print(output);
  client.publish(pubTopic, output);
  delay(500);
}

/************************* Functions *********************************/

// Callback for receiving distance factor on MQTT
void devicedatacallback(double x) {
  Serial.print("Received new optimal distance correction factor: ");
  Serial.println(x);
  optimalFactor = x;
}

// Function to make the car move backward until a certain distance is reached
void dropBackToOptimal(int optimal)
{
  Serial.println("Too close, dropping back to " + String(optimal) + "." );
  digitalWrite(BWD_PIN, HIGH);  // Run motor in backwards direction
  int dist = sonar.ping_cm();
  Serial.println ("Distance is now: " + String(dist));
  int calcSpeed =  maxSpeed;
  double speedBase = 1;
  double speedFactor = 1;
  analogWrite(PWM_PIN, calcSpeed);  // Initialize the speed as per defined value
  while(dist < optimal)
  {
    delay (PING_DELAY);
    if (dist > optimal - slowdownPoint)
    {
      speedBase = optimal - dist;
      speedFactor = speedBase / slowdownPoint;
      calcSpeed = (speedFactor * (maxSpeed - minSpeed)) + minSpeed;
      Serial.println ("Distance is now: " + String(dist));
      Serial.println ("calcSpeed is now: " + String(calcSpeed));
      analogWrite(PWM_PIN, calcSpeed);
    }
    dist = sonar.ping_cm();
    while (dist == 0)
    {
       delay (PING_DELAY);
       Serial.println("-- missed echo --");
       dist = sonar.ping_cm();
    }
  }
  digitalWrite(BWD_PIN, LOW);  // Stops Motor
  Serial.println("Drop back complete.");
}

// Function to make the car move forward until a certain distance is reached
void catchUpToOptimal(int optimal)
{
  Serial.println("Too far, catching up to " + String(optimal) + "." );
  digitalWrite(FWD_PIN, HIGH);  // Run motor in backwards direction
  int dist = sonar.ping_cm();
  Serial.println ("Distance is now: " + String(dist));
  int calcSpeed =  maxSpeed;
  double speedBase = 1;
  double speedFactor = 1;
  analogWrite(PWM_PIN, calcSpeed);  // Initialize the speed as per defined value
  while(dist > optimal)
  {
    delay(PING_DELAY);
    if (dist < optimal + slowdownPoint)
    {
      speedBase = dist - optimal;
      speedFactor = speedBase / slowdownPoint;
      calcSpeed = (speedFactor * (maxSpeed - minSpeed)) + minSpeed;

      Serial.println ("dist is now: " + String(dist));
      Serial.println ("calcSpeed is : " + String(calcSpeed));
      analogWrite(PWM_PIN, calcSpeed);
    }
    dist = sonar.ping_cm();
    while (dist == 0)
    {
       delay (PING_DELAY);
       Serial.println("-- missed echo --");
       dist = sonar.ping_cm();
    }
  }
  digitalWrite(FWD_PIN, LOW);  // Stops Motor
  Serial.println("Catch up complete.");
}

void optimalDistance()
{
  distState = "Optimal";
  setColor(0, 0, 255);  // blue
  Serial.println (" - Optimal Distance");
}

void safeDistance()
{
  distState = "Safe";
  setColor(0, 255, 0);  // green
  Serial.println (" - Safe Distance");
}

void tooClose()
{
  distState = "Unsafe";
  setColor(255, 0, 0);  // red
  Serial.println (" - !! TOO CLOSE !!");
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String strFactor = "";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    strFactor += (char)payload[i];
  }
  Serial.println();
  double x = strFactor.toFloat();
  Serial.print("Received new optimal distance correction factor: ");
  Serial.println(x);
  optimalFactor = x;
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      int str_len = topicInput.length() + 1;
      char subTopic[str_len];
      topicInput.toCharArray(subTopic, str_len);
      client.subscribe(subTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
