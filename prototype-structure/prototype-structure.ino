// amplitude from MAX4466 code reference https://hester.mtholyoke.edu/idesign/SensorAmp.html
// smoothing jumping values code from https://www.arduino.cc/en/tutorial/smoothing

#include <Adafruit_NeoPixel.h>
#include <ColorConverter.h>

#define PIN        6
#define pixelNum 60
Adafruit_NeoPixel pixels(pixelNum, PIN, NEO_GRB + NEO_KHZ800);
ColorConverter converter;
int h = 21;
int s = 84;
int i;

unsigned long period = 1000 * 10; //  sec
unsigned long currentTime;
unsigned long lastTime = -period;
int states = 0;
int b1 = 3;
int rangeMin = 0;
int rangeMax = 60; //largest value for sound peak difference 
int sensorPin = A0;
int sensorValue = 0;
  
int sampleWindow = 50; //50ms = 20Hz
const int numReadings = 10;
int readings[numReadings];      
int readIndex = 0;              
int total = 0;                  
int average = 0;                

void setup() {
  Serial.begin(9600);

  pinMode(b1,INPUT);
//  pinMode(b2,INPUT);
//  pinMode(b3,INPUT);
//  pinMode(b4,INPUT);
//  pinMode(b5,INPUT);


  pinMode(sensorPin, INPUT);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  pixels.begin();
  pixels.show();
  
}

void loop() {
  
  currentTime = millis();
  if( digitalRead(b1) == HIGH){
    resetTimer();
    states = 1;
  }
  
  if((currentTime - lastTime) >= period){
    
    if(states<6){ 
      states += 1;
      
      pixels.clear();
      pixels.show();     //clear neopixel at other states
      
    }
    if(states ==2){
      states = 1;
    }    
    lastTime = currentTime;
  }

  if(states == 1){
    function1();
  }

  else{
    Serial.println(states);  
  }
//  if(states == 2){
//    function2();
//  }
//  if(states == 3){
//    function3();
//  }
//  if(states == 4){
//    function4();
//  }
//  if(states == 5){
//    function5();
//  }

}




void resetTimer(){
  lastTime = currentTime;
}




void function1(){

  double startMillis = millis();
  int signalMax = 0;
  int signalMin = 1024;

  while (millis() - startMillis < sampleWindow){
      sensorValue = analogRead(sensorPin);
      if(sensorValue < 1024){
        if(sensorValue > signalMax){
          signalMax = sensorValue;
        }
        else if(sensorValue < signalMin){
          signalMin = sensorValue;
        }
      }
  }

  double peakDifference = signalMax - signalMin;

  total = total - readings[readIndex];
  readings[readIndex] = peakDifference;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;


  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;
  Serial.println(average);
  delay(1);

  
  if(average > rangeMax){
    i = map(average,rangeMax,350,20,0);
  }
  else{
    i = map(average, rangeMin, rangeMax, 90, 20);
  }
  //Serial.println(brightness);
  
  RGBColor color = converter.HSItoRGB(h, s, i);
  for (int j=0; j<pixelNum; j++){
    pixels.setPixelColor(j, color.red, color.green, color.blue);
    pixels.show(); 
  }
}

//void function2(){  
//  Serial.println("2");
//}
//
//void function3(){
//  Serial.println("3");
//}
//
//void function4(){
//  Serial.println("4");
//}
//
//void function5(){
//  Serial.println("5");
//}
