/*ESP8266*/
/*-------------------------------------------------------*/
/*El modulo ESP8266 recibe datos de la placa Arduino (DUE) por medio de 
comunicacion serial y sube esos datos a la pagina thingspeak.com*/

#include "ThingSpeak.h"//
#include "secrets.h"//Configuracion de la Red

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

#include <ESP8266WiFi.h>

char ssid[] = SECRET_SSID;   
char pass[] = SECRET_PASS;
//int keyIndex = 0;      
WiFiClient  client;

char buff [10];
volatile byte indx;
char c = NULL;

const int segundos = 1;//Tiempo de retraso en segundos
const int minutos = 0;//Minutos
const int canal = 2;//Campo donde se guardara el dato a subir
const int retraso = 50;

void conectaWiFi();//Conecta a una red WiFi con la SSID configurada en secrets.h
void publicaEnThingSpeak();//Funcion para subir datos a thingspeak.com
void leeSerial();//Funcion para leer datos del serial (En este caso provenientes de un arduino)

void setup() 
{
  //Serial.begin(115200);
  Serial.begin(9600);
  delay(100);
  
  WiFi.mode(WIFI_STA);//Configura el modulo en modo estacion
  conectaWiFi();
  ThingSpeak.begin(client);//Inicia comunicacion con la pagina thingspeak.com
}

void loop() 
{
  leeSerial(); 
  delay((minutos * 60 + segundos)*1000);
}

void conectaWiFi()
{
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print("Conenctando a la SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) 
  {
      WiFi.begin(ssid, pass); // Conectar a una red WPA/WPA2. Cambiar este comando si se usa una red WEP
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConectado.");
  }
}

void publicaEnThingSpeak()
{
  Serial.print("Temperatura = ");
  Serial.println(buff);
  int httpCode = ThingSpeak.writeField(myChannelNumber, canal, buff, myWriteAPIKey);

  if (httpCode == 200) 
  {
    Serial.println("Dato publicado con exito.");
  }
  else 
  {
    Serial.println("Hubo un Problema. Codigo de error HTTP " + String(httpCode));
  }
}

void leeSerial()
{
  if (Serial.available() > 0) 
  {
    
    c = Serial.read();//Lee un caracter del serial
    if (indx < sizeof buff) 
    {
      if (c == '\r') //Final del Mensaje
      { 
        publicaEnThingSpeak();//Al termino de la lectura se sube el dato a la pagina
        indx= 0; //Regresa la posicion a cero
        delay(retraso);
        
      }
      else
      {
        //Serial.print(c);
        buff[indx] = c; //Guarda el dato en el buffer
        indx++;
      }
    }
  }
}
/*void leeSerial()
{
  if (Serial.available() > 0) 
  {
    byte indx= 0; 
    char c = Serial.read();//Lee un caracter del serial
    while (indx < sizeof buff || c != '\r') 
    {
      buff[indx] = c; //Guarda el dato en el buffer
	    c = Serial.read();
      indx++;
	    delay(retraso);
    }
  }
}*/
