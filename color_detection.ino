#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define outPin 8
#define s0 9
#define s1 10
#define s2 11
#define s3 12

boolean DEBUG = true;

// Variables
int red, grn, blu;
String color ="";
long startTiming = 0;
long elapsedTime =0;

void setup(){
 Serial.begin(9600);
  
 pinMode(s0, OUTPUT);
 pinMode(s1, OUTPUT);
 pinMode(s2, OUTPUT);
 pinMode(s3, OUTPUT);
 pinMode(outPin, INPUT); //out from sensor becomes input to arduino

 // Setting frequency scaling to 100%
 digitalWrite(s0,HIGH);
 digitalWrite(s1,HIGH);

 lcd.begin(16, 2);
 lcd.clear();
 lcd.setCursor (3,0);
 lcd.print("Welcome To");
 lcd.setCursor (1,1);
 lcd.print("Color Detector");
 delay(2000);  
 lcd.clear();  
 startTiming = millis();
}

void loop(){
 getColor();
  
 if(DEBUG)printData(); 
 elapsedTime = millis()-startTiming; 
 if (elapsedTime > 1000) {
   showDataLCD();
  startTiming = millis();

  
  }
}

/* read RGB components */
void readRGB(){
 red = 0, grn=0, blu=0;
  
 int n = 10;
 for (int i = 0; i < n; ++i){
  //read red component
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = red + pulseIn(outPin, LOW);
  
  //read green component
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  grn = grn + pulseIn(outPin, LOW);
   
  //let's read blue component
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  blu = blu + pulseIn(outPin, LOW);
 }
 red = red/n;
 grn = grn/n;
 blu = blu/n;
}

/***************************************************
* Showing captured data at Serial Monitor
****************************************************/
void printData(void){
 Serial.print("red= ");
 Serial.print(red);
 Serial.print("  green= ");
 Serial.print(grn);
 Serial.print("  blue= ");
 Serial.print(blu);
 Serial.print (" - ");
 Serial.print (color);
 Serial.println (" detected!");
}

///***************************************************
//* Showing capured data at LCD
//****************************************************/
void showDataLCD(void){
lcd.clear();
lcd.setCursor (0,0);
lcd.print("R");
lcd.print(red);
lcd.setCursor (6,0);
lcd.print("G");
lcd.print(grn);
lcd.setCursor (12,0);
lcd.print("B");
lcd.print(blu);  

lcd.setCursor (0,1);
lcd.print("Color: ");  
lcd.print(color);  

}


void getColor(){  
 readRGB();

   if(red>9 && red<13 && grn>20 && grn<26 && blu>17 && blu<20) color = "RED";
else if(red>17 && red<21 && grn>11 && grn<15 && blu>12 && blu<18) color = "GREEN";
else if(red>30 && red<36 && grn>29 && grn<34 && blu>20 && blu<27) color = "BLUE";
else if(red>6 && red<10  && grn>10 && grn<15 && blu>17 && blu<20) color = "YELLOW";
else if(red>7 && red<10  && grn>7 && grn<10 && blu>6 && blu<10) color = "WHITE";
else if(red>49 && red<55 && grn>49 && grn<52 && blu>40 && blu<45) color = "BLACK";
else color = "NO_COLOR";

}
