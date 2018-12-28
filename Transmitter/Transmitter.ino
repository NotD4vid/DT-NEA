/*
SimpleSend
This sketch transmits a short text message using the VirtualWire library
connect the Transmitter data pin to Arduino pin 12
*/
#include <SoftwareSerial.h>
#include <VirtualWire.h>
#define whiteLed 3
SoftwareSerial mySerial(7, 8);
bool radioMode = false;
// False means manual, true means random
int msg = 1;
int c;
int moduleNo = 2;
int randInt;



void setup()
{
// Initialize the IO and ISR
Serial.begin(9600);
vw_setup(2000); // Bits per sec
Serial.println("Finished setup");
mySerial.begin(9600);
randomSeed(analogRead(0));
}
void loop()
{


  
if (mySerial.available()) {
    c = mySerial.read();  
    Serial.println("Got input:");
    Serial.println(c);
    Serial.println(char(c));
    if (c==42)
    {   
      Serial.println("random mode on");
      digitalWrite(whiteLed, HIGH);
      radioMode=true;
      c=0;
    }
    if (c==83)
    {
      Serial.println("manual mode on");
      digitalWrite(whiteLed, LOW);
      radioMode=false;
      c=0;
    }  
  }

if (radioMode==true)
{

    if (c==100)
   {
    randInt=random(1,moduleNo+1);
    Serial.println(randInt);
   if (randInt==1)
    {
      send("1");
    }
   if (randInt==2)
    {
      send("2");
    }
   if (randInt==3)
    {
      send("3");
    }
   if (randInt==4)
    {
      send("4");
    }
   if (randInt==5)
    {
      send("5");
    }     
    }
    c=0;
   }

 if (radioMode==false)
 {
    
    if (c==49)
    {
      send("1");
      c=0;
    }
    if (c==50)
    {
      send("2");
      c=0;
    }
    if (c==51)
    {
      send("3");
      c=0;
    }
    if (c==52)
    {
      send("4");
      c=0;
    }
    if (c==53)
    {
      send("5");
      c=0;
    }
    
 }
}










void send (char *message)
{
Serial.write("message in sending: ");
Serial.println(message);
vw_send((uint8_t *)message, strlen(message));
vw_wait_tx(); // Wait until the whole message is gone
}

