<a name="top"></a>
# Automatic-Pet-Food-Dispenser

![Arduino Project](https://github.com/FreakJazz/Automatic-Pet-Food-Dispenser/blob/master/images/logo_arduino.png)

<a name="item1"></a>
## Description

Automatic pet food dispenser with time programming, and level meter in Arduino MEGA with I2C communication
![Arduino Project](https://github.com/FreakJazz/Automatic-Pet-Food-Dispenser/blob/master/images/ARDUINO_MEGA.jpg)

<a name="item2"></a>
## Contents
- [Description](#item1)
- [Contents](#item2)
- [Library Installation](#item3)
- [Configuration](#item4)
- [Programation](#item5)
- [Results](#item6)
- [Contributing](#item6)

[Up](#top)

<a name="item3"></a>
## Library Installation

In order to this project several libraries are agreed 

### LiquidCrystal
![Arduino Project](https://github.com/FreakJazz/Automatic-Pet-Food-Dispenser/blob/master/images/LCD.jpg)

This library is used to LCD 16x2

```C++
#include <LiquidCrystal.h>
```

### DS1307 RTC I2C

![Arduino Project](https://github.com/FreakJazz/Automatic-Pet-Food-Dispenser/blob/master/images/DS1307.jpg)

This two libraries are used to DS1307 RTC I2C

```C++
#include <Wire.h> 
#include "RTClib.h"
```
### SERVO

![Arduino Project](https://github.com/FreakJazz/Automatic-Pet-Food-Dispenser/blob/master/images/servo.jpg)

Servo library is used to open and close the gate

```C++
#include <Servo.h>
```

[Up](#top)

<a name="item4"></a>
## Configuration

### LCD 16x2
```C++
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);//RS,E,D4,D5,D6,D7   RW A GND
lcd.begin(16,2);
```

### DS1307 RTC
```C++
RTC_DS1307 rtc;
Wire.begin(); // Port I2C init
rtc.begin(); // Comunication init
if (!rtc.begin()) {
      lcd.print(F("Couldn't find RTC"));
      while (1);
   }
    rtc.adjust(DateTime(2020, 02, 22, 12, 0, 0));
```

### BUTTONS OF CONFIGURATION SYSTEM

```C++
pinMode(bt_selec,INPUT_PULLUP); 
pinMode(bt_back,INPUT_PULLUP);
pinMode(bt_up,INPUT_PULLUP);
pinMode(bt_down,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(bt_selec), selec, RISING);
attachInterrupt(digitalPinToInterrupt(bt_back), back, RISING);
attachInterrupt(digitalPinToInterrupt(bt_up), up, RISING);
attachInterrupt(digitalPinToInterrupt(bt_down), down, RISING);
```

### SERVO 

```C++
 servoMotor.attach(10);
  // 
//Moves to position 0º
  servoMotor.write(60);
```

### ULTRASONIC
```C+++
/////ultrasonic
int ECHOPIN=10;
int TRIGGERPIN=11;
```

<a name="item5"></a>
## Programation

### OPEN GATE 

```C++
if(hours!=alarm_hour&&mins!=alarm_min){
    digitalWrite(l_green,LOW);
    active=1;
  }
  if(hours==alarm_hour&&mins==alarm_min){
    digitalWrite(l_green,HIGH);
      ///////Open gate///////
  delay(10*breed);
  servoMotor.write(60);  
    if(active==1){
        alarm_hour=food*alarm_hour;
      } 
    }
```
### CLOSE GATE 
```C++
if(manual==2){
///////Close gate manual mode 

/////// Close gate////
servoMotor.write(60);
/*if (digitalRead(Fin_up)==LOW){
manual=0;
}*/
    }
```
### ULTRASONIC
```C++
float ultrasonic(){
  digitalWrite(TRIGGERPIN,LOW);
  delayMicroseconds(1);
  digitalWrite(TRIGGERPIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGERPIN,LOW);
  //Calculo de la distance midiendo en el time que el pin ECHO esta en alto
  hightime = pulseIn(ECHOPIN, HIGH);
  time=hightime/2;
  //La velocidad del sonido es 340 m/s o 29 microseconds por centimetro
  distance=time/29;
  distance=21-distance;
  porcent=(distance*100)/20;  //porcentaje del plato
  if (porcent<=0){
    porcent=0;
    }
    if (porcent>=92){
    porcent=100;
    }
    if (porcent<=25){
    digitalWrite(l_red,HIGH);
    }
    if (porcent>25){
    digitalWrite(l_red,LOW);
    }
  return porcent;
  }
```

[Up](#top)

<a name="item6"></a>
## Result

### Pet Dispenser

![Automatic Pet Dispenser](![Arduino Project](https://github.com/FreakJazz/Automatic-Pet-Food-Dispenser/blob/master/images/pet1.jpg))

![Automatic Pet Dispenser](![Arduino Project](https://github.com/FreakJazz/Automatic-Pet-Food-Dispenser/blob/master/images/pet2.jpg))

[Up](#top)

<a name="item7"></a>
## Contributing

**KATHERINE QUIÑONEZ** 

[GitHub](https://github.com/), [LinkedIn](https://www.linkedin.com/)

**JAZMIN RODRIGUEZ** 

[GitHub](https://github.com/FreakJazz), [LinkedIn](https://www.linkedin.com/in/jazm%C3%ADn-rodr%C3%ADguez-80b580133/)

[Up](#top)