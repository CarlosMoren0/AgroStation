/*Arduino*/
/*------------------------------------------------------------*/
/*Este programa utiliza el sensor DHT11 para obtener temperatura y Humedad, 
esos datos se mandaran por medio de comunicacion serial a un modulo ESP8266*/
#include <DHT.h>

const int pin_Tmp_Hmd = 53;//Temperatura y Humedad relativa (Digital)(DHT11)
float Temperatura = 0;
float Humedad;
DHT Tmp_Hmd(pin_Tmp_Hmd, DHT11);

const int segundos = 20;//Tiempo de retraso en segundos
const int minutos = 0;//Minutos
const int retraso = 50;

void obtenTmp_Hmd();//Funcion para leer la temperatura y humedad del sensor
void mandaTmp_Hmd();//Manda los datos obtenidos por comunicacion serial 

void setup() 
{
  Serial.begin(9600);//Para mostrar datos en el monitor serial
  Serial3.begin(9600);/*La placa Arduino DUE cuenta con 4 pares de pines para
  establecer comunicacion serial, se utilizaran los pines TX3 y RX3 */
  Tmp_Hmd.begin();
  pinMode(pin_Tmp_Hmd, INPUT);
}

void loop() 
{
  obtenTmp_Hmd();
  mandaTmp_Hmd();
  delay((minutos * 60 + segundos) * 1000);
}

void obtenTmp_Hmd ()
{
  Humedad = Tmp_Hmd.readHumidity();
  Temperatura = Tmp_Hmd.readTemperature();
  if (isnan(Humedad) || isnan(Temperatura)) 
  {
		Serial.println("Error al leer el sensor DHT11!");
   for(int i =0; i < 3; i++)
   {
     digitalWrite(13, HIGH);
     delay(1000);
     digitalWrite(13, LOW);
     delay(1000);
   }
		//return;
	}
	delay(retraso);
}
 
 void mandaTmp_Hmd()
 {
	Serial.print(Temperatura);
	Serial.println();
	Serial3.print(Temperatura);//(Pines TX3 y RX3)
	Serial3.print("\r");
 }
