#include <RH_ASK.h>
#include <SPI.h> 
#include <GY6050.h>

GY6050 acc(0x68); //I2C address of MPU6050
RH_ASK driver;
const char *msg;
void setup()
{
    acc.initialisation();   //initialize acc obj
    Serial.begin(9600);    // Debugging only
    if (!driver.init())
    {
         Serial.println("init failed");
    }
}

void loop()
{    
       int AcX=acc.refresh('A', 'X'); //Acccelration along X axis
       int AcY=acc.refresh('A', 'Y'); //Acccelration along Y axis
       int AcZ=acc.refresh('A', 'Z'); //Acccelration along Z axis
       delay(25); 
       if(AcX>=65 && AcX<=80)
       { 
          msg="F";
          Serial.println("Front");
          
       }
       else if(AcY<=-10 && AcY>=-35)
          {
            Serial.println("Left");
            msg="L";
          }
       else if(AcY>=10 && AcY<=35)
          {
            Serial.println("Right");
            msg="R";
          }
       else if(AcZ<=-10 && AcX>=-80)
          {
            Serial.println("Back");
            msg="B";
          }
       else
          {
            Serial.println("Stop");
            msg="S";
          } 
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(500);
}
