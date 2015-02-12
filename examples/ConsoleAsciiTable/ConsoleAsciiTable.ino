/*
  ASCII table

 Prints out byte values in all possible formats:
 * as raw binary values
 * as ASCII-encoded decimal, hex, octal, and binary values

 For more on ASCII, see http://www.asciitable.com and http://en.wikipedia.org/wiki/ASCII

 The circuit:  No external hardware needed.

 created 2006
 by Nicholas Zambetti
 http://www.zambetti.com
 modified 9 Apr 2012
 by Tom Igoe
 modified 22 May 2013
 by Cristian Maglie
 modified 5 Feb 2015
 by Muchiri John

 This example code is in the public domain.

 http://arduino.cc/en/Tutorial/ConsoleAsciiTable

 */
 
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

void setup() {
  // put your setup code here, to run once:
   //connect to terminal with given creds
  LTerminal.begin(WIFI_AP, WIFI_AUTH, WIFI_PASSWORD, SERVER, PORT);
  //send data
  LTerminal.println();
  LTerminal.println("[--     LinkIt One Remote Terminal    --]");
  LTerminal.println("[--           ASCII TABLE DEMO        --]");
  LTerminal.println();
  //wait for 3 seconds
  delay(1000);
  // prints title with ending line break
  LTerminal.println("ASCII Table ~ Character Map");
  LTerminal.println();
  delay(2000);
}

// first visible ASCIIcharacter '!' is number 33:
int thisByte = 33;
// you can also write ASCII characters in single quotes.
// for example. '!' is the same as 33, so you could also use this:
//int thisByte = '!';

void loop() {
  // prints value unaltered, i.e. the raw binary version of the
  // byte. The Console monitor interprets all bytes as
  // ASCII, so 33, the first number,  will show up as '!'
  LTerminal.write(thisByte);

  LTerminal.print(",  dec: ");
  // prints value as string as an ASCII-encoded decimal (base 10).
  // Decimal is the  default format for Console.print() and Console.println(),
  // so no modifier is needed:
  LTerminal.printf("%03d", thisByte);
  // But you can declare the modifier for decimal if you want to.
  //this also works if you uncomment it:

  // Console.print(thisByte, DEC);

  LTerminal.print(",  hex: ");
  // prints value as string in hexadecimal (base 16):
  LTerminal.printf("0x%X",thisByte);

  LTerminal.print(",  oct: ");
  // prints value as string in octal (base 8);
  LTerminal.printf("%03o", thisByte);

  LTerminal.print(",  bin: 0b");
  // prints value as string in binary (base 2)
  // also prints ending line break:
  LTerminal.println(thisByte, BIN);

  // if printed last visible character '~' or 126, stop:
  if (thisByte == 126) {    // you could also use if (thisByte == '~') {
    // ensure the latest bit of data is sent
    //Console.flush();
    LTerminal.println();
    LTerminal.println("Done!");
    // This loop loops forever and does nothing
    while (true) {
      continue;
    }
  }
  // go on to the next character
  thisByte++;
}
