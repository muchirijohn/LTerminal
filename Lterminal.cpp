// 
// file: LTerminal.cpp
//
// library for linkit wifi remote terminal
//
// created 4 feb 2015
// muchiri john
//
// LTerminal.h
//
#include "LTerminal.h"

//
// DESCRIPTION
// initialize linkit as a client for communication through wifi
//
// PARAMETERS
// ssid: WIFI_AP
// enc: LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
// pwd: WIFI-PASSWORD
// host: SERVER IP address
// port: Communication PORT
//
// REUTRNS
// true if success else false
// 
//
void LTerminalClass::begin(const char *ssid, LWiFiEncryption enc,
						   const String pwd, const char *host, uint16_t port)
{

	LWifiInfo.lt_ssid = ssid; //wifi_AP
	LWifiInfo.lt_enc = enc; //wifi_auth
	LWifiInfo.lt_pwd = &pwd; //wifi_password
	LWifiInfo.lt_host = host; //host
	LWifiInfo.lt_port = port; //port
	
	bf = buffer;
	buffer_index = 0;
	retry = 0;
	
	LTask.begin();
	LWiFi.begin();
	wifiConnect();
}

//
// DESCRIPTION
// connect terminal client to server
//
// PARAMETERS
// none
//
// REUTRNS
// true if success else false
// 
//
uint8_t LTerminalClass::wifiConnect()
{
	retry = 0;
	//connect to wifi network with provided credentials
	while (0 == LWiFi.connect(LWifiInfo.lt_ssid, LWiFiLoginInfo(LWifiInfo.lt_enc, *LWifiInfo.lt_pwd)))
	{
		//wait for a second before next retry
		delay(1000);
		if(retry >= retry_Max)  return 0; //if retry times > retry_Max times exit method
		else retry++;
	}
	return 1; //return true if success
}

//
// DESCRIPTION
// send data to remote terminal
//
// PARAMETERS
// none
//
// REUTRNS
// true if success else false
// 
//
uint8_t LTerminalClass::sendData()
{
	char buff[max_Buffer];
	*(bf+buffer_index) = '\0';
	// keep retrying [retry_Max times] until connected to server
	retry = 0;
	while (0 == lc.connect(LWifiInfo.lt_host, LWifiInfo.lt_port)) 
	{
		//wait for 1 second before retrying again
		delay(1000);
		if(retry >= retry_Max)  return 0; //give up and go back
		else retry++; //retry again
	}
	//HTTP request, ending with CR/LF
	sprintf(buff,"GET /%s HTTP/1.1", bf);
	lc.println(buff);
	sprintf(buff, "Host: %s:%d",LWifiInfo.lt_host, LWifiInfo.lt_port);
	lc.println(buff);
	lc.println("Connection: keep-alive");
	lc.println();
	//initialize buffer to save new data
	initBuffer();
	return 1;
}

//
// DESCRIPTION
// @overide method, from Print class
//
// PARAMETERS
// value: value to send
//
// REUTRNS
// true if success else false
//
inline size_t LTerminalClass::write(uint8_t value) {
	//sendData(&value);
	if(value == '\n' || value == '\r')
	{
		if(value == '\r') //if CL found send data to terminal
		{
		    if(buffer_index == 0) *(bf+(buffer_index++)) = ' ';
			sendData();
		}
		return 0; //assume CL/LF
	}
	//encode special characters
	if(!encodeData(value))
		*(bf+(buffer_index++)) = value;
	//if overflow start from from zero
	if(buffer_index >= 1020) buffer_index = 0;

	return 1; // assume success
}

//
// DESCRIPTION
// initialize buffer index to 0
//
inline void LTerminalClass::initBuffer()
{
	buffer_index = 0; //set index to 0
}

// 
// DESCRIPTION
// encode characters so that they can interpreted correctly by the server
//
// PARAMETERS
// ch: value to check if it qualifies to be encoded
//
// REUTRNS
// true if success else false
//
inline uint8_t LTerminalClass::encodeData(uint8_t ch)
{
	char p[2], *pp;
	switch(ch)
	{
	case '`':
	case ' ':
	case '#':
	case '%':
	case '^':
	case '|':
	case '{':
	case '}':
		*(bf+(buffer_index++)) = '%'; //found special character to encode
		print(ch, 16);
		return 1;
	};
	return 0;
}

//instance
LTerminalClass LTerminal;

