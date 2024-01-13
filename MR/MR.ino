  /*
 * Arduino UNO
 * 13 SCK
 * 12 MISO
 * 11 MOSI
 * 10 SS
 * 
 * Arduino Mega
 * 50 MISO
 * 51 MOSI
 * 52 SCK
 * 53 SS
 */
#include <PS2X_lib.h>
#include <Servo.h>

#define LEFT_FORWARD 2
#define LEFT_BACKWARD 3
#define RIGHT_FORWARD 4
#define RIGHT_BACKWARD 5

#define LIFTER_UP 6
#define LIFTER_DOWN 7

#define SERVO 8

#define FAN_SUCK 6
#define FAN_BLOW 7

#define LAUNCHER_CW 11
#define LAUNCHER_CCW 12

#define DEFAULT_SPEED 150
#define FAST_SPEED 255
#define SLOW_SPEED 100

#define PS2_DAT        52 //  13  //14    
#define PS2_CMD        51 //  11  //15
#define PS2_SEL        53 //  10  //16
#define PS2_CLK        50 //  12  //17
  
#define pressures   false
#define rumble      false

PS2X ps2x;
Servo servo;

int error = 0;
byte type = 0;
byte vibrate = 0;

uint8_t position = 0;

void forward(byte speed) {
  analogWrite(LEFT_FORWARD, speed);
  analogWrite(LEFT_BACKWARD, 0);
  analogWrite(RIGHT_FORWARD, speed);
  analogWrite(RIGHT_BACKWARD, 0);  
}

void backward(byte speed) {
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(LEFT_BACKWARD, speed);
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(RIGHT_BACKWARD, speed);  
}

void rotateLeft(byte speed) {
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(LEFT_BACKWARD, speed);
  analogWrite(RIGHT_FORWARD, speed);
  analogWrite(RIGHT_BACKWARD, 0);    
}

void rotateRight(byte speed) {
  analogWrite(LEFT_FORWARD, speed);
  analogWrite(LEFT_BACKWARD, 0);
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(RIGHT_BACKWARD, speed);   
}

void liftUp() {
  analogWrite(LIFTER_UP, 100);
  analogWrite(LIFTER_DOWN, 0);
}

void putDown() {
  analogWrite(LIFTER_UP, 0);
  analogWrite(LIFTER_DOWN, 100);
}

void suck() {
  analogWrite(FAN_SUCK, 255);
  analogWrite(FAN_BLOW, 0);
}

void release() {
  analogWrite(FAN_SUCK, 0);
  analogWrite(FAN_BLOW, 255);
}



void shoot() {
  analogWrite(LAUNCHER_CW, 0);
  analogWrite(LAUNCHER_CCW, 255);
}

void stand() {
  analogWrite(LEFT_FORWARD, 0);
  analogWrite(LEFT_BACKWARD, 0);
  analogWrite(RIGHT_FORWARD, 0);
  analogWrite(RIGHT_BACKWARD, 0);
  analogWrite(LIFTER_UP, 0);
  analogWrite(LIFTER_DOWN, 0);
  analogWrite(FAN_SUCK, 0);
  analogWrite(FAN_BLOW, 0);
}

void setup(){
  pinMode(LEFT_FORWARD, OUTPUT);
  pinMode(LEFT_BACKWARD, OUTPUT);
  pinMode(RIGHT_FORWARD, OUTPUT);
  pinMode(RIGHT_BACKWARD, OUTPUT);
  pinMode(LIFTER_UP, OUTPUT);
  pinMode(LIFTER_DOWN, OUTPUT);
  pinMode(FAN_SUCK, OUTPUT);
  pinMode(FAN_BLOW, OUTPUT);
  pinMode(LAUNCHER_CW, OUTPUT);
  pinMode(LAUNCHER_CCW, OUTPUT);

  servo.attach(8);
  
  Serial.begin(112500);  
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0)
    Serial.print("OK!");
  else if(error == 1)
    Serial.println("No controller found!");
  else if(error == 2)
    Serial.println("Controller found but not accepting commands!");
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode!");
      
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller");
      break;
    case 1:
      Serial.print("DualShock Controller");
      break;
    case 2:
      Serial.print("GuitarHero Controller");
      break;
	case 3:
      Serial.print("Wireless Sony DualShock Controller");
      break;
   }
}

void loop() {
  if(error == 1)
    return;
  ps2x.read_gamepad(false, vibrate);

  if(ps2x.Button(PSB_PAD_UP)) {
    if(ps2x.Button(PSB_L1)) {
      forward(FAST_SPEED);
      Serial.println("Fast forward");
    }
    else if(ps2x.Button(PSB_L2)) {
      forward(SLOW_SPEED);
      Serial.println("Slow forward");
    }
    else {
      forward(DEFAULT_SPEED);
      Serial.println("Forward");
    }
  }
  
  else if(ps2x.Button(PSB_PAD_DOWN)) {
    if(ps2x.Button(PSB_L1)) {
      backward(FAST_SPEED);
      Serial.println("Fast backward");
    }
    else if(ps2x.Button(PSB_L2)) {
      backward(SLOW_SPEED);
      Serial.println("Slow backward");
    }
    else {
      backward(DEFAULT_SPEED);
      Serial.println("Backward");
    }
  }

  else if(ps2x.Button(PSB_PAD_LEFT)) {
    if(ps2x.Button(PSB_L1)) {
      rotateLeft(FAST_SPEED);
      Serial.println("Fast rotate left");
    }
    else if(ps2x.Button(PSB_L2)) {
      rotateLeft(SLOW_SPEED);
      Serial.println("Slow rotate left");
    }
    else {
      rotateLeft(DEFAULT_SPEED);
      Serial.println("Rotate left");
    }
  }
  
  else if(ps2x.Button(PSB_PAD_RIGHT)) {
    if(ps2x.Button(PSB_L1)) {
      rotateRight(FAST_SPEED);
      Serial.println("Fast rotate right");
    }
    else if(ps2x.Button(PSB_L2)) {
      rotateRight(SLOW_SPEED);
      Serial.println("Slow rotate right");
    }
    else {
      rotateRight(DEFAULT_SPEED);
      Serial.println("Rotate right");
    }
  }

  else if(ps2x.Button(PSB_R1)) {
    liftUp();
    Serial.println("Lift up");
  }
  
  else if(ps2x.Button(PSB_R2)) {
    putDown();
    Serial.println("Put down");
  }
  
  else if(ps2x.Button(PSB_TRIANGLE)) {
    Serial.println("Shoot");
  }
  
  else if(ps2x.Button(PSB_CROSS)) {
    Serial.println("Shoot");
  }
  
  else if(ps2x.Button(PSB_SQUARE)) {
    position++;
    if(position > 180)
      position = 180;
    servo.write(position);
    Serial.print("Hand up ");
    Serial.println(position);
    delay(5);
  }
  
  else if(ps2x.Button(PSB_CIRCLE)) {
    position--;
    if(position < 1)  
      position = 1;
    servo.write(position);     
    Serial.print("Hand down ");
    Serial.println(position);
    delay(5);
  }
  
  else {
    stand();
    Serial.println("Stand");
  }
//  delay(10);  
}
