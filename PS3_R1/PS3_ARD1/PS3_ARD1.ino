#include <PS3BT.h>

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);
//left/right
    #define LEFT_FORWARD 
    #define LEFT_FORWARD 
    #define RIGHT_FORWARD 
    #define RIGHT_FORWARD 
//lifter
    #define LEFT_FORWARD 
    #define LEFT_FORWARD 

//speed
    #define FAST_SPEED 255
    #define SLOW_SPEED 100

//Power 
    #define PWM_FREQUENCY 20000
    #define PWM_RESOLUTION 8
    #define PWM_CHANNEL_1 1
    #define PWM_CHANNEL_2 2
    #define PWM_CHANNEL_3 3
    #define PWM_CHANNEL_4 4
    
    #define PWM_CHANNEL_5 5
    #define PWM_CHANNEL_6 6
    #define PWM_CHANNEL_7 7
    #define PWM_CHANNEL_8 8
    
    #define PWM_CHANNEL_9 9
    #define PWM_CHANNEL_10 10

//const
    uint8_t forward = 0;
    uint8_t backward = 0;
    uint8_t left = 0;
    uint8_t right = 0;
    uint8_t fast = 0;
    uint8_t slow = 0;
    uint8_t fan = 0;
    uint8_t turn_left = 0;
    uint8_t turn_right = 0;


void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nPS3 Bluetooth Library Started"));
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(dirA, OUTPUT);
  pinMode(dirB, OUTPUT);
}

void loop() {
  Usb.Task();


  if (PS3.PS3Connected || PS3.PS3NavigationConnected) {

    if (PS3.getButtonPress(RIGHT)) {
      digitalWrite(dirA, HIGH);
      analogWrite(PWMA, 255);
      digitalWrite(dirB, LOW);
      analogWrite(PWMB, 255);
    }
    else if (PS3.getButtonPress(LEFT)) {
      digitalWrite(dirA, LOW);
      analogWrite(PWMA, 255);
      digitalWrite(dirB, HIGH);
      analogWrite(PWMB, 255);
    }
    else if (PS3.getButtonPress(CROSS)) {
      digitalWrite(dirA, LOW);
      analogWrite(PWMA, 255);
      digitalWrite(dirB, LOW);
      analogWrite(PWMB, 255);
    }
    else if (PS3.getButtonPress(TRIANGLE)) {
      digitalWrite(dirA, HIGH);
      analogWrite(PWMA, 255);
      digitalWrite(dirB, HIGH);
      analogWrite(PWMB, 255);;
    }

    else {

      digitalWrite(dirA, 0);
      analogWrite(PWMA, 0);
      digitalWrite(dirB, 0);
      analogWrite(PWMB, 0);
    }

    if (PS3.PS3Connected) {

      if (PS3.getButtonClick(PS)) {
        PS3.disconnect();
      }
    }
  }
}
