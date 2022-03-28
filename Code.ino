#include<ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char THING_ID[]           = "ENTER THING ID"; //Enter THING ID
const char DEVICE_LOGIN_NAME[]  = "ENTER DEVICE ID"; //Enter DEVICE ID

const char SSID[]               = "WIFI NAME";    //Enter WiFi SSID (name)
const char PASS[]               = "WIFI PASSWORD";    //Enter WiFi password
const char DEVICE_KEY[]         = "SECRET KEY";    //Enter Secret device password (Secret Key)


#define PinOfRelay1 19 //D19 pin
#define PinOfRelay2 21 //D21 Pin
#define PinOfRelay3 22 //D22 pin
#define PinOfRelay4 23 //D23 pin


#define switch1 13 //D13
#define switch2 12 //D12
#define switch3 14 //D14
#define switch4 27 //D27


bool statefortoggle1 = 0;
bool statefortoggle2 = 0;
bool statefortoggle3 = 0;
bool statefortoggle4 = 0;


bool switch1_state = LOW;
bool switch2_state = LOW;
bool switch3_state = LOW;
bool switch4_state = LOW;



void changeswitch1();
void changeswitch2();
void changeswitch3();
void changeswitch4();

CloudSwitch switch_1;
CloudSwitch switch_2;
CloudSwitch switch_3;
CloudSwitch switch_4;

#define LedforWiFi 2 //D2 (internally connected blue light)

void initProperties();

void doThisOnConnect();
void doThisOnDisconnect();
void doThisOnSync();

WiFiConnectionHandler ArduinoIOTPreferredConnection(SSID,PASS);


void relaytoggle(int);
void manual_control();

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //iNitialize serial and wait for port to open
  delay(1500); // delay gives teh chance to wait for a serial monitor without blocking if none is found

  initProperties(); 

//connect to arduino IOT coud
  ArduinoCloud.begin(ArduinoIOTPreferredConnection);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::CONNECT, doThisOnConnect);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::SYNC, doThisOnSync);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::DISCONNECT, doThisOnDisconnect);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(PinOfRelay1,OUTPUT);
  pinMode(PinOfRelay2,OUTPUT);
  pinMode(PinOfRelay3,OUTPUT);
  pinMode(PinOfRelay4,OUTPUT);


  pinMode(switch1,INPUT_PULLUP);
  pinMode(switch2,INPUT_PULLUP);
  pinMode(switch3,INPUT_PULLUP);
  pinMode(switch4,INPUT_PULLUP);


  pinMode(LedforWiFi,OUTPUT);

  //during start all relays should be off
  digitalWrite(PinOfRelay1,HIGH);
  digitalWrite(PinOfRelay2,HIGH);
  digitalWrite(PinOfRelay3,HIGH);
  digitalWrite(PinOfRelay4,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  ArduinoCloud.update();

  manual_control();
}

void initProperties()
{
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(switch_1, READWRITE, ON_CHANGE, changeswitch1);
  ArduinoCloud.addProperty(switch_2, READWRITE, ON_CHANGE, changeswitch2);
  ArduinoCloud.addProperty(switch_3, READWRITE, ON_CHANGE, changeswitch3);
  ArduinoCloud.addProperty(switch_4, READWRITE, ON_CHANGE, changeswitch4);
}

void doThisOnConnect(){
  Serial.println("ESP32 Board successfully connected to Arduino IOT cloud");
  digitalWrite(LedforWiFi, HIGH); //Turn on Wifi led
}

void doThisOnDisconnect()
{
  Serial.println("ESP32 board is disconnected from Arduino IOT Cloud");
  digitalWrite(LedforWiFi,LOW); //Turn Off WifiLed
}

void doThisOnSync(){
  Serial.println("Things Properties Synchronised.");
}
//FOR MANUAL CONTROLINNG VIA MANUAL SWITCHES
void manual_control()
{ 
  // for switch 1
  if(digitalRead(switch1) == LOW && switch1_state == LOW)
  {
    digitalWrite(PinOfRelay1,LOW); // turn on switch 1 
    statefortoggle1 = 1;
    switch1_state = HIGH;

    switch_1 = statefortoggle1;

    Serial.println("Switch 1 is on.");
  }
  else if(digitalRead(switch1)==HIGH && switch1_state == HIGH)
  {
    digitalWrite(PinOfRelay1,HIGH); // turn off switch

    statefortoggle1=0;
    switch1_state = LOW;

    switch_1 = statefortoggle1;
    Serial.println("Switch 1 is off");
  }

  //for switch 2
  if(digitalRead(switch2) == LOW && switch2_state == LOW)
  {
    digitalWrite(PinOfRelay2,LOW); // turn on switch 1 
    statefortoggle2 = 1;
    switch2_state = HIGH;

    switch_2 = statefortoggle2;

   Serial.println("Switch 2 is on.");
  }
  else if(digitalRead(switch2)==HIGH && switch2_state == HIGH)
  {
    digitalWrite(PinOfRelay2,HIGH); // turn off switch

    statefortoggle2=0;
    switch2_state = LOW;

    switch_2 = statefortoggle2;
    Serial.println("Switch 2 is off");
  }

  // for switch 3
  if(digitalRead(switch3) == LOW && switch3_state == LOW)
  {
    digitalWrite(PinOfRelay3,LOW); // turn on switch 1 
    statefortoggle3 = 1;
    switch3_state = HIGH;

    switch_3 = statefortoggle3;

    Serial.println("Switch 3 is on.");
  }
  else if(digitalRead(switch3)==HIGH && switch3_state == HIGH)
  {
    digitalWrite(PinOfRelay3,HIGH); // turn off switch

    statefortoggle3=0;
    switch3_state = LOW;

    switch_3 = statefortoggle3;
    Serial.println("Switch 3 is off");
  }

  //for switch 4
   if(digitalRead(switch4) == LOW && switch4_state == LOW)
  {
    digitalWrite(PinOfRelay4,LOW); // turn on switch 1 
    statefortoggle4 = 1;
    switch4_state = HIGH;

    switch_4 = statefortoggle4;

    Serial.println("Switch 4 is on.");
  }
  else if(digitalRead(switch4)==HIGH && switch4_state == HIGH)
  {
    digitalWrite(PinOfRelay4,HIGH); // turn off switch

    statefortoggle4=0;
    switch4_state = LOW;

    switch_4 = statefortoggle4;
    Serial.println("Switch 4 is off");
  }

}


// FOR CONTROLLING VIA ARDUINO WEB APPLICATION OR MOBILE APP OR VIA ALEXA
void changeswitch1()
{
  if(switch_1 == 1)
  {
    digitalWrite(PinOfRelay1,LOW);
    Serial.println("Load 1 is on");
    statefortoggle1 = 1;
  }
  else
  {
    digitalWrite(PinOfRelay1, HIGH);
    Serial.println("Load 1 is OFF");
    statefortoggle1 = 0;
  }
}

void changeswitch2()
{
  if(switch_2 == 1)
  {
    digitalWrite(PinOfRelay2,LOW);
    Serial.println("Load 2 is on");
    statefortoggle2 = 1;
  }
  else
  {
    digitalWrite(PinOfRelay2, HIGH);
    Serial.println("Load 2 is  OFF");
    statefortoggle2 = 0;
  }
}

void changeswitch3()
{
  if(switch_3 == 1)
  {
    digitalWrite(PinOfRelay3,LOW);
    Serial.println("Load 3 is on");
    statefortoggle3 = 1;
  }
  else
  {
    digitalWrite(PinOfRelay3, HIGH);
    Serial.println("Load 3 is OFF");
    statefortoggle3 = 0;
  }
}

void changeswitch4()
{
  if(switch_4 == 1)
  {
    digitalWrite(PinOfRelay4,LOW);
    Serial.println("Load 4 is on");
    statefortoggle4 = 1;
  }
  else
  {
    digitalWrite(PinOfRelay4, HIGH);
    Serial.println("Load 4 is OFF");
    statefortoggle4 = 0;
  }
}
