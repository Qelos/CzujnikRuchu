#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

unsigned long aktualnyCzas = 0;
unsigned long zapamietanyCzas = 0;
unsigned long roznicaCzasu = 0;

const int PIN_CZUJNIK = 4;

const char* ssid = "CBR";
const char* password = "droker2412CBR";

const uint16_t port = 8080;
const uint16_t portDlaBota = 1234;
//const char* host = "ESPSerwer"; //Możliwość przypisania URL jako adres hosta.
//const char* host = "192.168.45.54";
const char* host = "192.168.2.75";

WiFiClient ESPClient;
WiFiClient Bot;
WiFiServer dlaBota(portDlaBota);

bool x = false;
bool czujnik;

void setup()
{
  Start();
  WiFiConnection();
  Serial.println(WiFi.localIP());

  Serial.println("Otwieram serwer.");
  dlaBota.begin();

  firstConnection();
}
void loop()
{
  Signal();
  if (ESPClient.connected())
  {
    Communication();
  }
  else
  {
    Reconnection();
    Signal();
  }
  if (x != czujnik)
  {
    BotCommunication();
  }
}

void Communication()
{
  if (czujnik)
  {
    Serial.println("czujnik TRUE");
    ESPClient.print(1);
  }
  else
  {
    Serial.println("czujnik FALSE");
    ESPClient.print(0);
  }
}
void Signal()
{
  if (digitalRead(PIN_CZUJNIK) == HIGH)
  {
    zapamietanyCzas = millis();
    if (!czujnik)
    {
      Serial.println("czujnik TRUE");
      //ESPClient.print(1);
      czujnik = true;
    }
  }
  roznicaCzasu = millis() - zapamietanyCzas;
  if (roznicaCzasu >= 30000 && czujnik)
  {
    czujnik = false;
    Serial.println("czujnik FALSE");
    //ESPClient.print(0);
  }
}

void Reconnection()
{
  //Serial.println("Nie połączono z serwerem!!!");
  ESPClient.connect(host, port);
  if (ESPClient.connected())
  {
    Serial.println("Połączono z serwerem!");
  }
  else
  {
    //delay(1000);
    return;
  }
}
void firstConnection()
{
  Serial.println("Próba połaczenia z serwerem!");
  ESPClient.connect(host, port);
  delay(1000);
  if (!ESPClient.connected())
  {
    Serial.println("Nie połączono z serwerem!!!");
  }
  else
  {
    Serial.println("Połączono z serwerem!");
  }
}
void WiFiConnection()
{
  Serial.print("Łączę z ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nPołaczono z siecią WiFi.");
}
void Start()
{
  Serial.begin(9600);
  delay(3000);
  pinMode(PIN_CZUJNIK, INPUT);
  Serial.print("Start\n");
  digitalWrite(LED_BUILTIN, HIGH);
}

void BotCommunication()
{
  //HTTPClient Post;
  //Post.begin("http://localhost:1234/view/signal");
  Bot = dlaBota.available();
  if (Bot)
  {
    x = czujnik;
    if (czujnik)
    {
      //  Post.POST("1");
      Bot.print(1);
    }
    else
    {
      Bot.print(0);
      // Post.POST("0");
    }
  }
  delay(100);
  // Post.end();
}
