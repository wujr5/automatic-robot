#include <arduino.h>

Servo myservo;                     // create servo object to control a servo

int pos = 0;                       // variable to store the servo position
unsigned int Distance = 0;

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
  myservo.attach(10);                              // Pin 9 to control servo
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

  if (DistanceMeasured == 50000) {  // the reading is invalid.
    Serial.print("Invalid");    
  } else {
    Distance=DistanceMeasured / 50; // every 50us low level stands for 1cm
  }

  Serial.print("pos=");
  Serial.print(pos);
  Serial.print("D=");
  Serial.println(Distance);
}
