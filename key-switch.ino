#include <Keyboard.h>
#include <Mouse.h>
#include <Encoder.h>

#define KEY_DELETE      0xD4


boolean lastButton1 = 0;
boolean button1 = 0;
boolean play = false;

//boolean buttonState = false;

volatile int counterH = 0;
int debouncingDelay = 4;
long oldP;
int buttonState;

int count = 0;
int accountIndex = 0;
boolean choose = false;
boolean lastChoose = false;

String account[3] = {
  "580*******zjy", // my password, don't share out
  "334242",
  "234234"
};

Encoder myEncoder(2,3);


void setup() {
  // put your setup code here, to run once:
  pinMode(5,INPUT);
  pinMode(A1, INPUT_PULLUP);
  attachInterrupt(A1, buttonChange, CHANGE);
  Keyboard.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  button1 = digitalRead(5);
  buttonState = digitalRead(A1);

//  Serial.println(button1);
  if(button1 != lastButton1 && button1){
    play = true;
  }
  lastButton1 = button1;
  
  int change = 0;
  if(count%2 == 1){
    change = readEncoder();
    Serial.println(accountIndex);
    accountIndex += change;
    accountIndex = accountIndex%3;
    choose = true;
  }else{
    if(choose && choose != lastChoose){
      for(int i = 0; i < 20; i++){
        Keyboard.press(0xD8);
        delay(50);
        Keyboard.releaseAll();
        delay(100);
        
      }     
      for(int i = 0; i < 20; i++){
        Keyboard.press(KEY_DELETE);
        delay(50);
        Keyboard.releaseAll();
        delay(100);
        
      }
      
      Keyboard.print(account[accountIndex]);
      lastChoose = false;
      choose = false;
    }
  }
  
  if(play){
//    Keyboard.print("580968720zjy");
    delay(500);
    Keyboard.println("");
    play = false;
  }
//  Serial.println(signal);
}



void buttonChange(){
  delay(debouncingDelay);
  if(buttonState == LOW){
    count++;
    Serial.print("Account:");
//    Serial.println(counterH);
  }
}

int readEncoder(){
  int steps = 0;
  int reading = myEncoder.read();
  if (abs(reading - oldP) > 4){
    steps = (reading - oldP)/abs(reading - oldP);
//    Serial.println(steps);
    oldP =  reading;
  }
  return steps;
}
