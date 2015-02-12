/**
*
* LinkIt One remote Terminal
*
* demo for sending data to a remote terminal
*
* created 4 feb 2015
* muchiri john
*
**/

//includes required
#include <LWiFiClient.h>
#include <LWiFi.h>

//include LTerminal library
#include "LTerminal.h"

//defines: user credentials
#define WIFI_AP "your_AP" //wifi AP
#define WIFI_PASSWORD "password" //wifi Password
#define WIFI_AUTH LWIFI_WPA// choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define SERVER "192.168.1.101" //set server i.p address
#define PORT 2215 //port

//setup method
void setup()
{
  //connect to terminal with given creds
  LTerminal.begin(WIFI_AP, WIFI_AUTH, WIFI_PASSWORD, SERVER, PORT);
  //send data
  LTerminal.println();
  LTerminal.println("[--     LinkIt One Remote Terminal    --]");
  LTerminal.println("[-- Millis() and Distance sensor Demo --]");
  LTerminal.println();
  //wait for 3 seconds
  delay(3000);
}

//loop method
void loop()
{
  //wait to 250ms
  delay(250);
  //send millis()
  LTerminal.print("Current Millis() : ");
  LTerminal.print(millis());
  //send dustance sensor values
  LTerminal.print(" , Distance sensor Value = ");
  //map sensor values to distance values
  uint8_t distance = map(analogRead(A0), 27, 640, 80, 10);
  //send distance
  LTerminal.print(distance);
  //send units:cm
  LTerminal.println(" CM.");
  LTerminal.println();
}
