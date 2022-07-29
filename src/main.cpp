#define BLINKER_WIFI

#include <Arduino.h>
#include <Blinker.h>

const int SwitchKey = 4;
const int PowerState = 12;

char auth[] = "";
char ssid[] = "";
char pswd[] = "";

BlinkerButton Button1("ButtonKey");

void Button1Callback(const String & state)
{
    if(state == "on" && digitalRead(PowerState) == 0)
    {
      Blinker.vibrate(500);
      Blinker.notify("Wait For Computer Open...");
      digitalWrite(SwitchKey, HIGH);
      Blinker.delay(500); 
      digitalWrite(SwitchKey, LOW);
      Blinker.delay(500);
      if (digitalRead(PowerState) == HIGH)
      {
        Button1.color("#00FF00");
        Button1.text("ON");
        Button1.print("on");
      }
     }

     if(state == "off" && digitalRead(PowerState) == 1)
     {
      Blinker.vibrate(500);
      Blinker.notify("Wait For Computer Close...");
      digitalWrite(SwitchKey,HIGH);
      Blinker.delay(500);
      digitalWrite(SwitchKey,LOW);
     }

    if(state == "press")  
    {
        digitalWrite(SwitchKey, HIGH);
    }
    
    if(state == "pressup") 
    {
      digitalWrite(SwitchKey, LOW);
    }
}

void heartbeat()
{
    if (digitalRead(PowerState) == HIGH)
    {
      Button1.color("#00FF00");
      Button1.text("ON");
      Button1.print("on");
    }else if (digitalRead(PowerState) == LOW){
      Button1.color("#FF0000");
      Button1.text("OFF");
      Button1.print("off");
    }
}

ICACHE_RAM_ATTR void Funcation()
{
  heartbeat();
}

void setup()
{
    pinMode(2,OUTPUT);
    digitalWrite(2,LOW);
    pinMode(SwitchKey,OUTPUT);
    digitalWrite(SwitchKey,LOW);
    pinMode(PowerState,INPUT);
    Blinker.begin(auth,ssid,pswd);
    Button1.attach(Button1Callback);
    Blinker.attachHeartbeat(heartbeat);
    attachInterrupt(digitalPinToInterrupt(12),Funcation,CHANGE);
}

void loop()
{
    Blinker.run();
}