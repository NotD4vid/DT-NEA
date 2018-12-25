/*
SimpleReceive
This sketch displays text strings received using VirtualWire
Connect the Receiver data pin to Arduino pin 11
*/
#include <VirtualWire.h>
#include <NewPing.h>

int timer = 0;
int c = 0;
bool r = false;
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
int distance = 0;
NewPing sonar(9, 10, 100);

void setup()
{
Serial.begin(9600);
Serial.println("Device is ready");

vw_setup(2000); // Bits per sec
vw_rx_start(); // Start the receiver
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);

}


void loop()
{
Serial.println(sonar.ping_cm());

if (sonar.ping_cm()==0)
{
    pinMode(10, OUTPUT);   
    digitalWrite(10, LOW);
    pinMode(10, INPUT);
    
}

if (vw_get_message(message, &messageLength)) // Non-blocking
{
Serial.print("Received: ");


c=message[0];
Serial.println(c);
}
if (c == 50)
{
  timer = millis();
  c=0;
  digitalWrite(3,HIGH);
  if ((millis()-timer)>1000)
  {
    digitalWrite(3,LOW);
  }
  if ((sonar.ping_cm()<10)and (sonar.ping_cm()>0))

{
  digitalWrite(4,HIGH);
  delay(1000);
  digitalWrite(4,LOW);
}
}
else
{ 
c=0;
delay(1000);
digitalWrite(3,LOW);
}




}

