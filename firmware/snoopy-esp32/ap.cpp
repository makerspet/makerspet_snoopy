#include "ap.h"

// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
//const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_3 = "gateway";
const char* PARAM_INPUT_4 = "dest_ip";
const char* PARAM_INPUT_5 = "dest_port";

//Variables to save values from HTML form
String ssid;
String pass;
//String ip;
String gateway;
String dest_ip;
String dest_port;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
//const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";
const char* destIpPath = "/dest_ip.txt";
const char* destPortPath = "/dest_port.txt";

//IPAddress localIP(192, 168, 1, 200); // hardcoded
IPAddress localIP;
IPAddress localGateway; // Set your Gateway IP address
//IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);

// Read File from SPIFFS
String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path);
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }
  
  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;     
  }
  return fileContent;
}

// Initialize SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  Serial.println("SPIFFS mounted successfully");

  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  //ip = readFile(SPIFFS, ipPath);
  gateway = readFile(SPIFFS, gatewayPath);
  dest_ip = readFile(SPIFFS, destIpPath);
  dest_port = readFile(SPIFFS, destPortPath);

  Serial.println(ssid);
  Serial.println(pass);
  //Serial.println(ip);
  Serial.println(gateway);
  Serial.println(dest_ip);
  Serial.println(dest_port);
}

// Write file to SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
}

void ObtainWiFiCreds(void (*callback)()) {
  AsyncWebServer server(80);  // Create AsyncWebServer object on port 80

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting up Access Point ");
  Serial.println(SSID_AP);
  // NULL sets an open Access Point
  WiFi.softAP(SSID_AP, NULL);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); 

  // Web Server Root URL
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/wifimanager.html", "text/html");
  });
  
  server.serveStatic("/", SPIFFS, "/");
  
  server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
    int params = request->params();
    for(int i=0;i<params;i++){
      AsyncWebParameter* p = request->getParam(i);
      if(p->isPost()){
        // HTTP POST ssid value
        if (p->name() == PARAM_INPUT_1) {
          ssid = p->value().c_str();
          Serial.print("SSID set to: ");
          Serial.println(ssid);
          // Write file to save value
          writeFile(SPIFFS, ssidPath, ssid.c_str());
        }
        // HTTP POST pass value
        if (p->name() == PARAM_INPUT_2) {
          pass = p->value().c_str();
          Serial.print("Password set to: ");
          Serial.println(pass);
          // Write file to save value
          writeFile(SPIFFS, passPath, pass.c_str());
        }
        /*
        // HTTP POST ip value
        if (p->name() == PARAM_INPUT_3) {
          ip = p->value().c_str();
          Serial.print("IP Address set to: ");
          Serial.println(ip);
          // Write file to save value
          writeFile(SPIFFS, ipPath, ip.c_str());
        }
        */
        // HTTP POST gateway value
        if (p->name() == PARAM_INPUT_3) {
          gateway = p->value().c_str();
          Serial.print("Gateway set to: ");
          Serial.println(gateway);
          // Write file to save value
          writeFile(SPIFFS, gatewayPath, gateway.c_str());
        }
        // HTTP POST destination IP value
        if (p->name() == PARAM_INPUT_4) {
          dest_ip = p->value().c_str();
          Serial.print("Destination IP set to: ");
          Serial.println(dest_ip);
          // Write file to save value
          writeFile(SPIFFS, destIpPath, dest_ip.c_str());
        }
        // HTTP POST destination port value
        if (p->name() == PARAM_INPUT_5) {
          dest_port = p->value().c_str();
          Serial.print("Destination port set to: ");
          Serial.println(dest_port);
          // Write file to save value
          writeFile(SPIFFS, destPortPath, dest_port.c_str());
        }
        //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      }
    }
    request->send(200, "text/html; charset=utf-8",
      "<HTML><BODY>"
      "<center><h1><br>Connecting to your router...</h1>"
      "<p>Please reconnect to " + ssid + " now</p>"
      "</center></BODY></HTML>");
    delay(3000);
    ESP.restart();
  });
  server.begin();
  while(true) {
    callback();
    yield();
  }
}

String getSSID() {
  return ssid;
}

String getPassw() {
  return pass;
}

//String getIP() {
//  return ip;
//}

String getDestIP() {
  return dest_ip;
}

String getDestPort() {
  return dest_port;
}

String getGateway() {
  return gateway;
}

void resetWiFiSettings() {
  SPIFFS.remove(ssidPath);
  SPIFFS.remove(passPath);
//  SPIFFS.remove(ipPath);
  SPIFFS.remove(gatewayPath);
  SPIFFS.remove(destIpPath);
  SPIFFS.remove(destPortPath);
}
