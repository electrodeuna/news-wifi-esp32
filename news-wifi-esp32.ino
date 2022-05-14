#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET  -1   //Reset pin for oled
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define BUTTON_PIN 12
#define BUTTON_PIN2 14

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DynamicJsonDocument doc(16384);

const char *ssid = "NOMBRE-WIFI";
const char *password = "PASSWORD_WIFI";
int botonVer, botonSig;
int i = 0;

String API_Key = "TU-API-KEY"; // Enter a 32 digit API
int httpCode;
String payload;
String menu;
int pagina=0;

void setup()
{
  pinMode(12, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { //turning on the oled
    for(;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 6);
  display.print("Noticias del dia");
  display.setCursor(0, 32);
  display.print("Creado por");
  display.setCursor(0, 40);
  display.print("Electronica De Una");   // To make it intresting, you an change the name, and make your own. 
  display.display();
  delay(2000);

  display.clearDisplay();
  WiFi.begin(ssid, password);

  display.setCursor(5, 16);
  display.print("Conectando");
   while (WiFi.status() != WL_CONNECTED)
   {
    display.print(".");
    display.display();
    delay(500);
   }
   display.setCursor(5,40);
   display.print("WiFi Conectado");
   display.display();  //to clear the old screen
   delay(1000);

   if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClient client;
    HTTPClient http;

	// country = ar(Argentina), co (Colombia), mx (Mexico), ve (Venezuela)
    http.begin(client,"http://newsapi.org/v2/top-headlines?country=ar&pageSize=10&apiKey=" + API_Key);
    httpCode = http.GET();

    if (httpCode > 0)
    {
      display.clearDisplay();
      display.display();
      display.setCursor(2, 10);
      display.print("Noticias de Argentina");
      display.display();
      delay(4000);
        
      payload = http.getString();
      
      payload.replace("á","a");
      payload.replace("é","e");
      payload.replace("í","i");
      payload.replace("ó","o");
      payload.replace("ú","u");
      payload.replace("ñ","ni");
      payload.replace("“","'");
      payload.replace("”","'");
      
      deserializeJson(doc, payload);    
    }
    http.end();
  }

  String titulo = doc["articles"][i]["title"];
  String fuente = doc["articles"][i]["source"]["name"];

  mostrar(titulo, "<Ver>", "<Sig>");
}

void mostrar(String titulo, String menuIz, String menuDer) {
  display.clearDisplay();
  display.display();
  display.setCursor(2, 0);
  display.print(titulo);
  display.setCursor(0, 56);
  display.print(menuIz);  
  display.setCursor(98, 56);
  display.print(menuDer); 
  display.display();
}

void loop ()
{
  botonVer = digitalRead(BUTTON_PIN);
  botonSig = digitalRead(BUTTON_PIN2);
  
  if(botonSig == LOW)
  {
    if(menu=="ver") {
      pagina = pagina+1;
      String titulo = doc["articles"][i]["description"];

      mostrar(titulo.substring(120,240), "<Volver>", "");
    }
    else {
      i = i+1;
      if(i == 10) {
        i=0;
      }
      String titulo = doc["articles"][i]["title"];

      mostrar(titulo, "<Ver>", "<Sig>");
    }
  }
  else if(botonVer == LOW)
  {
    if(menu=="ver") {
      menu="inicio";
      String titulo = doc["articles"][i]["title"];
      mostrar(titulo, "<Ver>", "<Sig>");
    }
    else {
      menu="ver";
      pagina = pagina+1;
      String titulo = doc["articles"][i]["description"];

      mostrar(titulo.substring(0,120), "<Volver>", ">>");
    }
  }
  delay(200);
}