#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
  
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "Otavio"; //SSID
char pass[] = "38227423*"; // Password
//-------------------------------------------//

const int trigger = 16;
const int echo = 5;
long T;
float distanceCM;
WiFiClient  client;

unsigned long myChannelField = 926562; // Channel ID
const int ChannelField = 1; // Which channel to write data
const char * myWriteAPIKey = "JCM7DJHELZHUXJLG"; // Your write API Key

void setup()
{
  Serial.begin(115200);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  
    if (WiFi.status() != WL_CONNECTED)
  {
    //Serial.print("Attempting to connect to SSID: ");
    //Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
     // Serial.print(".");
      delay(4000);
    }
    //Serial.println("\nConnected.");
  }
}
void loop()
{
  
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  T = pulseIn(echo, HIGH);
  distanceCM = T * 0.034;
  distanceCM = distanceCM / 2;
  
//  Serial.print("Distance in cm: ");
//  Serial.println(distanceCM);
  ThingSpeak.writeField(myChannelField, ChannelField, distanceCM, myWriteAPIKey);
  delay(100);
}
