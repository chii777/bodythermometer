#include <I2CLiquidCrystal.h>
#include <mglcd.h>
#include <Wire.h>
#include<stdio.h>
#include<math.h>
#define num 100
int i;
float average;
int vol;
float real;
float thr;
float temp;
short tempr[num];
float sum =0;
float val;



I2CLiquidCrystal lcd(60, (bool)true);

void setup() {
Serial.begin(9600);

lcd.begin(16, 1);
lcd.kana("mami");
delay(2000);
lcd.clear();
lcd.kana("body temperature");
delay(2000);

 vol = analogRead(A0);
 real = vol*5.0/1023.0;  //voltage
 thr = 10000.0*real/(5.0-real); //resistor
 temp = (1/(((1/3380.0)*log(thr/10000))+(1/298.0)))-273.0;

 
}


void loop() {

 vol = analogRead(A0);
 real = vol*5.0/1023.0;  //voltage
 thr = 10000.0*real/(5.0-real); //resistor
 temp = (1/(((1/3380.0)*log(thr/10000))+(1/298.0)))-273.0;

lcd.clear();
tempr[0] = temp;  // 温度を格納
for (i = 9; i > 0; i--) {
  tempr[i] = tempr[i-1];
  Serial.println(tempr[i]);
  sum += tempr[i];
}
/*
 * 
for (i = 0; i < 10;i++) {
  sum += tempr[i];
}
average = sum / 10;
*/

lcd.print(sum);

delay(1000);

/*
if(temp<20.0){
  lcd.print("error");
  delay(1000);
}else{
  lcd.print(average);
  delay(1000);
}
*/


 
}
