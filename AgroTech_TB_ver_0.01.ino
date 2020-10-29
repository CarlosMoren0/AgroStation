//AgroTech Test B Version 0.01
/*-------------------------------------------------*/
//Librerias
#include <DHT.h>
#include <SFE_BMP180.h>
#include <Wire.h>

//Asignacion de Pines
const int pin_Tmp_Hmd = 2;//Temperatura y Humedad relativa (Digital)(DHT11)
const int pin_Lluvia_D = 3;//Luvia Digital (MH-RD)
const int pin_Lluvia_H = A7;//Luvia Analogo (MH-RD)
//const int pin_Luz_D = 3;//Luz Digital
const int pin_Luz = A2;//Luz Analogo (TEMT6000)
const int pin_Luz_UV = A6;//Luz UltraVioleta
/* Pines para sensor de presion(BMP180 GY-68) SDA = A4, SCK = A5 En Arduino UNO/NANO; 
SDA = 20 SCK = 21 En Arduino MEGA/DUE Comunicacion por I2C */
//Sensores por implementar: Sensor de Viento (Direccion y Velocidad),Riego, Evotranspiracion

//Variables para guardar valores de los sensores
float Temperatura;
float Humedad;
int Lluvia_D;
float Lluvia_H;
float Luz;
int Luz_UV;
SFE_BMP180 presion;//Variable auxiliar que contiene los valores del sensor de presion
DHT Tmp_Hmd(pin_Tmp_Hmd, DHT11);//Variable auxiliar que contiene los valores del sensor DTH11

//Variables auxiliares
const int No_Sensores = 5;
const int No_Pines = 8;
int cont = 0;
const int retraso = 50;
const int Tiempo = 10;//Tiempo de lectura en segundos

//Clase para sensores
/*class sensor
{
  public:
    string nombre;
	int pin, valor;
	bool status;
	sensor *sig;
	sensor *ant;
  
}*/

//Cabeceras
void obtenTmp_Hmd ();
void obtenLuz();
void obtenLluvia();
void mandaSerial();

//Main
/*-------------------------------------------------*/
void setup() 
{
  Tmp_Hmd.begin();
  inicializar_pines();
  pinMode(13,OUTPUT); 
  Serial.begin(9600);

}

void loop()
{
  obtenTmp_Hmd ();
  obtenLuz();
  obtenLluvia();
  mandaSerial();
  delay(Tiempo*1000);
}

//Funciones
/*-------------------------------------------------*/
void inicializar_pines()//Cambia a modo input a todos los pines utilizados
{
  pinMode(pin_Tmp_Hmd, INPUT);
  pinMode(pin_Lluvia_D, INPUT);
  pinMode(pin_Lluvia_H, INPUT);
  //pinMode(pin_Luz_D, INPUT);
  pinMode(pin_Luz, INPUT);
  pinMode(pin_Luz_UV, INPUT);
}

/*void estado_sensores()//Checa el funcionamiento de los sensores
{
  int aux;
  //int chk = TyH.read(pin_Tmp_Hmd);
  if (!presion.begin())
  {   
     Serial.println("Sensor de Presion Offline"); 
	 //while (1) {}
  } else if (!Tmp_Hmd.begin();)
  {
    Serial.println("Sensor de Temperatura y Presion Offline"); 
	//while (1) {}
    
  } else
  {   
     Serial.println("Sensor de Temperatura y Presion Online");
	 Serial.println("Sensor de Presion Online"); 
	 //while (1) {}
  } 
}*/
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

int obtenPresion()
{
  //
}

void obtenLuz()
{
  Luz = analogRead(pin_Luz);
  delay(retraso);
}

void obtenLluvia()
{
  Lluvia_H = analogRead(pin_Lluvia_H);
  Lluvia_D = digitalRead(pin_Lluvia_D);
  delay(retraso);
}

/*void mandaSerial()
{
  Serial.print("Humedad: ");
  Serial.print(Humedad);
  Serial.println(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(Temperatura);
  Serial.println(" *C ");
  Serial.print("Luminosidad: ");
  Serial.print(Luz * 0.0976);
  Serial.println(" %\t");
  Serial.print("Lluvia: ");
  if(Lluvia_D == LOW) 
  {
	Serial.print("Gotas en el Sensor "); 
  }
  else
  {
    Serial.print("Sensor seco ");
       
  }
  Serial.print(100-(Lluvia_H * 0.0976));
  Serial.println(" %\t");
  Serial.println("==================================================================");
}*/

void mandaSerial()
{
  Serial.print('T');
  Serial.print(Temperatura);
  Serial.print("\r");
  
  Serial.print('H');
  Serial.print(Humedad);
  Serial.print("\r");
  
  Serial.print('L');
  Serial.print(Luz * 0.0976);
  Serial.print("\r");
  
  Serial.print('Y');
  if(Lluvia_D == LOW) 
  {
	//Serial.print("Gotas en el Sensor ");
    Serial.print(1);	
  }
  else
  {
    //Serial.print("Sensor seco ");
	Serial.print(0);
       
  }
  Serial.print("\r");
  Serial.print('R');
  Serial.print(100-(Lluvia_H * 0.0976));
  Serial.print("\r");
  //Serial.println("==================================================================");
}

/*void inicializa_sensores()//
{

}*/
