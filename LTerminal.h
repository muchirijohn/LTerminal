// 
// file: LTerminal.h
//
// library for linkit remote terminal
//
// created 4 feb 2015
// muchiri john
//
// LTerminal.h
//

#ifndef _LTERMINAL_h
#define _LTERMINAL_h


#include <stdio.h>

//incudes
#include <LTask.h>
#include "LWiFi.h"
#include "LWiFiClient.h"

//number of times to retry connections before giving up
#define retry_Max 3
//max number of bytes to hold in buffer for transmission
#define max_Buffer 1024

//struct to hold user credentials
struct wifiInfo
{
	const char *lt_ssid; //wifi_AP
	LWiFiEncryption lt_enc; //wifi_auth
	const String *lt_pwd; //wifi_password
	const char *lt_host; //host
	uint16_t lt_port; //port
};


class LTerminalClass:public Print
{
 protected:
	 //client
	 LWiFiClient lc;
	 //buffer to hold contents
	 uint8_t buffer[max_Buffer], *bf;
	 //index to hold the position of the next value in buffer
	 unsigned int buffer_index;
	 //initialize buffer index to zero
	 inline void initBuffer();
	 //encode special characters
	 inline uint8_t encodeData(uint8_t c);
	 //struct to hold user credentials
	 struct wifiInfo LWifiInfo;
	 //variable for retry connections times
	 uint8_t retry;
 public:
	 //begin and connect linkit to remote terminal using given creds
	void begin(const char *ssid, LWiFiEncryption enc, const String pwd,
		const char *host, uint16_t port);
	//connect to wifi network
	uint8_t wifiConnect();
	//send data to remote terminal
	uint8_t sendData();
	//@override method from Print Class
	virtual size_t write(uint8_t data);
	//this library uses the Print Class write method
	using Print::write;
};

//extern instance
extern LTerminalClass LTerminal;

#endif

