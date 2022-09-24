 #include"ThingSpeak.h"
 #include <ESP8266WiFi.h>
 
long mychannelnumber = 1871981;
String apikey = "RBKEBJNFTSBE02Y9"; // Enter your Write API key from Thingspeak
const char *ssid = "abc"; // replace with your wifi said and wpa2 key
const char *pass = "123456789";
const char* server = "api.thingspeak.com";

const int sensor_pin = A0;

WiFiClient client;


 // Connect Soil moisture analog sensor pin to A0 of NodeMCU

void setup() {
Serial.begin(115200);

delay(10);

Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, pass);

while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print (".");
}
Serial.println("");
Serial.println("WiFi connected");
delay(4000);
}
void loop()
{
int moisture_percentage;

moisture_percentage = (100.00 - ((analogRead(sensor_pin)/1023.00)*100.00 ) ); 

Serial.print("Soil Moisture (in Percentage)= ");
Serial.print (moisture_percentage);
Serial.println("%");

if (client.connect(server, 80)) // "184.106.153.149" or ap1.thingspeak.com
{
String postStr = apikey;
postStr += "&field1=";
postStr += String (moisture_percentage);
postStr += "r\n";

client.print ("POST /update HTTP/1.1\n");
client.print ("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print ("X-THINGSPEAKAPIKEY: " + apikey + "\n");
client.print ("Content-Type: application/x-www-form-urlencoded\n"); 
client.print ("Content-Length: ");
client.print (postStr.length());
client.print ("\n\n");
client.print (postStr);

Serial.println("Data Send to Thingspeak");
}
client.stop();
Serial.println("Waiting...");
delay(2000);
}
// thingspeak needs minimum 15 sec delay between updates.
