/*
  SimpleReceive
  This sketch displays text strings received using VirtualWire
  Connect the Receiver data pin to Arduino pin 11
*/
#define whiteLed 3
#define greenLed 4
#include <VirtualWire.h>
#include <NewPing.h>
int id = 49;
int loopTime = 0;
int detectionConstant = 3000;
int timer = 0;
char c = 0;
bool shotTrig = false;
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
  pinMode(whiteLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

}


void loop()
{


  if (sonar.ping_cm() == 0)
  {
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
    pinMode(10, INPUT);

  }

  if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    Serial.print("Received: ");


    c = message[0];
    Serial.println(c);
  }


  if (c == id)
  {
    timer = millis();
    loopTime = 0;
    digitalWrite(whiteLed, HIGH);
    Serial.println("before while");
    while (loopTime < detectionConstant)
    {

      if ((sonar.ping_cm() < 10) and (shotTrig == false) and (sonar.ping_cm() > 0) )
      {
        shotTrig = true;
        Serial.println("before green:");
        Serial.println(sonar.ping_cm());
        digitalWrite(greenLed, HIGH);
        delay(detectionConstant);
        digitalWrite(whiteLed, LOW);
        digitalWrite(greenLed, LOW);

      }

      loopTime = (millis() - timer);
      Serial.println(loopTime);

    }
    if (loopTime > (detectionConstant-1))
    {
      digitalWrite(whiteLed, LOW);
      c = 0;
      shotTrig = false;
    }
    c = 0;
  }

  else
  {
    c = 0;

  }




}

