//////Automatic-Pet-Food-Dispenser

#include <Wire.h> 
#include<SoftwareSerial.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);//RS,E,D4,D5,D6,D7   RW A GND
RTC_DS1307 rtc;

//VARIABLES
int  months=0, days=0;
uint16_t years=0;
int hours=0, mins=0, seconds=0;
int alarm_hour=9, alarm_min=10;
int confifh=0, contfh=0, check=0;
int daysmax[12]{ 31,28,31,30,31,30,31,31,30,31,30,31 };
float hightime,time,distance;
int porcent;
float tanque=21; //altura del tanque de almacenamiento
int menu=1, contmenu=1;
int breed=1, manual=0, food=1, active=1;

/////BUTTONS
int bt_selec=2, bt_back=3, bt_up=18, bt_down=19;
/////LEDS
int l_green=22 , l_red=23;
int Fin_up=53;
//SWITCHS
int Fin_down=51;
/////ultrasonic
int ECHOPIN=10;
int TRIGGERPIN=11;

int inputPin = A2;

//Definimos los pines a usar
int CoilUA=31;
int CoilUB=33;
int CoilDC=35;
int CoilDD=37; 

void setup() {
  Serial.begin(9600);
  servoMotor.attach(10);
  // 
25/5000
//Moves to position 0º
  servoMotor.write(60);
  delay(1000);

  Wire.begin(); // Port I2C init
  rtc.begin(); // Comunication init
  pinMode(bt_selec,INPUT_PULLUP); 
  pinMode(bt_back,INPUT_PULLUP);
  pinMode(bt_up,INPUT_PULLUP);
  pinMode(bt_down,INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(bt_selec), selec, RISING);
  attachInterrupt(digitalPinToInterrupt(bt_back), back, RISING);
  attachInterrupt(digitalPinToInterrupt(bt_up), up, RISING);
  attachInterrupt(digitalPinToInterrupt(bt_down), down, RISING);

  pinMode (inputPin, INPUT);
  
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print(" AUTOMATIC PET    ");
  lcd.setCursor(1,1);
  lcd.print("    DISPENSER   ");
  delay(2000);
  lcd.clear();
if (!rtc.begin()) {
      lcd.print(F("Couldn't find RTC"));
      while (1);
   }
    rtc.adjust(DateTime(2020, 02, 22, 12, 0, 0));
   delay(3000);
  lcd.setCursor(0,0);
  lcd.print("DATE");
  DateTime now = rtc.now(); // Get the date from RTC
  lcd.setCursor(0,1);
  lcd.print(now.year(), DEC); // Year
  lcd.print('/');
  lcd.print(now.month(), DEC); // Month
  lcd.print('/');
  lcd.print(now.day(), DEC); //day
  lcd.print(' ');
  lcd.print(now.hour(), DEC); // hours
  lcd.print(':');
  lcd.print(now.minute(), DEC); // mins
  lcd.print(':');
  lcd.print(now.second(), DEC); // seconds
  delay(2000);
  lcd.clear();
  years=now.year();
  months=now.month();
  days=now.day();
  hours=now.hour();
  mins=now.minute();
  seconds=now.second();
  
}

void loop() {
if(manual==0){
  if (check==1){
      rtc.adjust(DateTime(years, months, days, hours, mins, seconds));
      lcd.clear();
      confifh=1;
      check=0;
      Serial.println(contfh);
      Serial.println(confifh);
      Serial.println(check);
      
      }

  if (confifh==0){
    //rtc.adjust(DateTime(years, months, days, hours, mins, seconds));
         
      /*DateTime now = rtc.now();
      hours = rtc.now().hour();
      mins = rtc.now().minute();
      seconds = rtc.now().second();
      months = rtc.now().month();
      years = rtc.now().year();
      days = rtc.now().day();*/
      Serial.println(contfh);
      Serial.println(confifh);
      Serial.println(check);
      lcd.setCursor(0,0);
      lcd.print("Configurar FECHA");
      lcd.setCursor(0,1);
      lcd.print(years, DEC); // year
      lcd.print('/');
      lcd.print(months, DEC); // month
      lcd.print('/');
      lcd.print(days, DEC); // day
      lcd.print(' ');
      lcd.print(hours, DEC); // hours
      lcd.print(':');
      lcd.print(mins, DEC); // mins
      lcd.print(':');
      lcd.print(seconds, DEC); // 
      delay(150);
      lcd.setCursor(0,0);
      lcd.print("                ");
      delay(150);
    }
    //////////////LUEGO DE PROGRAMAR LA HORA
    else if (confifh==1){
   
      //distance=ultrasonic();
      DateTime now = rtc.now();
      hours = rtc.now().hour();
      mins = rtc.now().minute();
      seconds = rtc.now().second();
      months = rtc.now().month();
      years = rtc.now().year();
      days = rtc.now().day();
      
      lcd.setCursor(0,0);
      /*lcd.print(years, DEC); // year
      lcd.print('/');
      lcd.print(months, DEC); // Month
      lcd.print('/');
      lcd.print(days, DEC); // day
      lcd.print(' ');*/
      lcd.print(hours, DEC); // hours
      lcd.print(':');
      lcd.print(mins, DEC); // mins
      lcd.print(':');
      lcd.print(seconds, DEC); // seconds
      lcd.setCursor(10,0);
      lcd.print(" A:");
      lcd.print(alarm_hour, DEC); // hours
      lcd.print(':');
      lcd.print(alarm_min, DEC); // mins
      porcent=ultrasonic();
      lcd.setCursor(0,1);
      lcd.print("%:"); // year
      lcd.print(porcent, DEC);
      lcd.print("            ");
      lcd.setCursor(6,1);
      lcd.print("R: "); // year
      switch(breed){
          case 1:
      lcd.print("Small"); 

          break;

          case 2:
           lcd.print("Medium ");
           
          break;

         case 3:
          lcd.print("Big ");
          break;
          }
          lcd.setCursor(11,1);
      lcd.print("C: "); // year
      switch(food){
          case 1:
          lcd.print(food);
      lcd.print("    "); 

          break;

          case 2:
           lcd.print(food);
      lcd.print("    "); 
           
          break;

         case 3:
          lcd.print(food);
      lcd.print("    "); 
          break;
          }
      }
      /*lcd.print(now.year(), DEC); // year
      lcd.print('/');
      lcd.print(now.month(), DEC); // month
      lcd.print('/');
      lcd.print(now.day(), DEC); // day
      lcd.print(' ');
      lcd.print(now.hour(), DEC); // hours
      lcd.print(':');
      lcd.print(now.minute(), DEC); // mins
      lcd.print(':');
      lcd.print(now.second(), DEC); // seconds*/
      
      else if(confifh==2){
        switch(contmenu){
          case 1:
          ///////breed
          lcd.setCursor(0,0);
      lcd.print(" MENU                 "); 
      lcd.setCursor(0,1);
      lcd.print("Kind of breed      "); 

          break;

          case 2:
          //////NUMERO DE foodS
        lcd.setCursor(0,0);
      lcd.print(" MENU                "); 
      lcd.setCursor(0,1);
      lcd.print("Num of foods     ");
          break;

         case 3:
          ///////manual mode
          lcd.setCursor(0,0);
      lcd.print(" MENU               "); 
      lcd.setCursor(0,1);
      lcd.print("Manual Mode       ");
          break;
          }}

          else if(confifh==3){
            
             switch(contmenu){
          case 1:
          ///////breed
          lcd.setCursor(0,0);
      lcd.print("Kind of breed        "); 
      switch(menu){
        ///////Small
          case 1:
          lcd.setCursor(0,1);
          lcd.print("Small         ");
          
          
          break;
          ///////Medium
          case 2:
          lcd.setCursor(0,1);
          lcd.print("Medium         ");
          
          break;
          ///////Big
          case 3:
          lcd.setCursor(0,1);
          lcd.print("Big           ");
          
          break;
      }
          break;

          case 2:
          //////# of foods
        lcd.setCursor(0,0);
      lcd.print("Num of foods       "); 
      switch(menu){
        ///////one
          case 1:
          lcd.setCursor(0,1);
          lcd.print("One food        ");
          
          break;
          ///////two
          case 2:
          lcd.setCursor(0,1);
          lcd.print("Two foods      ");
          
          break;
          ///////three
          case 3:
          lcd.setCursor(0,1);
          lcd.print("Three foods       ");
          
          break;
      }
          break;

         case 3:
          ///////manual mode
          lcd.setCursor(0,0);
      lcd.print("Manual Mode       "); 
switch(menu){
        ///////small
          case 1:
          lcd.setCursor(0,1);
          lcd.print("Open gate    ");
          
          break;
          ///////medium
          case 2:
          lcd.setCursor(0,1);
          lcd.print("Close gate    ");
          
          break;
          ///////big
          case 3:
          lcd.setCursor(0,1);
          lcd.print("AUTOMATIC        ");
          
          break;
      }
      
          break;
          }

            }

            
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

          
                  
          }
          


           if(manual!=0){
          lcd.setCursor(0,0);
          lcd.print("Manual Mode     ");
          lcd.setCursor(0,1);
          lcd.print("BACK AUTOMATIC    ");
          if(manual==1){

       ///////Open gate manual mode 
    
        servoMotor.write(105);
        delay(500*breed);
        /////// Close gate////
        servoMotor.write(60);

        /*if (digitalRead(Fin_down)==LOW){
        manual=0;
        }*/
          }
          if(manual==2){

       ///////Close gate manual mode 
       
        /////// Close gate////
        servoMotor.write(60);
        /*if (digitalRead(Fin_up)==LOW){
        manual=0;
        }*/
          }
        
       /* porcent=ultrasonic();
      lcd.setCursor(0,1);
      lcd.print("%: "); // year
      lcd.print(porcent);
      
      lcd.setCursor(8,1);
      lcd.print("  "); // year
      lcd.print(analogRead (inputPin));*/
}

}

  int ajustehours (int hora){
    if(hora>=24){
      hora=0;
      }
      else if(hora<0){
        hora=23;
        }
      else{
        hora=hora;
        }
        return hora;
    }

    int ajustemonths (int month){
    if(month>=13){
      month=1;
      }
      else if(month<0){
        month=12;
        }
      else{
        month=month;
        }
        return month;
    }
  int ajustedays (int day, int month){
    if(day>=daysmax[month]){
      day=1;
      }
      else if(day<0){
        day=daysmax[month];
        }
      else{
        day=day;
        }
        return day;
    }
int ajustemins (int minuto){
    if(minuto>=60){
      minuto=0;
      }
      else if(minuto<0){
        minuto=59;
        }
      else{
        minuto=minuto;
        }
        return minuto;
    }

   uint16_t ajusteyears (uint16_t ano){
    if(ano>=2040){
      ano=2000;
      }
      else if(ano<2000){
        ano=2040;
        }
      else{
        ano=ano;
        }
        return ano;
    }

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

    ///////////////////Selec Button//////////////
void selec(){
  delay(50);
  if (manual==0){
  if (confifh==0){
    if (contfh==6){
    Serial.println("Change Configuration");
          check=1;
            }
            else{
              contfh+=1;
              }
            }
      else if (confifh==1){
        confifh=2;
        lcd.clear();
        }
        else if (confifh==2){
        confifh=3;
        }

          else if(confifh==3){
            
             switch(contmenu){
          case 1:
          ///////breed
      switch(menu){
        ///////small
          case 1:
          breed=1;
          
          break;
          ///////medium
          case 2:
          breed=2;
          break;
          ///////big
          case 3:
          breed=3;
          break;
      }
          break;

          case 2:
          //////NUMERO DE foodS
      switch(menu){
        ///////one
          case 1:
          food=1;
          break;
          ///////two
          case 2:
          food=2;
          break;
          ///////three
          case 3:
          food=3;
          break;
      }
          break;

         case 3:
          ///////manual mode
        switch(menu){
        ///////small
          case 1:
          manual=1;
          break;
          ///////medium
          case 2:
          manual=2;
          break;
          ///////big
          case 3:
          manual=0;
          break;
      }
      
          break;
          }
confifh=1;
}
}
if (manual!=0){
  if (manual==1){
    manual=2;
    }
    if (manual==2){
    manual=1;
    }
  
  }
}

/////////////////back button/////////////////////
  void back(){
    delay(50);
    if (manual==0){
    if (confifh==0){
    if (contfh>=1&&contfh<=6){
        contfh=contfh-1;
        }
        else{
          contfh=1;
          }
          
    }
    else if(confifh==2){
          confifh=1;
          }
    else if(confifh==3){
          confifh=2;
          }
          else if(confifh==4){
          confifh=3;
          }
  }
  if (manual!=0){
      ////Close gate
      while(digitalRead(Fin_up)==HIGH){
        giroAntiHorario(5);
        }
    manual=0;
    }
  
  }

  ///////////////////////////inc button////////////////////////
  void up(){
    delay(20);
     if (confifh==0){
        switch (contfh){
          //Configurar years 
          case 1:
          years+=1;
          years=ajusteyears(years);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds

          break;

          case 2:
//// Configurar months
             months+=1;
             months=ajustemonths(months);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds
          break;

          case 3:
//// Configurar days
             days+=1;
             days=ajustedays(days, months);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds

          break;

          case 4:
          //// Configurar hours
             hours=hours+1;
             hours=ajustehours(hours);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds

          break;

          case 5:
          //// Configurar mins
             mins+=1;
             mins=ajustemins(mins);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds
          break;
          }
      }
    else if(confifh==2){
      if (contmenu==4){
        contmenu=1;
        }
        else{
      contmenu+=1;
        }
      }

      else if(confifh==3){
      if (menu==4){
        menu=1;
        }
        else{
      menu+=1;
        }
      }
  
  
  }
  /////////////////Dec button/////////////////////////
  void down(){
    delay(20);
     if (confifh==0){
         switch (contfh){
          //Configurate years 
          case 1:
          years=years-1;
          years=ajusteyears(years);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds
          break;

          case 2:
//// Configurate months
            months=months-1;
            months=ajustemonths(months);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds
          break;

          case 3:
//// Configurate days
             days=days-1;
             days=ajustedays(days, months);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds
          break;

          case 4:
          //// Configurate hours
            hours=hours-1;
            hours=ajustehours(hours);
            lcd.setCursor(0,0);
            lcd.print("Configurar FECHA");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds

          break;

          case 5:
          //// Configurar mins
             mins=mins-1;
             mins=ajustemins(mins);
            lcd.setCursor(0,0);
            lcd.print("Date Configuration");
            lcd.setCursor(0,1);
            lcd.print(years, DEC); // year
            lcd.print('/');
            lcd.print(months, DEC); // month
            lcd.print('/');
            lcd.print(days, DEC); // day
            lcd.print(' ');
            lcd.print(hours, DEC); // hours
            lcd.print(':');
            lcd.print(mins, DEC); // mins
            lcd.print(':');
            lcd.print(seconds, DEC); // seconds

          break;
          }
      
    }
    else if(confifh==2){
      if (contmenu==0){
          contmenu=3;
        }
        else{
          contmenu=contmenu-1;
          }
      }

      else if(confifh==3){
     if (menu==0){
         menu=3;
        }
        else{
          menu=menu-1;
          }
      }
  }

  void giroHorario(int time){
  digitalWrite(CoilUA, HIGH);
  digitalWrite(CoilUB, LOW);
  digitalWrite(CoilDC, HIGH);
  digitalWrite(CoilDD, LOW);
  delay(time);
  digitalWrite(CoilUA, LOW);
  digitalWrite(CoilUB, HIGH);
  digitalWrite(CoilDC, HIGH);
  digitalWrite(CoilDD, LOW);
  delay(time);
  digitalWrite(CoilUA, LOW);
  digitalWrite(CoilUB, HIGH);
  digitalWrite(CoilDC, LOW);
  digitalWrite(CoilDD, HIGH);
  delay(time);  
  digitalWrite(CoilUA, HIGH);
  digitalWrite(CoilUB, LOW);
  digitalWrite(CoilDC, LOW);
  digitalWrite(CoilDD, HIGH);
  delay(time);  
}

void giroAntiHorario(int time){
  digitalWrite(CoilUA, HIGH);
  digitalWrite(CoilUB, LOW);
  digitalWrite(CoilDC, LOW);
  digitalWrite(CoilDD, HIGH);
  delay(time);
  digitalWrite(CoilUA, LOW);
  digitalWrite(CoilUB, HIGH);
  digitalWrite(CoilDC, LOW);
  digitalWrite(CoilDD, HIGH);
  delay(time);
  digitalWrite(CoilUA, LOW);
  digitalWrite(CoilUB, HIGH);
  digitalWrite(CoilDC, HIGH);
  digitalWrite(CoilDD, LOW);
  delay(time);  
  digitalWrite(CoilUA, HIGH);
  digitalWrite(CoilUB, LOW);
  digitalWrite(CoilDC, HIGH);
  digitalWrite(CoilDD, LOW);
  delay(time);  
  delay(time);  
}
