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

void set_speed_left(int left_speed, int dir) {
  if (dir > 0) {
    analogWrite(M2, left_speed);
    analogWrite(E2, 0);
  } else {
    analogWrite(M2, 0);
    analogWrite(E2, left_speed);
  }
}

void set_speed_right(int right_speed, int dir) {
  if (dir > 0) {
    analogWrite(M1, right_speed);
    analogWrite(E1, 0);
  } else {
    analogWrite(M1, 0);
    analogWrite(E1, right_speed);
  }
}
// end - 控制速度

// start - 控制舵机和超声波传感器
#include <Servo.h> 

Servo myservo;                     // create servo object to control a servo

int pos = 0;                       // variable to store the servo position
unsigned int Distance = 0, goal = 40;

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
  // myservo.attach(10);                              // Pin 10 to control servo
  PWM_Mode_Setup();
}

void servo_and_pwm() {
  if(up) {
    myservo.write(135);
    up = false;
  }
  else {
    myservo.write(45);
    up = true;
  }
}

// end - 控制舵机和超声波传感器


bool a = true;
void change_speed() {
  int left = 0;
  int right = 0;

  if (Distance > 60) {
    left = 70 + 50;
    right = 30 + 50;
  }
  else if (Distance > 40) {
    left = 50 + 50;
    right = 30 + 50;
  }
  else if (Distance > 30) {
    left = 20 + 50;
    right = 40 + 50;
  }
  else if (Distance > 10) {
    left = 20;
    right = 50 + 50;
  }
  else if (Distance <= 10) {
   left = 10;
   right = 55 + 50;
  }

  // if (true) {
  //   int temp = left;
  //   left = right;
  //   right = temp;
  //   // a = false;
  // }

  set_speed(right, left, 1);
}

// int adjustServoCount = 5;

void findTheWall() {
  PWM_Mode();

  // if (adjustServoCount > 0) {
  //   if(Distance > 100) {
  //     myservo.write(45);
  //     up = true;
  //   } else {
  //     myservo.write(135);
  //     up = false;
  //   }
  //   adjustServoCount = adjustServoCount - 1;
  // }

  change_speed();
}

void findTheMan() {

}

int blackLine = 0;
bool preDirLeft = false;
bool preDirRight = false;

void findTheLine_king() {
  int leftLight = digitalRead(16);
  int centerLight = digitalRead(15);
  int rightLight = digitalRead(14);

  if(leftLight == blackLine) {
    set_speed(20, 80, 1);
    preDirLeft = true;
    preDirRight = false;
  }
  else if (rightLight == blackLine) {
    set_speed(80, 20, 1);
    preDirLeft = false;
    preDirRight = true;
  }
  else {
    if (centerLight == blackLine) {
      set_speed(120, 120, 1);
      preDirLeft = false;
      preDirRight = false;
    } else if (preDirLeft) {
      set_speed(0, 85, 1);
    } else if (preDirRight) {
      set_speed(85, 0, 1);
    } else {
      set_speed(120, 120, 1);
      preDirLeft = false;
      preDirRight = false;
    }
  }
}

int centerLightCount = 0;
int leftLightCount = 0;
int rightLightCount = 0;

void findTheLine() {
  int leftLight = digitalRead(16);
  int centerLight = digitalRead(15);
  int rightLight = digitalRead(14);

  if(centerLight != blackLine && leftLight == blackLine && rightLight != blackLine) {
    set_speed(150, 255, 1);
    preDirLeft = true;
    preDirRight = false;

    leftLightCount++;
    centerLightCount = 0;
    rightLightCount = 0;
  }
  else if (centerLight != blackLine && leftLight != blackLine && rightLight == blackLine) {
    set_speed(255, 150, 1);
    preDirLeft = false;
    preDirRight = true;

    leftLightCount = 0;
    centerLightCount = 0;
    rightLightCount++;
  }
  else {
    if (centerLight == blackLine && leftLight == blackLine && rightLight == blackLine) {
      if (preDirLeft) set_speed(30, 60, 1);
      else if (preDirRight) set_speed(60, 30, 1);

      preDirLeft = false;
      preDirRight = false;
    }
    else if (centerLight == blackLine && leftLight != blackLine && rightLight != blackLine) {
      set_speed(200, 200, 1);
      preDirLeft = false;
      preDirRight = false;

      leftLightCount = 0;
      centerLightCount++;
      rightLightCount = 0;
    }
    else if (centerLight == blackLine && leftLight == blackLine && rightLight != blackLine) {
      set_speed(30, 60, 1);
    }
    else if (centerLight == blackLine && leftLight != blackLine && rightLight == blackLine) {
      set_speed(60, 30, 1);
    }
    else if (leftLightCount >= 1) {
      set_speed(0, 140, 1);
    }
    else if (rightLightCount >= 1) {
      set_speed(140, 0, 1);
    } else {
      if (preDirLeft) set_speed(60, 100, 1);
      else if (preDirRight) set_speed(100, 60, 1);
      preDirLeft = false;
      preDirRight = false;
    }
  }

  // if (centerLightCount == 2) {
  //   set_speed(220, 220, 1);
  // }

  if (centerLightCount >= 2) {
    set_speed(255, 255, 1);
  }
  // else if (leftLightCount >= 2) {
  //   set_speed(10, 100, 1);
  // }
  // else if (rightLightCount >= 2) {
  //   set_speed(100, 10, 1);
  // }
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
  if (DistanceMeasured >= 50000) {  // the reading is invalid.
    Serial.print("Invalid");    
  } else {
    Distance = DistanceMeasured / 50; // every 50us low level stands for 1cm
    Serial.print(Distance);
    Serial.println("cm");
  }
}

// ------ 相扑算法 ---------

int function = 3;

void rotate_right() {
  set_speed_right(255, 1);
  set_speed_left(255, 0);
}

void rotate_left() {
  set_speed_right(255, 0);
  set_speed_left(255, 1);
}

int counter = 0;
int mode = 0;
int flag = 0;

void xiangpu() {
  int head = digitalRead(14);
  int tail_right = digitalRead(16);
  int tail_left = digitalRead(15);

  if (flag == 0) {
    set_speed(255, 255, 1);
    flag = 1;
    delay(1000);
  }

  if (mode == 0) {
    if(head == blackLine) {
      set_speed(100, 100, 0);
      mode = 1;
      // delay(500);
    }
    else if(tail_right == blackLine) {
      set_speed(200, 200, 1);
      // delay(500);
    }
    else if (tail_left == blackLine) {
      set_speed(200, 200, 1);
    }
    else {
      // if (counter >= 200) {
      //   function = 4;
      // }
      // counter++;
      
      // set_speed(0, 200, 1);
      rotate_right();
    }
  } else {
    if (tail_left == blackLine) {
      set_speed(200, 100, 1);
      delay(200);
      mode = 0;
    }
    else if (tail_right == blackLine) {
      set_speed(100, 200, 1);
      delay(200);
      mode = 0;
    }
  }
}

void attack() {
  int head = digitalRead(14);
  int tail_right = digitalRead(16);
  int tail_left = digitalRead(15);

  if (head == blackLine) {
    function = 3;
    counter = 0;
  } else {
    set_speed(100, 100, 0);
    if (tail_left == blackLine || tail_right == blackLine) {
      // set_speed
    }
  }
}

void setup() {
  set_speed_setup();
  PWM_Mode_Setup();

  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  function = 0;
}

void loop() {

  PWM_Mode();
  if (function == 0)
    findTheWall();
  else if (function == 1)
    findTheMan();
  else if (function == 2)
    findTheLine();
  else if (function == 3)
    xiangpu();
  else if (function == 4)
    attack();
}
