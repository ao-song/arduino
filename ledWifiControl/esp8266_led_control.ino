#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

//SSID and Password to your ESP Access Point
const char* ssid = "StrangeAP";
const char* password = "Okay007890123456";

ESP8266WebServer server(80);

//serve the default page
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_part_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
String html_part_2 = "<form id='F1' action='turn'><input class='button' type='submit' name='RELAY' value='ON' ></form><br>";
String html_part_3 = "</div></body></html>";
 
void print_page() {
  String page = html_part_1 + html_part_2 + html_part_3;
  server.send(200, "text/html", page);
}

void handle_submit() {
  String request_value;

  if (!server.hasArg("RELAY")) {
    return;
  }

  request_value = server.arg("RELAY");
  if (request_value == "ON") {
    handle_on();
  } else if (request_value == "OFF") {
    handle_off();
  }
}

void handle_turn() {
  if (server.hasArg("RELAY")) {
    handle_submit();
  }
}

void handle_root() {
  print_page();
}

void handle_on() {
  Serial.print("on"); 
  html_part_2 = "<form id='F1' action='turn'><input class='button' type='submit' name='RELAY' value='OFF' ></form><br>";
  print_page();
}

void handle_off() {
  Serial.print("off");  
  html_part_2 = "<form id='F1' action='turn'><input class='button' type='submit' name='RELAY' value='ON' ></form><br>";
  print_page();
}


void setup(void) {
    
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);           
  WiFi.softAP(ssid, password);  

  IPAddress myIP = WiFi.softAPIP(); 
  Serial.print("StrangeAP IP:");
  Serial.println(myIP);
 
  server.on("/", handle_root);
  server.on("/on", handle_on);
  server.on("/off", handle_off);   
  server.on("/turn", handle_turn);  
  
  server.begin(); 
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();  
}
