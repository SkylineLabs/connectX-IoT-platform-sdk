#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// Update these with values suitable for your network.
const char* ssid = "";												//Enter Wifi SSID
const char* password = "";											//Enter Wifi password

int dpin = D4;
WiFiClient espClient;
PubSubClient client(espClient);


void setup() {

  Serial.begin(115200);//Begin serial monitor
  pinMode(BUILTIN_LED, OUTPUT);// Initialize the BUILTIN_LED pin as an output
  pinMode(dpin, OUTPUT);

  setup_wifi(); //Connect to wifi
  
  //Setup the device for server communication
  client.setServer("", 1883);     													//Enter Server IP here
  client.setCallback(callback);//Function to handle data coming from server
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void callback(char* topic, byte* payload, unsigned int length) {	//Function called when message received
  int i =0;
  char message[1000] ;
   
   for(i=0;i<length;i++)
   {
     message[i]=payload[i];
   }
   message[i] = '\0';
   
   String content =String(message);  
   String head =String(topic);
  
   if(head.equals(""))													//Enter incoming message topic here
  {
     //Action to perform
   }
}


void reconnect() {

  // Loop to get internet connection
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("", "", "")) {											//Enter Client ID, Username, Password
      Serial.println("connected");
      client.subscribe("");														//Subscribe to topics here
    } 
	
	else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  client.publish("","")															//Publish message here - Topic, Message
}
