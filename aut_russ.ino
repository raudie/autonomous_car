#include <Servo.h>
#include <HCSR04.h>

Servo L_motor;
Servo R_motor;
Servo steering_servo;

int steering_servo_range[] = {1100, 1900}; // Range of steering servo

// Offsets to zero motor speeds (PWM), can both be nonzero but it will limit max speed
int L_mot_offset = 0;        // PWM offset of left motor zero position
int R_mot_offset = 10;       // PWM offset of right motor zero position

// Absolute hardware PWM limits of motor
int abs_mot_pwm[] = {1000, 2000};

// Constrained PWM limits of motor. This prevents a max PWM operation from resulting in differential wheel drive speeds
int L_min_mot_pwm = abs_mot_pwm[0] - min(L_mot_offset,0);
int L_max_mot_pwm = abs_mot_pwm[1] - max(L_mot_offset,0);
int R_min_mot_pwm = abs_mot_pwm[0] - min(R_mot_offset,0);
int R_max_mot_pwm = abs_mot_pwm[1] - max(R_mot_offset,0);

// Sensor reading variables
byte echo_count = 1;                          // Number of distance sensors
byte trigger_pin = 21;
byte* echo_pins = new byte[echo_count] {12};
double* distances = new double[echo_count];

// State variables
double speed_val = 0;       // -1 full reverse, 1 full forward
double steer_val = 0;       // -1 full left, 1 full right

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  L_motor.attach(5);
  R_motor.attach(7);
  steering_servo.attach(2);
  
  HCSR04.begin(trigger_pin, echo_pins, echo_count);
  
}

void loop() {
  bool runner = true;
  
  while (runner) {
    update_distances();
    
    if (distances[0] < 30) {
      speed_val = 0;
    }
    else {
      speed_val = 0.2;
    }
    
    set_speed();
    set_steer();
    
    print_logs();
  }


  while (true) {      // Stall in an endless loop, zero out

    speed_val = 0;
    steer_val = 0;
    
    set_speed();
    set_steer();
    // Do Nothing
  }

}

/* 
Description: Set car speed from global speed_val
Inputs: 
    None
Outputs:
    None 
*/
void set_speed(){
  L_motor.writeMicroseconds(map(speed_val, -1, 1, L_min_mot_pwm, L_max_mot_pwm));   
  R_motor.writeMicroseconds(map(speed_val, -1, 1, R_min_mot_pwm, R_max_mot_pwm));   
}


/* 
Description: Set steering angle of wheels from global steer_val
Inputs: 
    None 
Outputs:
    None 

Notes: Should make this degrees instead of unitless value
*/
void set_steer(){
  steering_servo.writeMicroseconds(map(steer_val, -1, 1, steering_servo_range[0], steering_servo_range[1]));
}

void update_distances() {
  distances = HCSR04.measureDistanceCm();
}

void print_logs(){
  Serial.print(distances[0]);
  Serial.println(" cm");
  Serial.println("---");
}
