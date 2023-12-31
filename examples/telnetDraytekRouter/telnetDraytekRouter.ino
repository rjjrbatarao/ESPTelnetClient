#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

#include <SyncClient.h>
#include "ESPTelnetClient.h"

//Enter your Wifi details here (multiple SSIDs possible)
#ifndef STASSID
#define STASSID "**********"
#define STAPSK  "**********"

#endif

//put here your router ip address, and login details
IPAddress draytekRouterIp (192, 168, 1, 2);
const char* user = "************";
const char* pwd = "***********"; 

const char* ssid     = STASSID;
const char* password = STAPSK;



SyncClient client;

ESPtelnetClient tc(client);

  

void setup () { 
                                       
  Serial.begin (9600);                              

// We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);


  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Connecting.... ");




  //WHICH CHARACTER SHOULD BE INTERPRETED AS "PROMPT"?
  tc.setPromptChar('>');

  //this is to trigger manually the login 
  //since it could be a problem to attach the serial monitor while negotiating with the server (it cause the board reset)
  //remove it or replace it with a delay/wait of a digital input in case you're not using the serial monitors
  
//  char key = 0;
//  Serial.println("\r\npress Enter to begin:");
//  do{
//    key = Serial.read();
//  }while(key<=0);

    //PUT HERE YOUR USERNAME/PASSWORD
  if(tc.login(draytekRouterIp, user, pwd)){        //tc.login(RouterIp, "admin", "", 1234) if you want to specify a port different than 23
    tc.sendCommand("ipf view -V");
    tc.sendCommand("exit");         
  }
  else{
    Serial.println("login failed");
  }
  tc.disconnect();

}

void loop () {                                         //  run your loop routine

}
