#include <Servo.h>

Servo left_motor;
Servo right_motor;
Servo myservo;


int left_speed = 0;
int right_speed = 0;
int left_offset = 0;
int right_offset = 1;

void setup() {
  // put your setup code here, to run once:
  left_motor.attach(5);
  right_motor.attach(7);
  myservo.attach(2);
  
}

void loop() {

  center();
  forward(25, 3);     // Go forward at 10% for 2 seconds
  delay(500);
  right();       // Go right at 10% for 2 seconds
  forward(25,5);
  delay(500);
  center();
  forward(25, 3);
  delay(500);
  
  //left();       // Go right at 10% for 2 seconds
  //delay(500);



  
  while (true) {      // Stall in an endless loop
    // Do Nothing
  }

}


void zero(){
  left_motor.writeMicroseconds(percent_to_pwm(0));
  right_motor.writeMicroseconds(percent_to_pwm(0 + (right_offset)));
}

int percent_to_pwm(int percent){
  return constrain(percent,-100,100) * 5 + 1500;
}

void forward(int speed_percent, int wait_time){
  left_motor.writeMicroseconds(percent_to_pwm(speed_percent));
  right_motor.writeMicroseconds(percent_to_pwm((speed_percent + right_offset)));
  delay(wait_time*1000);
  zero();
}

void reverse(int speed_percent, int wait_time){
  left_motor.writeMicroseconds(percent_to_pwm(-speed_percent));
  right_motor.writeMicroseconds(percent_to_pwm(-(speed_percent + right_offset)));
  delay(wait_time*1000);
  zero();
}



void right(){
  myservo.writeMicroseconds(1900); //Dont do to strong, it could break stuff.
  delay(3000);
}

void center(){
  myservo.writeMicroseconds(1500); //Dont do to strong, it could break stuff.
  delay(3000);
}
///rn delaty is 3 seconds so it will turn then wait 3 seconds
void left(){
  myservo.writeMicroseconds(1100); //Dont do to strong, it could break stuff.
  delay(3000);
}
