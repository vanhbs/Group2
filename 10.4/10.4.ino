#include <Servo.h>
Servo LWheel,RWheel;
int LGreySensor=A0,RGreySensor=A1,Trig=8,Echo=9;
void setup() {
  Serial.begin(9600);
  
  LWheel.attach(3);
  RWheel.attach(2);

  pinMode(LGreySensor,INPUT);
  pinMode(RGreySensor,INPUT);
  
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
}

float measureDistance()
{
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  float distance = pulseIn(Echo,HIGH)*0.034/2;
  Serial.print("Current distance:");
  Serial.print(distance);
  return distance;
}

void spin()
{
  LWheel.writeMicroseconds(1560);
  RWheel.writeMicroseconds(1575);

}

void setAdvance()
{
  LWheel.writeMicroseconds(1560);
  RWheel.writeMicroseconds(1480);
  //根据实际要求调节速度
}

void setTurnLeft()
{
  LWheel.writeMicroseconds(1500);
  RWheel.writeMicroseconds(1335);
}

void setTurnRight()
{
  LWheel.writeMicroseconds(1645);
  RWheel.writeMicroseconds(1500);
}

void setStill()
{
  LWheel.writeMicroseconds(1510);
  RWheel.writeMicroseconds(1525);
}

void loop()
{
  setAdvance();
  while(1)
  {
    if(measureDistance()<20)
    {
      Serial.println("Avoiding a crush...");
      setTurnRight();
      delay(1550);
      setAdvance();
      delay(2200);
      setTurnLeft();
      delay(860);
      setAdvance();
      delay(6250);
      setTurnLeft();
      delay(890);
      setAdvance();
      delay(2200);
      setTurnRight();
      delay(900);
      setAdvance();
    }
    if(analogRead(LGreySensor)>400 && analogRead(RGreySensor)<700)//实测数据
    {
      setTurnRight();
      delay(50);
    }
    else if(analogRead(RGreySensor)>400 && analogRead(LGreySensor)<700)//实测数据
    {
      setTurnLeft();
      delay(50);
    }
    else
    {
      setAdvance();
      delay(50);
    }
  }
}
