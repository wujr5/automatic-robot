#include <arduino.h>

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
  if (dir == 1) {
    analogWrite(M1, left_speed);
    analogWrite(E1, 0);

    analogWrite(M2, right_speed);
    analogWrite(E2, 0);
  } else {
    analogWrite(M1, 0);
    analogWrite(E1, left_speed);

    analogWrite(M2, 0);
    analogWrite(E2, right_speed);
  }
}