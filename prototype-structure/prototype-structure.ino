unsigned long period = 1000 * 30; //one min
unsigned long currentTime;
unsigned long lastTime;
int states = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  currentTime = millis();
  if((currentTime - lastTime) >= period){
    states += 1;
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

}

void function1(){
  Serial.println("run 1");
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
