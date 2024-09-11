  #include <ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ThingSpeak.h>

const char* ssid = "Maverick";
const char* password = "ayush_12345";

WiFiClient client;
unsigned long myChannelNumber = 1323459;
const char *myWriteAPIKey = "20BRMUBMNBF1M9Y5";

WiFiServer server(80);
float temp;

void setup() 
{
  Serial.begin(115200);
  delay(10);
  Serial.println("Connecting to");
  Serial.print(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address");
  Serial.println(WiFi.localIP());
  server.begin();
  if(ThingSpeak.begin(client))
  {
  Serial.println("Start Uploading");
  }
}

void loop() {
WiFiClient client = server.available();
temp = random(10,30);
Serial.print("Temperature Value is: ");
Serial.print(temp);
Serial.println("C");

ThingSpeak.writeField(myChannelNumber,1,temp,myWriteAPIKey);

client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: Close");
client.println("Refresh: 5");
client.println();
client.println("<!DOCTYPE html>");
client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
client.println("<head>\n<meta charset='UTF-8'>");
client.println("<title>IOT PROGRAM 2</title>");
client.println("</head>\n<body>");
client.println("<H2>Connecting Temperature sensor");
client.println("<pre>");
client.print("Temperature sensor value: ");
client.println(float(temp),2);
delay(1000);
}
