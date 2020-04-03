
#include <Adafruit_NeoPixel.h>
#define PIN        6
#define pixelNum 60
Adafruit_NeoPixel pixels(pixelNum, PIN, NEO_GRB + NEO_KHZ800);


unsigned long period = 1000 * 10; //  sec
unsigned long currentTime;
unsigned long lastTime = -period;
int states = 0;
int b1 = 3;
int rangeMin = 0;
int rangeMax = 260; //largest value for sound peak difference 
int sensorPin = A0;
int sensorValue = 0;
  
int sampleWindow = 50; //50ms = 20Hz

int brightness = 0;

void setup() {
  Serial.begin(9600);

  pinMode(b1,INPUT);
//  pinMode(b2,INPUT);
//  pinMode(b3,INPUT);
//  pinMode(b4,INPUT);
//  pinMode(b5,INPUT);


  pinMode(sensorPin, INPUT);
  
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
    if(states ==3){
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

  if(peakDifference > rangeMax){
    brightness = 0;
  }
  else{
    brightness = map(peakDifference, rangeMin, rangeMax, 255, 0);
  }
  Serial.println(brightness);
  for (int i=0; i<pixelNum; i++){
    pixels.setPixelColor(i, pixels.Color(255, 101, 35));
    pixels.setBrightness(brightness);
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
