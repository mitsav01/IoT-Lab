volatile char MY_DATA1[60];
volatile unsigned char k1 = 0,CC1=0,RX1 = 0,D = 0;
void setup()
{
// relay out put pin control.//
pinMode(0,OUTPUT);
pinMode(1,OUTPUT);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
digitalWrite(0,HIGH);
digitalWrite(1,HIGH);
digitalWrite(2,HIGH);
digitalWrite(3,HIGH);
// Initial setup //
Serial.begin(115200);
// Initial ESP8266 //
ESP8266_INIT();
}
void loop()
{
// receive data from ESP8266 //
if(Serial.available())
{
MY_DATA1[k1] = Serial.read(); // read receive data from wi-fi module.
CC1 = MY_DATA1[k1];
if(CC1 == ':')D = k1;// check weather data scan start or not.
k1++;
if(CC1 == '\n'){k1=0;RX1 = 1;} // chaeck new line character are receive or not.
}
// Processing  data which are receiving  from ESP8266 //
if(RX1 == 1)
{
if(MY_DATA1[D] == ':')
{
MY_DATA1[D] = '0';
if(MY_DATA1[D+1] == 'F')
{
MY_DATA1[D+1] = '0';

if(MY_DATA1[D+2] == 'A')//switch 1 on
{
MY_DATA1[D+2] = '0';

digitalWrite(0,LOW);
RX1 = 0;
}
else if(MY_DATA1[D+2] == 'B')//switch 1 off
{
MY_DATA1[D+2] = '0';
digitalWrite(0,HIGH);
RX1 = 0;
}
else if(MY_DATA1[D+2] == 'C')//switch 2 on
{
MY_DATA1[D+2] = '0';
digitalWrite(1,LOW);
RX1 = 0;
}
else if(MY_DATA1[D+2] == 'D')//switch 1 off
{
MY_DATA1[D+2] = '0';
digitalWrite(1,HIGH);
RX1 = 0;
}
else if(MY_DATA1[D+2] == 'E')//switch 3 on
{
MY_DATA1[D+2] = '0';
digitalWrite(2,LOW);
RX1 = 0;
          }
else if(MY_DATA1[D+2] == 'F')//switch 1 off
{
MY_DATA1[D+2] = '0';
digitalWrite(2,HIGH);
RX1 = 0;
}
else if(MY_DATA1[D+2] == 'G')//switch 1 on
{
MY_DATA1[D+2] = '0';
digitalWrite(3,LOW);
RX1 = 0;
}
else if(MY_DATA1[D+2] == 'H')//switch 1 off
{
MY_DATA1[D+2] = '0';
digitalWrite(3,HIGH);
RX1 = 0;
}
     }
}
RX1 = 0;
}
}
void ESP8266_INIT()// initializing wi-fi module.
{
Serial.println("AT");// check AT mode.
delay(1000);
Serial.println("AT+RST");//RESET module.
delay(3000);
Serial.println("AT+CWSAP=\DemoConnection\",\"2231anto\",3,2");//set the ssid and password.
 delay(1500);
Serial.println("AT+CWMODE=3");// set ESP8266 in MODE 3 (Both mode AP+station).
delay(1400);
Serial.println("AT+CIPMUX=1");// set ESP8266 in MUX 1 (allow multiple connection).
delay(1400);
Serial.println("AT+CIPSERVER=1,80");// start communication ESP8266 on PORT80.
delay(1500);
}
