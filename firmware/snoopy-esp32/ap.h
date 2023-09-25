#ifndef KAIA_AP_H_
#define KAIA_AP_H_

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"

#define SSID_AP "KAIAAI-WIFI"

void initSPIFFS();
void ObtainWiFiCreds(void (*callback)());
String getSSID();
String getPassw();
String getIP();
String getGateway();
String getDestIP();
String getDestPort();

//String readFile(fs::FS &fs, const char * path);
//void writeFile(fs::FS &fs, const char * path, const char * message);
void resetWiFiSettings();

#endif
