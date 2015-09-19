#define tempPin A5
float tempSlope;
float tempIntercept;
void setup() {
  // put your setup code here, to run once:
  tempSlope = 20 * ((float)1024/5000);
  tempIntercept = 0;
  Serial.begin(9600);
}

float getTemperature(int analogInput){
  return (analogInput - tempIntercept) /tempSlope;  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(getTemperature(analogRead(tempPin)));
  delay(2000);
}
