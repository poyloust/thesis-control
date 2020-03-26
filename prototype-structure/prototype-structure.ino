
#include <Adafruit_NeoPixel.h>
#define PIN        6
#define pixelNum 60
Adafruit_NeoPixel pixels(pixelNum, PIN, NEO_GRB + NEO_KHZ800);


unsigned long period = 1000 * 5; // 5 sec
unsigned long currentTime;
unsigned long lastTime = -period;
int states = 0;
int b1 = 3;
int rangeMin = 0;
int rangeMax = 1023;
int sensorPin = A0;
int sensorVal = 0;

void setup() {
  Serial.begin(9600);

  
  pinMode(b1,INPUT);
//  pinMode(b2,INPUT);
//  pinMode(b3,INPUT);
//  pinMode(b4,INPUT);
//  pinMode(b5,INPUT);

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
    if(states ==6){
      states = 1;
    }    
    lastTime = currentTime;
  }

  if(states == 1){
    function1();
  }
  if(states == 2){
    function2();
  }
  if(states == 3){
    function3();
  }
  if(states == 4){
    function4();
  }
  if(states == 5){
    function5();
  }

}




void resetTimer(){
  lastTime = currentTime;
}




void function1(){
//  Serial.println("run 1");

  sensorVal = analogRead(sensorPin);
  int brightness = map(sensorVal, rangeMin, rangeMax, 0, 255);
  Serial.println(brightness);
  for (int i=0; i<pixelNum; i++){
    pixels.setPixelColor(i, pixels.Color(255, 101, 35));
    pixels.setBrightness(brightness);
    pixels.show(); 
  }
}

void function2(){  
  Serial.println("run 2");
}

void function3(){
  Serial.println("run 3");
}

void function4(){
  Serial.println("run 4");
}

void function5(){
  Serial.println("run 5");
}
