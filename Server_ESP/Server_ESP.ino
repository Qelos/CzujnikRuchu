#include <ESP8266WiFi.h>

IPAddress staticIP(192, 168, 45, 54);
IPAddress gateway(192, 168, 45, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "CBR";
const char* password = "droker2412CBR";

const uint16_t port = 80;
//const char* host = "192.168.45.75";

WiFiClient ESPClient;
WiFiServer ESPServer(port);

void setup()
{
  pinMode(2, OUTPUT);
  Start();
  WiFiConnection();

  Serial.println("Otwieram serwer.");
  ESPServer.begin();
}



void loop()
{

  //if (ESPServer.hasClient())
  //{
  ESPClient = ESPServer.available();
  if (ESPClient)
  {
    Serial.println("Mam klienta");

    while (ESPClient.connected())
    {
      if (ESPClient.available())
      {
        String Message = ESPClient.readString();
        Serial.println(Message);
        String Msg = Message;
        if (Msg == "1")
        {
          //Wyślij do bota żeby pisał że ma wolne piłkarzyki
          digitalWrite(2, 1);
        }
        else if (Msg == "0")
        {
          //Wyślij do bota żeby pisał że ma zajęte piłkarzyki
          digitalWrite(2, 0);
        }
      }
    }
    Serial.println("Rozłączono z klientem");
  }
  //}
}

void Start()
{
  Serial.begin(9600);
  WiFi.disconnect();
  delay(3000);
  pinMode(2, OUTPUT);
  Serial.print("Start\n");
}

void WiFiConnection()
{
  WiFi.hostname("ESPSerwer");

  Serial.print("Łączę z ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  WiFi.config(staticIP, gateway, subnet);

  Serial.print("\nPołaczono z siecią WiFi\nAdres IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Moja nazwa: ");
  Serial.println(WiFi.hostname());
}
