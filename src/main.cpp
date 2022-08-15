#define BLINKER_WIFI

#include <Arduino.h>
#include <Blinker.h>

//开关按键引脚
const int SwitchKey = 4;

//状态检测引脚
const int PowerState = 12;

char auth[] = "";
char ssid[] = "";
char pswd[] = "";

BlinkerButton Button1("ButtonKey");

/**
  * @file    main.cpp
  * @brief   开关机按键回调函数
  * @param   unknow
  * @return  None
  * @version v1.0.0
  * @date    2022-08-15
  */
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


/**
  * @file    main.cpp
  * @brief   心跳包函数
  * @param   None
  * @return  None
  * @version v1.0.0
  * @date    2022-08-15
  */
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


/**
  * @file    main.cpp
  * @brief   状态引脚检测中断服务函数
  * @param   None
  * @return  None
  * @version v1.0.0
  * @date    2022-08-15
  */
ICACHE_RAM_ATTR void Funcation()
{
  heartbeat();
}


/**
  * @file    main.cpp
  * @brief   初始化函数
  * @param   None
  * @return  None
  * @version v1.0.0
  * @date    2022-08-15
  */
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


/**
  * @file    main.cpp
  * @brief   主循环函数
  * @param   None
  * @return  None
  * @version v1.0.0
  * @date    2022-08-15
  */
void loop()
{
    Blinker.run();
}