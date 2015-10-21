// start - 控制速度

int E1 = 7;
int M1 = 6;
int E2 = 5;
int M2 = 4;

void set_speed_setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void set_speed(int left_speed, int right_speed, int dir) {
  // left_speed: 左轮子速度， right_speed: 右轮子速度，dir: 方向 1 前， 0 后
  if (dir > 0) {
    analogWrite(M1, right_speed);
    analogWrite(E1, 0);

    analogWrite(M2, left_speed);
    analogWrite(E2, 0);
  } else {
    analogWrite(M1, 0);
    analogWrite(E1, right_speed);

    analogWrite(M2, 0);
    analogWrite(E2, left_speed);
  }
}

// end - 控制速度

// start - 控制舵机和超声波传感器
#include <Servo.h> 

Servo myservo;                     // create servo object to control a servo

int pos = 0;                       // variable to store the servo position
unsigned int Distance = 0, Distance2 = 0, goal = 50;

int URPWM = 8;                     // PWM Output 0-25000us,every 50us represent 1cm
int URTRIG = 9;                    // PWM trigger pin

boolean up = true;                 // create a boolean variable

unsigned long time;                // create a time variable
unsigned long urmTimer = 0;        // timer for managing the sensor reading flash rate

uint8_t EnPwmCmd[4] = {0x44, 0x22, 0xbb, 0x01};  // distance measure command

void PWM_Mode_Setup();
void PWM_Mode();

void servo_and_pwm_setup() {
  Serial.begin(9600);                              // Sets the baud rate to 9600
  myservo.attach(10);                              // Pin 10 to control servo
  PWM_Mode_Setup();
}

void servo_and_pwm() {
  if (millis() - time >= 20) {
    time = millis();
    if (up) {
      if(pos >= 0 && pos <= 179) {
        pos = pos + 1;
        myservo.write(pos);
      }
      if (pos > 179) up = false;
    } else {
      if(pos >= 1 && pos <= 180) {
        pos = pos - 1;
        myservo.write(pos);
      }
      if(pos < 1) up = true;
    }
  }

  if(millis() - urmTimer > 50) {
    urmTimer = millis();
    PWM_Mode();
  }
}

void PWM_Mode_Setup() { 
  pinMode(URTRIG, OUTPUT);    // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG, HIGH);   // Set to HIGH
  pinMode(URPWM, INPUT);       // Sending Enable PWM mode command

  for(int i = 0; i < 4; i++){
    Serial.write(EnPwmCmd[i]);
  }
}

void PWM_Mode() {        // a low pull on pin COMP/TRIG  triggering a sensor reading
  digitalWrite(URTRIG, LOW); 
  digitalWrite(URTRIG, HIGH); // reading Pin PWM will output pulses

  unsigned long DistanceMeasured = pulseIn(URPWM, LOW);
  Distance2 = Distance;
  if (DistanceMeasured >= 50000) {  // the reading is invalid.
    // Serial.print("Invalid");    
  } else {
    Distance = DistanceMeasured / 50; // every 50us low level stands for 1cm
  }

  // Serial.print("pos=");
  // Serial.print(pos);
  // Serial.print("D=");
  // Serial.println(Distance);
}

// end - 控制舵机和超声波传感器

void setup() {
  set_speed_setup();
  servo_and_pwm_setup();

  myservo.write(45);
  // find the wall
  // set_speed(50, 50, 1);
}

void change_speed() {
  if (goal < Distance) {
    // turn right
    // set_speed(30, 20, 1);
    if ()
  } else if (goal > Distance) {
    // turn left
    // set_speed(20, 30, 1);
  } else {
   set_speed(30, 30 , 1);
  }
}

void loop() {
  PWM_Mode();
  change_speed();
  delay(50);
  // for(pos = 0; pos <= 90; pos += 1) {                                 
  //   myservo.write(pos);             
  //   // delay(5);
  //   change_speed();
  // }
  // for(pos = 90; pos>=0; pos-=1) {                                
  //   myservo.write(pos);             
  //   // delay(5);
  //   change_speed();
  // }
}
