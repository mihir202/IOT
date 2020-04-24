#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2,3);
#include <DHT.h>
#include <SimpleTimer.h>
#define DHTPIN 2

int pinValue1;
int pinValue2;
int pinValue3;
int pinValue4;

// Your key to connect application with arduino system
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "DJKnight";
char pass[] = "Knight@276";

SimpleTimer timer;

String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

//for soild moisture
int firstVal ;

// This function sends Arduino's up time every second to Virtual Pin (1).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

 
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}




void setup()
{
  // Debug console
  DebugSerial.begin(9600);
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
    timer.setInterval(1000L,sensorvalue1);

}

void loop()
{
   if (Serial.available() == 0 )
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
   }
  
  if (Serial.available() > 0 )
  {
    rdata = Serial.read();
    myString = myString+ rdata;
   // Serial.print(rdata);
    if( rdata == '\n')
    {
   //  Serial.println(myString);
// new code
String l = getValue(myString, ',', 0);



firstVal = l.toInt();


  myString = "";
// end new code
    }
  }

}

void sensorvalue1()
{
int sdata = firstVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, sdata);

}


String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

// in Blynk app writes values to the Virtual Pin 10
BLYNK_WRITE(V10)
{
   pinValue1 = param.asInt(); // assigning incoming value from pin V10 to a variable

  Serial.print(pinValue1);

}


// in Blynk app writes values to the Virtual Pin 11
BLYNK_WRITE(V11)
{
   pinValue2 = param.asInt(); // assigning incoming value from pin V10 to a variable

  Serial.print(pinValue2);

}
