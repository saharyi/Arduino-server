/*
 * Sketch: ESP8266_LED_Control_02
 * Control an LED from a web browser
 * Intended to be run on an ESP8266
 * 
 * connect to the ESP8266 AP then
 * use web broswer to go to 192.168.4.1
 * 
 */
 
 
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#define DEBUG true 
SoftwareSerial esp8266(2,3); 
const char* ssid = "sahar";               
const char* password = "099224466";   
 
WiFiServer server(80);
IPAddress ip(192,168,43 ,200); // where xx is the desired IP Address
IPAddress gateway(192,168,43,1); // set gateway to match your network
IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "LED TURN_ON success";
String html_2 = "LED TURN_OFF success";
/*String html_3 = "<form id='F2' action='LEDOFF'><input class='button' type='submit' value='LED OFF' ></form><br>";
String html_4 = "</div></body></html>";*/
 
String request = "";
//int LED_Pin = D2;
 
void setup() 
{
  Serial.begin(115200);
  esp8266.begin(115200); // your esp's baud rate might be different
   pinMode(D2,OUTPUT);
    digitalWrite(D2,LOW);
  Serial.print(F("Setting static ip to : "));
  Serial.println(ip);
  
  // Connect to WiFi network
  //5
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  //Trying to connect it will display dots
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP IS: ");
  Serial.println(WiFi.localIP());
  // Start the server
  server.begin();
  Serial.println("Server started");
} // void setup()
 
 
void loop() 
{
 
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');
 
    if       ( request.indexOf("ON") > 0 )  { digitalWrite(D2,HIGH);  }
    if  ( request.indexOf("OFF") > 0 ) { digitalWrite(D2,LOW);  }
 
    client.flush();
 
     client.print( header );
   // client.print( html_1 );
   // client.print( html_2 );
   /* client.print( html_3 );
    client.print( html_4);*/
 
    delay(5);
  // The client will actually be disconnected when the function returns and 'client' object is detroyed
 
} // void loop()
