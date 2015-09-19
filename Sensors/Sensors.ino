#define tempPin A5
#define lightPin A4
#define soundPin A3

float tempSlope;
float tempIntercept;
float soundSlope;
float soundIntercept;
float lightSlope;
float lightIntercept;
char * buffer;

void setup() {
  // put your setup code here, to run once:
  tempSlope = 20 * ((float)1024/5000);
  tempIntercept = 0;
  lightSlope = ((float)1/69);
  lightIntercept = -4.78;
  Serial.begin(9600);
  buffer = (char*)malloc(sizeof(char)*200);
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
  sprintf(buffer, "Temperature: %d\tSound: %d\t Light:%d",
    (int)getTemperature(analogRead(tempPin)),
    getSound(analogRead(soundPin)),
    getLight(analogRead(lightPin))
    );
  Serial.println(buffer);
  delay(2000);
}
