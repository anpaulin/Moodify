#include <LiquidCrystal.h>

#include <Wire.h>
#include <SparkFunHTU21D.h>

#define soundPin A3
#define tempPin A2
#define lightPin A1
#define motionPin 13
#define Epin 8
#define Rs 7
#define D7 9
#define D6 10
#define D5 12
#define D4 11

float tempSlope;
float tempIntercept;
float soundSlope;
float soundIntercept;
float lightSlope;
float lightIntercept;
char * buffer;
HTU21D myHumidity;
LiquidCrystal lcd(Rs, Epin, D4, D5, D6, D7);
void setup() {
  // put your setup code here, to run once:
  tempSlope = 20 * ((float)1024/5000);
  tempIntercept = 0;
  lightSlope = ((float)1/69);
  lightIntercept = -4.78;
  Serial.begin(9600);
  pinMode(motionPin, INPUT);
  delay(2000);
  buffer = (char*)malloc(sizeof(char)*200);
  myHumidity.begin();
  lcd.begin(16, 1);
  // set the display to automatically scroll:
  lcd.autoscroll();
  lcd.setCursor(16, 0);
}

/**@params analogInput this is the 
 * analog reading of the temperatire sensor pin
 * @return temperature in Celcius
 */
float getTemperature(int analogInput){
  return (analogInput - tempIntercept) /tempSlope;  
}

int getSound(int analogInput){
  return (analogInput);  
}

//returns light on a scale of 0 to 10
//0 total darkness, 10 light directly on it
int getLight(int analogInput){
  float returnValue = lightSlope * analogInput + lightIntercept;
  if(returnValue < 0)
    return 0;
  else if(returnValue > 10)
    return 10;
  else
    return ((int)returnValue);  
}
void loop() {
  // put your main code here, to run repeatedly:
  int motion = digitalRead(motionPin);
  sprintf(buffer, "Temperature: %d\tSound: %d\t Light:%d\tHumidity: %d\tTemperature:%d\tmotion:%d.\t",
    (int)getTemperature(analogRead(tempPin)),
    getSound(analogRead(soundPin)),
    getLight(analogRead(lightPin)),
    (int)myHumidity.readHumidity(),
    (int)myHumidity.readTemperature(),
    motion
    );
  Serial.println(buffer);
  int i = 0;
  while(buffer[i] != 0){
    if(buffer[i] != '\t')
      lcd.print(buffer[i]);
    else{
      lcd.print(' ');
      delay(200);
      lcd.print(' ');
      delay(200);
      lcd.print(' ');
      delay(200);
      lcd.print(' ');
    }
    delay(300);
    i++;
  }
//  // turn off automatic scrolling
//  lcd.noAutoscroll();
  if(motion == LOW)
    delay(2000);
  delay(2000);
}
