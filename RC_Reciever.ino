#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;
char* variable;
int rm1 = 5;
int rm2 = 6;
int lm1 = 7;
int lm2 = 8;
void setup()
{
    Serial.begin(9600);  // Debugging only
    pinMode(rm1, OUTPUT);
    pinMode(rm2, OUTPUT);
    pinMode(lm1, OUTPUT);
    pinMode(lm2, OUTPUT);
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
    uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);  
      if ((char*)buf[0]=='F')
      {
        digitalWrite(rm1,HIGH);
        digitalWrite(rm2,LOW);
        digitalWrite(lm1,HIGH);
        digitalWrite(lm2,LOW);
      }
      if ((char*)buf[0]=='B')
      {
        digitalWrite(rm1,LOW);
        digitalWrite(rm2,HIGH);
        digitalWrite(lm1,LOW);
        digitalWrite(lm2,HIGH);
      }
      if ((char*)buf[0]=='R')
      {
        digitalWrite(rm1,LOW);
        digitalWrite(rm2,LOW);
        digitalWrite(lm1,HIGH);
        digitalWrite(lm2,LOW);
      }
      if ((char*)buf[0]=='L')
      {
        digitalWrite(rm1,HIGH);
        digitalWrite(rm2,LOW);
        digitalWrite(lm1,LOW);
        digitalWrite(lm2,LOW);
      }
      if ((char*)buf[0]=='S')
      {
        digitalWrite(rm1,LOW);
        digitalWrite(rm2,LOW);
        digitalWrite(lm1,LOW);
        digitalWrite(lm2,LOW);
      }
      
     }
       
 }
    
