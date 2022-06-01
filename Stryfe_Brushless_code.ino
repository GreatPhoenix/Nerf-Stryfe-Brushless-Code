// code Created by Bridget Whitacre (^▽^)
// Code works with Turnigy Plush speed Controller with Brushless moters installed in a nerf gun
// D9 and D10 are used for the ESC
// D2 is used for start switch
// D13 is used with an LED

#include <Servo.h>

Servo Motor1;
Servo Motor2;

bool allowHighRamp = false;
bool justSpunUp = false;

int speedValue = 170; //(speed 0 == no speed, speed 180 = max speed) 40 = 90 - 100 fps| 50 == 120 - 140 |48 best for 130 fps
// 170 for best accuracy

int idleSpeed = 34; // the speed that the blaster operates when the rev trigger is not pressed (0 to 33 does does nothing, 34 is the best)
void setup() {
  // put your setup code here, to run once:
  Motor1.attach(9, 1000, 2000);
  Motor2.attach(10, 1000, 2000);
  pinMode(2, INPUT_PULLUP);
  digitalWrite(7, LOW);
  Serial.begin(9600);
  Serial.print("Start Code");
  //  Motor1.write(180);
  //  Motor2.write(180);
  //  delay(9000);
  Motor1.write(0);
  Motor2.write(0);
  delay(12000); // the delay for the ecs to calibrate
}

void loop() {
  if (allowHighRamp == true) {
    allowHighRampUP();
  }
  else {
   
    if (digitalRead(2) == LOW) {
      Motor1.write(speedValue);
      Motor2.write(speedValue);
      digitalWrite(13, HIGH);
      justSpunUp = true;

    }
    else {
//      if (justSpunUp == true) {
//        for (int i = speedValue; i >= 1; i--) {
//          Serial.print(i);
//          Serial.print("\n");
//          Motor1.write(i);
//          Motor2.write(i);
//          delay(10);
//        }
//        justSpunUp = false;
//      }

      Motor1.write(idleSpeed);
      Motor2.write(idleSpeed);
      digitalWrite(13, LOW);
    }
  }
}

void allowHighRampUP() { // this allows the motors to be put at a lower speed but ramp up very fast
  if (digitalRead(2) == LOW) {
    Motor1.write(180);
    Motor2.write(180);
    delay(100);
    Motor1.write(speedValue);
    Motor2.write(speedValue);
    digitalWrite(13, HIGH);
  }
  else {
    Motor1.write(0);
    Motor2.write(0);
    digitalWrite(13, LOW);
  }

}
