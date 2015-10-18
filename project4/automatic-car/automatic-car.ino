#include "speed-and-direction/speed-and-direction.h"
// 提供如下函数：
// set_speed_setup() 速度初始化设置
// set_speed(int left, int right, int didr) 设置左右轮子速度，大小从0-225，两轮一样。dir控制方向
// 1 前，0 后

#include <Servo.h> 
// 驱动舵机的库

#include "ultrasonic/ultrasonic.h"
// 提供如下函数：
// servo_and_pwm_setup() 舵机和超声波传感器初始化设置
// servo_and_pwm() 舵机和超声波传感器运行

void setup() {
  set_speed_setup();
  servo_and_pwm_setup();
  // set_speed(0, 100, 0);
}

void loop() {
  servo_and_pwm();
  set_speed(0, 50, 1);
  // delay(2000);
  // set_speed(100, 100, 1);
  // delay(3000);
}
