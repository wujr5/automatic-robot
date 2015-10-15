
#include "pt-1.4/pt.h"

int E1 = 7;   
int M1 = 6;
int E2 = 5;                         
int M2 = 4;    

int URECHO = 8;
int URTRIG = 9;
int sensorPin = A0;
int sensorValue = 0;

//int speadLeft, speadRight;

unsigned int DistanceMeasured = 0;

void set_speed_setup();
void set_speed();

void ultrasonic_setup();
void get_distance_from_ultrasonic();

void setup() {
  set_speed_setup();
  ultrasonic_setup();
//  speadLeft = 100, speadRight = 100;
  set_speed();
} 

void loop() {
// set_speed(100);
  get_distance_from_ultrasonic();
}

void set_speed_setup() {
//   pinMode(M1, OUTPUT);   
//   pinMode(M2, OUTPUT);
}

void set_speed() {
  int  valueLeft = 100;
  //   for(int value = 0 ; value <= 255; value += 5) { 
  analogWrite(M1, 0);
  analogWrite(M2, 0);       
  analogWrite(E1, 0);   //PWM调速
  analogWrite(E2, 0);   //PWM调速 
  //     delay(1000);
  //  }
}

void ultrasonic_setup() {
  Serial.begin(9600);                        // Sets the baud rate to 9600
  pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                 // Set to HIGH 
  pinMode(URECHO, INPUT);                    // Sending Enable PWM mode command
}

void get_distance_from_ultrasonic() {
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);

  unsigned long LowLevelTime = pulseIn(URECHO, LOW);

  if(LowLevelTime >= 45000) {
    Serial.print("Invalid");
  } else {
    DistanceMeasured = LowLevelTime / 50;
    Serial.print(DistanceMeasured);
    Serial.println("cm");
  }
}

