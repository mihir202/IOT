#include <SoftwareSerial.h>
#include <DHT.h>
SoftwareSerial nodemcu(2,3);
#define DHTPIN A2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int msensor = 1; // moisture sensor is connected with the analog pin A1 of the Arduino
int msvalue = 0; // moisture sensor value
long int data;
int relay1 = 12; // to control the solenoid value
// to control the motor or anything else relay2


int sdata1 = 0;
int sdata2 = 0;
int sdata3 = 0;// Moisture sensor value


String cdata; // complete data
String cdata1;

void setup()
{
Serial.begin(9600);
nodemcu.begin(9600);
dht.begin(9600);
pinMode(msensor, INPUT);
pinMode(relay1, OUTPUT); 
pinMode(4, OUPUT);
digitalWrite(4, HIGH);

  }


void loop()
{
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();

   if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
if(nodemcu.available() == 0 )
{
     msvalue = analogRead(msensor);
  Serial.println(msvalue); 
  sdata1 = msvalue;

   cdata = cdata + sdata1+",";
   Serial.println(cdata);
   nodemcu.println(cdata);
   delay(1000); // 1000 milli seconds
   cdata = "";
   
}

if ( nodemcu.available() > 0 )
{
  data = nodemcu.parseInt();
  delay(100);
  Serial.println(data);

  if ( cdata > 350 )
  {
    digitalWrite(relay1, LOW);
  }
   else if ( cdata <= 350 )
  {
    digitalWrite(relay1, HIGH);
  }


}



}
