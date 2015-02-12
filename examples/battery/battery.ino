/**
* Battery info
* 
* Modified from original LinkIt One Battery Example
* Muchiri Jon
* feb 09 2015
*
**/

#include <LBattery.h>
//includes required
#include <LWiFiClient.h>
#include <LWiFi.h>

//include LTerminal library
#include "LTerminal.h"

//defines: user credentials
#define WIFI_AP "net" //wifi AP
#define WIFI_PASSWORD "netconn14" //wifi Password
#define WIFI_AUTH LWIFI_WPA// choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
#define SERVER "192.168.1.101" //server address
#define PORT 2215 //port

char buff[256];

void setup() {
  // put your setup code here, to run once:
   //connect to terminal with given creds
  LTerminal.begin(WIFI_AP, WIFI_AUTH, WIFI_PASSWORD, SERVER, PORT);
  //send data
  LTerminal.println();
  LTerminal.println("[--     LinkIt One Remote Terminal    --]");
  LTerminal.println("[--          Battery info DEMO        --]");
  LTerminal.println();
  //wait for 3 seconds
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  sprintf(buff,"battery level = %d", LBattery.level() );
  LTerminal.println(buff);
  sprintf(buff,"is charging = %d",LBattery.isCharging() );
  LTerminal.println(buff);
  LTerminal.println();
  delay(1000); 
}

