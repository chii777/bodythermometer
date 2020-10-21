#include <I2CLiquidCrystal.h>
#include <mglcd.h>
#include <Wire.h>
#include<stdio.h>
#include<math.h>
#define num 100
int i;
double average;
double vol;
double real;
double res;
double temp;
double tempr[num];
double sum =0;

I2CLiquidCrystal lcd(60, (bool)true);

void setup() {
Serial.begin(9600);
digitalWrite(13,HIGH);

lcd.begin(16, 1);
lcd.kana("mami");
delay(2000);
lcd.clear();
lcd.kana("body temperature");
delay(2000);

 vol = analogRead(A0);
 real = vol*5.0/1023.0;  //voltage
 res = 10000.0*real/(5.0-real); //resistor
 temp = (1/(((1/3380.0)*log(res/10000))+(1/298.0)))-273.0;

 
}


void loop() {
 sum = 0;
 vol = analogRead(A0);
 real = vol*5.0/1023.0;  //voltage
 res = 10000.0*real/(5.0-real); //resistor
 temp = (1/(((1/3380.0)*log(res/10000))+(1/298.0)))-273.0;

lcd.clear();


for (i = 9; i > 0; i--) {
 if(temp > 35.0){
   tempr[0] = temp;  // 温度を格納
   tempr[i] = tempr[i-1];
   //Serial.println(tempr[i]);
 }else{
   tempr[i] = tempr[i];
   //Serial.println(tempr[i]);
 } 
}

for (i = 0; i < 10;i++) {
  sum += tempr[i];
}

average = sum / 10;

if((average - temp) < 0.5){
  lcd.print(average - 0.6);
}else{
  lcd.print("stay");
}
Serial.println(temp);
Serial.print(",");
Serial.println(average);
//lcd.print(average - 0.6);

delay(1000);

}
