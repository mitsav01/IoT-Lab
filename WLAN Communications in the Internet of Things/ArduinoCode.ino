#include <SoftwareSerial.h> 
#include <NanoESP.h> 
// define WLAN connection information 
#define WLAN_SSID "CN-Students" 
#define LDR_PIN A0
#define WLAN_PWD "CnStudentsWiFiAccess123" 
#define REMOTE_IP_ADDRESS "192.168.1.197" 
#define REMOTE_PORT 9999 
// define used global variables 
NanoESP esp8266 = NanoESP(); 
int counter = 0; 
char msg[64]; 
void setup() { 
    // setup communications with the serial monitor 
    Serial.begin(19200); // initialize WLAN and TCP/IP connection 
    esp8266.init(); 
    esp8266.configWifi(STATION, WLAN_SSID, WLAN_PWD); 
    esp8266.newConnection(0, "UDP", REMOTE_IP_ADDRESS, REMOTE_PORT); } 
void loop() { 
      
      // increment counter 
      counter++; 
      // create message 
      int lightvalue = analogRead(LDR_PIN);
      Serial.println(lightvalue);
      sprintf(msg, "6003798; %d; %d",counter, lightvalue);
      // show message on serial monitor 
      Serial.println(msg);
      
      // send data over UDP to the server 
      esp8266.sendData(0, msg); 
      // wait 4 seconds before next message 
      delay(4000); }
