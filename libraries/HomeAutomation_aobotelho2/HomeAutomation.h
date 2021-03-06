#ifndef HomeAutomation_h
#define HomeAutomation_h

#include <Arduino.h>

#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

enum outputStatus{
  nodeON = 0,
  nodeOFF
};

class HomeAutomation{
public:
	enum nodeType{
	  lightType=0,
	  switchType,
	  doubleSwitch
	};

	//constructor
	HomeAutomation(nodeType newNodeType,bool useSerial);
	
	//Getters and Setters
	nodeType getNodeType();

	
private:
	HomeAutomation::nodeType _type;
	bool _useSerial;

	void printSerial(char* msg);

	const char* mqtt_server = "192.168.1.22";
	const int mqtt_port = 1883;

	WiFiClient wificlient;
	PubSubClient client;
	WiFiManager wifimanager;

	//This is the specific topic in which the server will use to update the status of every node
	char* STATUS_TOPIC = "/update/status";
	//This is the specific topic in which the server will be listening to in order to update every node status
	char* STATUS_CALLBACK = "/update/callback/";
	//This is the specific topic in which the server will receive the information that a new device is available
	char* DISCOVER_TOPIC = "/discover/newDevices";
	//This is the specific topic in which the server will send the confirmation (or not) that the device was added
	char* DISCOVER_CALLBACK = "/discover/registerDevice/";
	//This is the specific topic in which the server will send the output status
	//The update topic is in the format "/NodeID/status", set further on on the code
	char* UPDATE_TOPIC;
	//This is the specific topic in whic the server will send a reset message
	char* RESET_TOPIC = "/update/reset/";

	
};
#endif
